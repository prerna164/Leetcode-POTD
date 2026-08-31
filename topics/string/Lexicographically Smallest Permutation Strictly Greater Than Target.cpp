/*
Problem: Lexicographically Smallest Permutation Strictly Greater Than Target
Link: LeetCode (Lexicographically Smallest Permutation Greater Than Target)

Difficulty: Medium / Hard
Tags: String, Backtracking, Greedy, Counting, Frequency Array

Intuition:
We are looking for a permutation of `s` that is strictly greater than `target` lexicographically.
To make it as small as possible while being strictly greater than `target`:
1. Matching Prefix:
   - Suppose the permutation matches `target` up to index `i - 1`.
   - At index `i`, we choose a character `c` from the available frequency pool of `s` such that `c > target[i]`.
   - For all positions after `i` (`i + 1` to `n - 1`), we fill them with the remaining available characters of `s` in sorted (ascending) order.

2. Finding the Optimal Split Index `i`:
   - To make the overall string as small as possible, we should try to match as long a prefix as possible.
   - We can iterate over all possible prefix match lengths `i` from `n - 1` down to `0`.
   - For a fixed prefix length `i`:
     - Check if the characters in `target[0...i-1]` can be formed by `s`. If not, this prefix length is invalid.
     - Look for the smallest character `c` in the remaining frequency count of `s` such that `c > target[i]`.
     - If such a character `c` exists, construct the result string:
       `target[0...i-1]` + `c` + (all remaining available characters in ascending order).
     - Because we iterate `i` from right to left (longest prefix match first), the first valid permutation we construct is guaranteed to be the lexicographically smallest one that is strictly greater than `target`.

---

Approach:

1. Frequency Counting:
   * Build a global character frequency array `totalCount` for string `s`.

2. Iterate Prefix Match Length `i` from `n - 1` Down to `0`:
   * Compute the frequency array of the prefix `target[0...i-1]`.
   * Verify if all characters in `target[0...i-1]` are available in `s` (i.e., `prefixCount[ch] <= totalCount[ch]`). If not, continue to smaller `i`.
   * For remaining available characters `remCount = totalCount - prefixCount`:
     - Try every character `c` from `target[i] + 1` to `'z'`.
     - If `remCount[c] > 0`, we have found our answer!
     - Append `c` to `target[0...i-1]`, decrement `remCount[c]`, and append all remaining characters in `remCount` in alphabetical order.
     - Return the constructed string immediately.

3. Fallback:
   * If no such `i` and `c` pair is found, return `""`.

---

⏱ Time Complexity:
O(N^2 + N * 26)

* `N` is up to 300.
* For each `i` from `N - 1` down to `0`:
  - Checking prefix validity takes O(26) time.
  - Finding candidate character `c` takes O(26) time.
  - Constructing the final string takes O(N) time (only executed once upon finding the answer).
* Total Runtime: O(N^2) worst case, executing in under 1 millisecond.

Space Complexity:
O(N + 26) Auxiliary Space

* Space used for frequency arrays of size 26 and the output string.
*/

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = s.length();
        vector<int> totalCount(26, 0);
        for (char ch : s) {
            totalCount[ch - 'a']++;
        }

        // Keep track of the frequency of characters in target[0...i-1]
        vector<int> prefixCount(26, 0);
        for (int i = 0; i < n; ++i) {
            prefixCount[target[i] - 'a']++;
        }

        // Iterate backwards over the prefix length i to maximize the matched prefix
        for (int i = n - 1; i >= 0; --i) {
            // Remove target[i] from prefixCount because position i is where we want a strictly larger char
            prefixCount[target[i] - 'a']--;

            // Check if target[0...i-1] can be formed using a subset of characters from s
            bool validPrefix = true;
            for (int c = 0; c < 26; ++c) {
                if (prefixCount[c] > totalCount[c]) {
                    validPrefix = false;
                    break;
                }
            }

            if (!validPrefix) continue;

            // Calculate remaining available characters for index i and beyond
            vector<int> remCount(26, 0);
            for (int c = 0; c < 26; ++c) {
                remCount[c] = totalCount[c] - prefixCount[c];
            }

            // Look for the smallest character > target[i] to place at position i
            int targetCharIndex = target[i] - 'a';
            for (int c = targetCharIndex + 1; c < 26; ++c) {
                if (remCount[c] > 0) {
                    // Valid split found! Build the result string
                    string ans = target.substr(0, i);
                    ans += (char)('a' + c);
                    remCount[c]--;

                    // Fill remaining positions with leftover characters in ascending order
                    for (int r = 0; r < 26; ++r) {
                        while (remCount[r] > 0) {
                            ans += (char)('a' + r);
                            remCount[r]--;
                        }
                    }

                    return ans;
                }
            }
        }

        return "";
    }
};