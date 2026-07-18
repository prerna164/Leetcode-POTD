/*
Problem: Find Greatest Common Divisor of Array Extremes
Link: Array Min-Max GCD Extraction

Date: 2026-07-18
Difficulty: Easy
Tags: Array, Math, Number Theory

Intuition:
The problem asks us to find the greatest common divisor (GCD) of only two specific elements from the array:
1. The smallest number (`min_element`).
2. The largest number (`max_element`).

We can achieve this in a single linear pass by finding both elements simultaneously using C++'s built-in `std::minmax_element` utility or a custom iterator loop. Once we have isolated the minimum and maximum values, we pass them directly into the standard `std::gcd` function (available since C++17 inside the `<numeric>` library) to compute the final answer.

---

Approach:

1. Extremes Isolation:
   * Use `std::minmax_element` to find the minimum and maximum elements in the array in a single traversal pass.

2. Greatest Common Divisor Evaluation:
   * Compute the GCD using the standard function `std::gcd(*result.first, *result.second)`.
   * Return the computed value.

---

⏱ Time Complexity:
O(N)

* A single pass over the array of size $N$ isolates the minimum and maximum values in $O(N)$ time.
* Finding the GCD of two numbers up to 1000 using the Euclidean algorithm takes logarithmic $O(\log(\text{MAX\_VAL}))$ time, which is roughly 10 operations.
* The execution is instantaneous, finishing in under 1 millisecond.

Space Complexity:
O(1) Auxiliary Space

* The operation runs fully in-place requiring zero extra memory allocations.
*/

#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

using namespace std;

class Solution {
public:
    int findGCD(vector<int>& nums) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        // Step 1: Find pointers to the minimum and maximum elements simultaneously
        auto extremes = minmax_element(nums.begin(), nums.end());
        int min_val = *extremes.first;
        int max_val = *extremes.second;

        // Step 2: Compute and return the greatest common divisor of the two boundary values
        return std::gcd(min_val, max_val);
    }
};