/*
Problem: Maximum Length Substring With Two Occurrences
Link: LeetCode 3090 - Maximum Length Substring With Two Occurrences

Difficulty: Easy
Tags: Hash Table, String, Sliding Window

Intuition:
We need to find the maximum length of a contiguous substring where no character appears more than 2 times.

Key Observations:
1. Sliding Window / Two Pointers Strategy:
   - Expand a window `[left, right]` by moving the `right` pointer.
   - Maintain the count of each character using a frequency map or fixed-size array (`count` array of size 26).
   - If adding `s[right]` causes its frequency to exceed 2 (`count[s[right] - 'a'] > 2`), the window becomes invalid.
   - Shrink the window from the `left` by incrementing `left` and decrementing `count[s[left] - 'a']` until `count[s[right] - 'a'] <= 2`.
   - Record the maximum window length `right - left + 1` at each step.

---

Approach:

1. Frequency Array & Pointers:
   * Maintain an array `freq[26]` initialized to 0.
   * Initialize `left = 0` and `maxLen = 0`.

2. Expand Window:
   * Iterate `right` from `0` to `s.length() - 1`.
   * Increment `freq[s[right] - 'a']`.

3. Shrink Window if Invalid:
   * While `freq[s[right] - 'a'] > 2`, decrement `freq[s[left] - 'a']` and increment `left`.

4. Update Result:
   * Update `maxLen = max(maxLen, right - left + 1)`.

---

⏱ Time Complexity:
O(N)

* Both `left` and `right` pointers traverse the string of length `N` at most once.
* Array updates take O(1) time.
* Total Runtime: O(N) linear time.

Space Complexity:
O(1) Auxiliary Space

* Frequency array size is fixed at 26 (lowercase English letters).
*/

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int maximumLengthSubstring(string s) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        vector<int> freq(26, 0);
        int left = 0;
        int maxLen = 0;

        for (int right = 0; right < s.length(); ++right) {
            freq[s[right] - 'a']++;

            // Shrink window from the left if any character appears more than twice
            while (freq[s[right] - 'a'] > 2) {
                freq[s[left] - 'a']--;
                left++;
            }

            // Update max length of valid substring
            maxLen = max(maxLen, right - left + 1);
        }

        return maxLen;
    }
};