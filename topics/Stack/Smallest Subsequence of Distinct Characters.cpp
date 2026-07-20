/*
Problem: Smallest Subsequence of Distinct Characters
Link: https://leetcode.com/problems/smallest-subsequence/

Date: 2026-07-20
Difficulty: Medium
Tags: String, Stack, Greedy, Monotonic Stack

Intuition:
The goal is to build the lexicographically smallest subsequence that contains all unique characters exactly once. 
To achieve the smallest alphabetical order, we want smaller characters to appear as early as possible. We can construct the result character by character using a monotonic stack-like approach (implemented here via a `std::string`).

As we iterate through the string, if we encounter a character that is smaller than the last character we added to our result, we should consider removing that last character. However, we can only safely remove it if we are certain it appears again later in the string (so we don't permanently lose a unique character). 

By tracking the last occurrence index of each character and maintaining a visited set, we can greedily pop larger characters out of the way whenever a smaller character arrives, provided those larger characters have duplicates remaining down the line.

---

Approach:

1. Frequency Tracking:
   * Perform an initial pass over the string to record the last occurrence index of every character.

2. Monotonic Stack Construction:
   * Maintain a `visited` array to keep track of characters already included in the active result.
   * Iterate through the string character by character. If a character is already marked as `visited`, skip it to avoid duplicates.
   * While the active result is not empty, the current character is lexicographically smaller than the last character in the result, AND the last character in the result appears again later in the string:
     * Mark the last character as unvisited.
     * Pop it off the end of the result.
   * Append the current character to the result and mark it as visited.

3. Finalization:
   * Return the result string.

---

⏱ Time Complexity:
O(N)

* Finding the last occurrence takes a single pass over the string of size $N$, which is $O(N)$ time.
* In the main loop, each character is pushed onto and popped from the result string at most once. Thus, the inner while loop executes at most $N$ times across the entire runtime.
* Total time complexity is strictly linear, $O(N)$.

Space Complexity:
O(1) Auxiliary Space

* The `last_occurrence` and `visited` arrays use a fixed size of 26 elements, which scales as $O(1)$ constant space.
* The output string itself holds at most 26 unique characters, taking $O(1)$ extra space.
*/

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    string smallestSubsequence(string s) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        // Step 1: Record the last occurrence index of each character
        vector<int> last_occurrence(26, 0);
        for (int i = 0; i < s.length(); ++i) {
            last_occurrence[s[i] - 'a'] = i;
        }

        // Step 2: Track if a character is already present in the current result sequence
        vector<bool> visited(26, false);
        string result = ""; // Acting as a monotonic stack

        // Step 3: Process each character greedily
        for (int i = 0; i < s.length(); ++i) {
            char c = s[i];

            // If the character is already included, maintain unique constraints and skip
            if (visited[c - 'a']) {
                continue;
            }

            // Pop elements from the result if they are larger than the current character
            // and will appear again later in the remaining substring
            while (!result.empty() && c < result.back() && last_occurrence[result.back() - 'a'] > i) {
                visited[result.back() - 'a'] = false;
                result.pop_back();
            }

            // Append the optimal character and mark it as visited
            result.push_back(c);
            visited[c - 'a'] = true;
        }

        return result;
    }
};