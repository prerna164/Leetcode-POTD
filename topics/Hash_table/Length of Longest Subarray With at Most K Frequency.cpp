/*
Problem: Length of Longest Subarray With at Most K Frequency
Link: LeetCode 2958 - Length of Longest Subarray With at Most K Frequency

Difficulty: Medium
Tags: Array, Hash Table, Sliding Window

Intuition:
We need to find the length of the longest contiguous subarray where no element appears more than `k` times.

Key Observations:
1. Contiguous Subarray Property:
   - A contiguous window `[left, right]` remains valid as long as `frequency[nums[right]] <= k`.
   - If adding `nums[right]` causes `frequency[nums[right]] > k`, the current window becomes invalid.
   
2. Sliding Window / Two Pointers Strategy:
   - Expand the window by moving the `right` pointer and updating element frequencies using a hash map.
   - When the frequency of `nums[right]` exceeds `k`, shrink the window from the `left` by incrementing `left` and decrementing `frequency[nums[left]]` until `frequency[nums[right]] <= k` again.
   - Record the maximum window size `right - left + 1` at each valid state.

---

Approach:

1. Maintain Frequency Map & Sliding Window Pointers:
   * Use an `unordered_map<int, int>` to track element frequencies in the current window.
   * Initialize `left = 0` and `maxLen = 0`.

2. Expand Window:
   * Iterate `right` from `0` to `nums.size() - 1`.
   * Increment `freq[nums[right]]`.

3. Shrink Window if Invalid:
   * While `freq[nums[right]] > k`, decrement `freq[nums[left]]` and increment `left`.

4. Update Result:
   * `maxLen = max(maxLen, right - left + 1)`.

---

⏱ Time Complexity:
O(N)

* Both `left` and `right` pointers traverse the array of length `N` at most once.
* Hash map lookups and updates take O(1) average time.
* Total Runtime: O(N) linear time.

Space Complexity:
O(N) Auxiliary Space

* `unordered_map` stores at most N distinct integers from `nums`.
*/

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        unordered_map<int, int> freq;
        int left = 0;
        int maxLen = 0;

        for (int right = 0; right < nums.size(); ++right) {
            freq[nums[right]]++;

            // Shrink window from the left if the frequency constraint is violated
            while (freq[nums[right]] > k) {
                freq[nums[left]]--;
                left++;
            }

            // Update max valid subarray length
            maxLen = max(maxLen, right - left + 1);
        }

        return maxLen;
    }
};