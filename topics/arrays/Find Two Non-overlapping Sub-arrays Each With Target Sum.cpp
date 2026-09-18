/*
Problem: Find Two Non-overlapping Sub-arrays Each With Target Sum
Link: LeetCode 1477 - Find Two Non-overlapping Sub-arrays Each With Target Sum

Difficulty: Medium
Tags: Array, Hash Table, Binary Search, Sliding Window, Dynamic Programming, Prefix Sum

Intuition:
We need to find two non-overlapping sub-arrays that each sum to `target` such that the sum of their lengths is minimized.

Since all elements in `arr` are positive (`arr[i] >= 1`), we can find all valid sub-arrays with sum equal to `target` using either a Sliding Window or Prefix Sum + Hash Map in linear time.

To guarantee that the two sub-arrays are non-overlapping and maintain the minimum combined length:
1. Let `min_len[i]` store the minimum length of a valid sub-array ending at or before index `i`.
2. As we traverse the array from left to right, whenever we find a valid sub-array `arr[left...right]` with `sum == target`:
   - Its length is `curr_len = right - left + 1`.
   - If a valid sub-array with `sum == target` exists strictly before `left` (i.e., ending at or before `left - 1`), we can combine them!
   - Combined length = `curr_len + min_len[left - 1]`.
   - Update our global answer `ans = min(ans, curr_len + min_len[left - 1])`.
   - Update `min_len[right] = min(min_len[right - 1], curr_len)`.

Using sliding window works in $O(N)$ because all numbers are positive, which means the running sum is strictly monotonic.

---

Approach:

1. Initialization:
   * `n = arr.size()`.
   * `min_len` array of size `n` filled with `INF` (e.g., `1e9`).
   * `ans = INF`.
   * Sliding window pointers `left = 0`, `right = 0`, and running `current_sum = 0`.

2. Sliding Window Traversal:
   * Expand `right` pointer and add `arr[right]` to `current_sum`.
   * While `current_sum > target`, subtract `arr[left]` and increment `left`.
   * When `current_sum == target`:
     - Current sub-array length `curr_len = right - left + 1`.
     - Check if `left > 0` and `min_len[left - 1] != INF`.
     - If so, update `ans = min(ans, curr_len + min_len[left - 1])`.
     - Update minimum length seen so far at index `right`:
       `min_len[right] = min(left > 0 ? min_len[right - 1] : INF, curr_len)`.
   * If `current_sum != target`:
     - Carry forward `min_len[right] = (right > 0) ? min_len[right - 1] : INF`.

3. Return Result:
   * If `ans == INF`, return `-1` (fewer than 2 valid sub-arrays found).
   * Otherwise, return `ans`.

---

⏱ Time Complexity:
O(N)

* Both `left` and `right` pointers iterate across the array at most once.
* Total Runtime: $O(N)$ linear time.

Space Complexity:
O(N) Auxiliary Space

* `min_len` array of size `N`.
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = arr.size();
        const int INF = 1e9;

        // min_len[i] stores the minimum length of a valid sub-array ending at or before index i
        vector<int> min_len(n, INF);

        int ans = INF;
        int current_sum = 0;
        int left = 0;

        for (int right = 0; right < n; ++right) {
            current_sum += arr[right];

            // Shrink window if sum exceeds target
            while (current_sum > target && left <= right) {
                current_sum -= arr[left];
                left++;
            }

            // Found a sub-array with sum equal to target
            if (current_sum == target) {
                int curr_len = right - left + 1;

                // Check if a non-overlapping valid sub-array exists to the left
                if (left > 0 && min_len[left - 1] != INF) {
                    ans = min(ans, curr_len + min_len[left - 1]);
                }

                // Update min_len at index right
                int prev_min = (left > 0) ? min_len[right - 1] : INF;
                if (right > 0) {
                    min_len[right] = min(min_len[right - 1], curr_len);
                } else {
                    min_len[right] = curr_len;
                }
            } else {
                // Carry forward the best minimum length seen so far
                if (right > 0) {
                    min_len[right] = min_len[right - 1];
                }
            }
        }

        return ans >= INF ? -1 : ans;
    }
};