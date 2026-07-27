/*
Problem: Maximum Product of Two Elements in an Array
Link: LeetCode - Maximum Product of Two Elements in an Array

Date: 2026-07-27
Difficulty: Easy
Tags: Array, Math, Sorting

Intuition:
We are given an array of positive integers `nums` (with 1 <= nums[i] <= 10^3).
We need to pick two distinct indices `i` and `j` to maximize `(nums[i] - 1) * (nums[j] - 1)`.

Since all elements are positive (>= 1), `(nums[i] - 1)` is always non-negative.
To maximize the product of two non-negative terms, we should simply choose the two largest numbers in the array.

Therefore, the problem reduces to finding:
1. The largest number in the array (`max1`).
2. The second largest number in the array (`max2`).
3. Returning `(max1 - 1) * (max2 - 1)`.

---

Approach:

1. Single-Pass Iteration:
   * Keep track of two variables: `max1` and `max2`, both initialized to 0.
   * Iterate through each number `x` in `nums`:
     - If `x > max1`, the previous `max1` becomes the new `max2`, and `max1` is updated to `x`.
     - Else if `x > max2`, update `max2` to `x`.

2. Calculate Result:
   * Return `(max1 - 1) * (max2 - 1)`.

---

⏱ Time Complexity:
O(N)

* We perform a single linear pass over the array of size N.
* Comparisons and updates take constant O(1) time per element.

Space Complexity:
O(1) Auxiliary Space

* Uses only two scalar variables (`max1` and `max2`).
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int max1 = 0;
        int max2 = 0;

        for (int x : nums) {
            if (x > max1) {
                max2 = max1;
                max1 = x;
            } else if (x > max2) {
                max2 = x;
            }
        }

        return (max1 - 1) * (max2 - 1);
    }
};