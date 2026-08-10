/*
Problem: Find the Lexicographically Smallest Valid Sequence
Link: LeetCode 3291 / Problem 3302 - Find the Lexicographically Smallest Valid Sequence

Difficulty: Medium
Tags: Two Pointers, String, Dynamic Programming, Greedy

Intuition:
We need to find a sequence of indices in `word1` of length `M` (where `M = word2.length()`) such that the characters picked match `word2`, with AT MOST 1 mismatch (change allowed).
We also want the resulting array of indices to be LEXICOGRAPHICALLY SMALLEST.

Key Strategy:
To get the lexicographically smallest indices, we should greedily match each character of `word2` as early as possible in `word1`.

1. Suffix Precomputation:
   - Compute `last[j]`, which stores the maximum index in `word1` where we can match `word2[j...M-1]` as a exact subsequence without any mismatches.
   - This allows us to know during our forward traversal whether the remaining suffix of `word2` can be formed strictly after our current position in `word1`.

2. Greedy Forward Construction:
   - Maintain `usedChange` (boolean flag to track if we've used our 1 character mismatch allowance).
   - Iterate through `word2` from index `j = 0` to `M - 1`.
   - For each character `word2[j]`, scan `word1` from our current index `i`:
     * If `word1[i] == word2[j]`:
       Match character exactly, add `i` to answer, increment `i` and `j`.
     * If `word1[i] != word2[j]`:
       - If `!usedChange` and the remaining suffix `word2[j + 1...M - 1]` can be matched in `word1[i + 1...]` (i.e., `i + 1 <= last[j + 1]`):
         Greedily use our mismatch here at index `i`! Set `usedChange = true`, add `i` to answer, increment `i` and `j`.
       - Otherwise, skip `word1[i]` (increment `i` only) and continue searching for a match.

---

Approach:

1. Precompute Suffixes (`last` array):
   * `last[j]` = largest index in `word1` that can match `word2[j]`, given `word2[j+1...]` is matched at/after `last[j+1]`.

2. Construct Solution:
   * Walk `i` through `word1` and `j` through `word2`.
   * At each step, greedily choose index `i` either via exact match or via allowed mismatch if the suffix condition `i + 1 <= last[j + 1]` holds.

3. Result:
   * If we successfully collect `M` indices, return the array.
   * Otherwise, return an empty vector `{}`.

---

⏱ Time Complexity:
O(N + M)

* Precomputing `last` takes $O(N + M)$ time where $N = \text{word1.length()}$ and $M = \text{word2.length()}$.
* The greedy matching loop iterates through $N$ and $M$ once with $O(1)$ checks per step.
* Total Runtime: $O(N + M)$ linear time.

Space Complexity:
O(M) Auxiliary Space

* `last` vector requires $O(M)$ extra space.
*/

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = word1.length();
        int m = word2.length();

        // last[j] stores the maximum index in word1 to match word2[j...m-1] as an exact subsequence
        vector<int> last(m, -1);

        int ptr = n - 1;
        for (int j = m - 1; j >= 0; --j) {
            while (ptr >= 0 && word1[ptr] != word2[j]) {
                ptr--;
            }
            last[j] = ptr;
            if (ptr >= 0) {
                ptr--; // move to the next available position to the left
            }
        }

        vector<int> ans;
        bool usedChange = false;
        int i = 0; // index in word1

        for (int j = 0; j < m; ++j) {
            while (i < n) {
                if (word1[i] == word2[j]) {
                    // Exact match
                    ans.push_back(i);
                    i++;
                    break;
                } else if (!usedChange) {
                    // Mismatch: check if remaining suffix word2[j+1...m-1] can be matched in word1[i+1...]
                    bool canMatchSuffix = (j == m - 1) || (i + 1 <= last[j + 1]);
                    if (canMatchSuffix) {
                        usedChange = true;
                        ans.push_back(i);
                        i++;
                        break;
                    }
                }
                i++;
            }

            // If we couldn't find a valid index for word2[j], no solution exists
            if (ans.size() <= j) {
                return {};
            }
        }

        return ans;
    }
};