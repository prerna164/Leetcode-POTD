/*
Problem: Maximum Product of Two Digits
Link: LeetCode - Maximum Product of Two Digits

Date: 2026-07-25
Difficulty: Easy
Tags: Math, Greedy

Intuition:
We are given a positive integer `n` with constraints 10 <= n <= 10^9.
We want to find the maximum product of any two digits present in `n`.
Note that a digit can be used twice if and only if it appears at least twice in `n`.

Since all digits are non-negative integers (0 through 9), the product of two numbers is maximized when we choose the two largest available numbers.
Therefore, the problem simply reduces to:
1. Extract all digits from `n`.
2. Find the largest digit, `max1`.
3. Find the second largest digit, `max2`.
4. Return `max1 * max2`.

---

Approach:

1. Digits Extraction & Tracking:
   * Repeatedly extract the last digit of `n` using `n % 10` and then update `n /= 10`.
   * Keep track of the highest digit (`max1`) and the second highest digit (`max2`) encountered so far.

2. Updating Max Digits:
   * For each digit `d`:
     - If `d >= max1`, shift `max1` to `max2`, and set `max1 = d`.
     - Otherwise, if `d > max2`, update `max2 = d`.

3. Result Calculation:
   * Return `max1 * max2`.

---

⏱ Time Complexity:
O(log10(N))

* The number of digits in `n` is at most 10 (since n <= 10^9).
* We iterate through each digit once, performing constant O(1) operations.
* Overall Runtime: O(1) in practical terms.

Space Complexity:
O(1) Auxiliary Space

* Uses a few primitive variables (`max1`, `max2`, `d`) requiring constant extra space.
*/

#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int maxProduct(int n) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int max1 = 0;
        int max2 = 0;

        while (n > 0) {
            int d = n % 10;
            n /= 10;

            if (d >= max1) {
                max2 = max1;
                max1 = d;
            } else if (d > max2) {
                max2 = d;
            }
        }

        return max1 * max2;
    }
};