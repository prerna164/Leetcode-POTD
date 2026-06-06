/*
Problem: Left and Right Sum Differences
Link: Prefix Sum Difference Calculation

Date: 2026-06-06
Difficulty: Easy
Tags: Array, Prefix Sum, Simulation

Intuition:
The problem asks us to find the absolute difference between the sum of elements to the left of each index and the sum of elements to the right of that index. 

Instead of recomputing the left and right sums for every index from scratch (which would take O(N^2) time), we can maintain the total sum of the array. Let's observe the structural behavior at any index `i`:
1. `leftSum[i]` represents the sum of all elements from index `0` to `i-1`.
2. `rightSum[i]` represents the sum of all elements from index `i+1` to `n-1`.

Notice that the sum of the entire array can be broken down as: 
  `totalSum = leftSum[i] + nums[i] + rightSum[i]`

From this, we can easily derive `rightSum[i]` dynamically if we know `leftSum[i]` and the `totalSum`:
  `rightSum[i] = totalSum - leftSum[i] - nums[i]`

By scanning the array from left to right, we can build `leftSum[i]` iteratively by tracking a running total. This optimizes the approach to a single linear scan after calculating the initial total sum.

---

Approach:

1. Initialization:
   * Find the total sum of all elements in `nums` and store it in a variable `rightSumTotal`. Initially, before checking any index, the total sum of elements to the right of a virtual starting point is the sum of the entire array.
   * Initialize a variable `leftSumTotal` to `0`, representing the sum of elements to the left of the current index.
   * Create an array `answer` of the same size as `nums` to store the final results.

2. Iteration and Maintenance:
   * Loop through each element `nums[i]` from index `0` to `n-1`.
   * Since `rightSumTotal` currently holds the sum of elements from index `i` to the end, subtract the current element `nums[i]` from it. Now, `rightSumTotal` perfectly represents the sum of elements strictly to the right of index `i`.
   * Calculate the absolute difference `abs(leftSumTotal - rightSumTotal)` and store it in `answer[i]`.
   * Update `leftSumTotal` by adding the current element `nums[i]` to it so that it is accurately prepared for the next index.

3. Return Result: Once the loop completes, return the `answer` array.

---

⏱ Time Complexity:
O(N)

* We make one complete pass over the array to compute the total sum using `std::accumulate`.
* We make a second linear pass over the array of size N to calculate the differences and update our running balances.
* Since both operations are sequential, the time complexity remains perfectly linear, scaling effortlessly for the maximum constraint of N = 1000.

Space Complexity:
O(1) auxiliary space (excluding the output vector)

* The algorithm updates balances using scalar variables (`leftSumTotal`, `rightSumTotal`).
* Aside from the required output vector `answer` of size N, no additional vectors or auxiliary dynamic memory allocations are generated.
*/

#include <vector>
#include <numeric>
#include <cmath>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> leftRightDifference(vector<int>& nums) {
        // Optimize standard standard I/O streams for competitive programming speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = nums.size();
        vector<int> answer(n);

        int leftSumTotal = 0;
        int rightSumTotal = accumulate(nums.begin(), nums.end(), 0);

        for (int i = 0; i < n; ++i) {
            // Subtract the current element to get the sum of elements strictly to its right
            rightSumTotal -= nums[i];

            // Calculate the absolute difference
            answer[i] = abs(leftSumTotal - rightSumTotal);

            // Add the current element to the left sum for the next iteration
            leftSumTotal += nums[i];
        }

        return answer;
    }
};