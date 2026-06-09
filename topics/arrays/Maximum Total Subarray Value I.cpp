/*
Problem: Maximum Total Subarray Value I
Link: Custom Subarray Value Maximization

Date: 2026-06-09
Difficulty: Medium
Tags: Array, Greedy

Intuition:
The problem asks us to choose exactly `k` non-empty subarrays and maximize the sum of their values, where the value of a subarray is defined as `max(subarray) - min(subarray)`. 
Crucially, the problem states that subarrays may overlap and the exact same subarray can be chosen more than once.

Let's find the absolute maximum value (`globalMax`) and the absolute minimum value (`globalMin`) across the entire `nums` array. 
Suppose `globalMax` is located at index `i` and `globalMin` is located at index `j`. We can construct a single subarray spanning from `min(i, j)` to `max(i, j)`. This single subarray is guaranteed to contain both `globalMax` and `globalMin`. Therefore:
  Value of this subarray = globalMax - globalMin

Since any other subarray can at most have a maximum element equal to `globalMax` and a minimum element equal to `globalMin`, the value of any subarray in `nums` is mathematically bounded by `globalMax - globalMin`. 

Since we can choose the exact same subarray multiple times, the optimal strategy is to simply choose the subarray containing both the global maximum and the global minimum exactly `k` times. The maximum possible total value is therefore:
  Total Value = k * (globalMax - globalMin)

---

Approach:

1. Initialization:
   * Keep track of the absolute minimum element using a variable `globalMin` initialized to the maximum possible integer.
   * Keep track of the absolute maximum element using a variable `globalMax` initialized to the minimum possible integer.

2. Linear Scan:
   * Iterate through the array `nums` exactly once.
   * Update `globalMin` with the minimum value encountered so far.
   * Update `globalMax` with the maximum value encountered so far.

3. Calculate and Return:
   * Calculate the difference between `globalMax` and `globalMin`.
   * Multiply this difference by `k` and cast the result to a `long long` to prevent potential integer overflow issues.
   * Return the computed maximum total value.

---

⏱ Time Complexity:
O(N)

* We perform a single sequential loop over the array `nums` of size N to find the maximum and minimum elements.
* Inside the loop, finding the min and max takes O(1) operations.
* For the maximum constraint of N = 5 * 10^4, the execution finishes in under a millisecond.

Space Complexity:
O(1)

* The algorithm relies strictly on a few scalar tracking variables (`globalMin`, `globalMax`).
* No auxiliary structures, vectors, or additional dynamic storage are used, yielding a constant space footprint.
*/

#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>

using namespace std;

class Solution {
public:
    long long maxTotalValue(vector<int>& nums, int k) {
        // Optimize standard standard I/O streams for competitive programming speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int globalMin = INT_MAX;
        int globalMax = INT_MIN;

        // Find the global extreme boundaries in a single pass
        for (int num : nums) {
            if (num < globalMin) globalMin = num;
            if (num > globalMax) globalMax = num;
        }

        // Multiply the maximum possible single subarray value by k
        // Cast to long long to ensure it doesn't overflow
        return (long long)k * (globalMax - globalMin);
    }
};