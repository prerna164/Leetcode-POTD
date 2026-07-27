/*
Problem: Maximum Product of Three Numbers
Link: LeetCode - Maximum Product of Three Numbers

Date: 2026-07-26
Difficulty: Easy
Tags: Array, Math, Sorting

Intuition:
We are given an integer array `nums` of length at least 3, containing both positive and negative numbers.
We want to select three numbers such that their product is maximized.

Key Observations:
1. All Positive Numbers / Small Negatives:
   - The maximum product will naturally come from multiplying the three largest numbers in the array.
2. Large Negative Numbers Present:
   - Multiplying two negative numbers yields a positive number.
   - Therefore, multiplying the two smallest (most negative) numbers together with the largest positive number could potentially yield a greater product than multiplying the three largest numbers.

Thus, the maximum product is always the maximum of:
1. `max1 * max2 * max3` (the product of the three largest numbers)
2. `min1 * min2 * max1` (the product of the two smallest numbers and the largest number)

---

Approach:

1. One-Pass Search for Extremes:
   * Instead of sorting the array in O(N log N) time, we can find the three largest (`max1`, `max2`, `max3`) and two smallest (`min1`, `min2`) numbers in a single linear pass O(N).
   * Initialize `max1`, `max2`, `max3` to `INT_MIN` and `min1`, `min2` to `INT_MAX`.

2. Iterate & Update:
   * For each number `x` in `nums`:
     - Update top 3 maximums accordingly.
     - Update top 2 minimums accordingly.

3. Calculate & Return:
   * Return `max(max1 * max2 * max3, min1 * min2 * max1)`.

---

⏱ Time Complexity:
O(N)

* We iterate through the array `nums` of length N exactly once.
* Updating the five track variables takes constant O(1) time per element.

Space Complexity:
O(1) Auxiliary Space

* Requires only a constant amount of extra variables (`max1`, `max2`, `max3`, `min1`, `min2`).
*/

#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>

using namespace std;

class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int max1 = INT_MIN, max2 = INT_MIN, max3 = INT_MIN;
        int min1 = INT_MAX, min2 = INT_MAX;

        for (int x : nums) {
            // Update the top 3 maximums
            if (x >= max1) {
                max3 = max2;
                max2 = max1;
                max1 = x;
            } else if (x >= max2) {
                max3 = max2;
                max2 = x;
            } else if (x > max3) {
                max3 = x;
            }

            // Update the top 2 minimums
            if (x <= min1) {
                min2 = min1;
                min1 = x;
            } else if (x < min2) {
                min2 = x;
            }
        }

        return max(max1 * max2 * max3, min1 * min2 * max1);
    }
};