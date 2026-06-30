/*
Problem: Number of Substrings Containing All Three Characters
Link: Sliding Window Substring Counting

Date: 2026-06-30
Difficulty: Medium
Tags: Hash Table, String, Sliding Window, Two Pointers

Intuition:
The problem asks us to find the number of substrings that contain at least one occurrence of the characters 'a', 'b', and 'c'. 

Instead of checking every single substring, which would take $O(N^2)$ time, we can use a sliding window / two-pointer approach or track the last seen positions of each character.

Let's use the **last seen position** approach:
As we iterate through the string with an index `i` (representing the end of our valid substring):
1. We keep track of the most recent index where we saw 'a', 'b', and 'c'. Let these be stored in a tracking array or variables.
2. If we have seen all three characters at least once, the smallest index among the three last-seen positions represents the start of the shortest valid substring ending at `i`. Let this be `min_idx = min({last['a'], last['b'], last['c']})`.
3. Any substring starting from index 0, 1, 2, ..., up to `min_idx` and ending at `i` will guaranteed contain all three characters. Thus, there are exactly `min_idx + 1` valid substrings that end precisely at index `i`.

By summing up `min_idx + 1` for all indices `i` where all three characters are present, we can find the total count in a single linear pass.

---

Approach:

1. Tracking array initialization:
   * Maintain a vector `last_seen(3, -1)` to store the latest index of 'a', 'b', and 'c' (mapped to indices 0, 1, and 2 respectively).
   * Initialize a variable `total_substrings = 0`.

2. Linear Sweep:
   * Loop through the string `s` from `i = 0` to `n - 1`.
   * Update the last seen position of the current character: `last_seen[s[i] - 'a'] = i`.
   * Check if all three characters have been seen at least once by verifying if `min({last_seen[0], last_seen[1], last_seen[2]}) != -1`.
   * If true, add `min({last_seen[0], last_seen[1], last_seen[2]}) + 1` to `total_substrings`.

3. Return result:
   * Return the accumulated `total_substrings` count.

---

⏱ Time Complexity:
O(N)

* We scan the string of length N exactly once.
* At each position, finding the minimum of 3 numbers takes $O(1)$ constant time.
* Total Time Complexity scales perfectly linearly, executing well within 4 milliseconds for $N = 5 \times 10^4$.

Space Complexity:
O(1) Auxiliary Space

* The memory footprint is strictly bounded by a 3-element tracking array, using an incredibly small, flat, and optimal amount of constant storage.
*/

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int numberOfSubstrings(string s) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        // Store the last seen indices of 'a', 'b', and 'c' respectively
        vector<int> last_seen(3, -1);
        int total_substrings = 0;
        int n = s.length();

        for (int i = 0; i < n; ++i) {
            // Update the index snapshot for the current character
            last_seen[s[i] - 'a'] = i;

            // If all three characters have been encountered at least once
            if (last_seen[0] != -1 && last_seen[1] != -1 && last_seen[2] != -1) {
                // The number of valid substrings ending at index i is determined by 
                // the furthest left bottleneck character index + 1
                int min_idx = min({last_seen[0], last_seen[1], last_seen[2]});
                total_substrings += (min_idx + 1);
            }
        }

        return total_substrings;
    }
};
+