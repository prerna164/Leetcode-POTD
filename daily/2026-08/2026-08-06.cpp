/*
Problem: Smallest Divisible Digit Product I
Link: LeetCode - Smallest Number With Digit Product Divisible by t

Difficulty: Easy
Tags: Math, Enumeration

Intuition:
We need to find the smallest integer x >= n such that the product of the digits of x is divisible by t.

Given the constraints:
- 1 <= n <= 100
- 1 <= t <= 10

Since n is very small (at most 100), we can directly iterate upward starting from x = n and check whether the digit product of x is divisible by t.
Notice that any number containing '0' as a digit (e.g., 10, 20, 100, 101) will have a digit product of 0, which is divisible by any integer t >= 1. 
Therefore, we will find a valid number almost immediately (within at most 10 steps from n).

---

Approach:

1. Helper Function / Digit Product Check:
   * Write a helper function to compute the product of all digits of a given number `x`.
   * For `x`, extract each digit using `x % 10` and multiply them together.

2. Sequential Search:
   * Start a loop from `x = n`.
   * Check if `digitProduct(x) % t == 0`.
   * If true, return `x`.
   * Otherwise, increment `x` and repeat.

---

⏱ Time Complexity:
O(1)

* Given `n <= 100`, the search space is bounded by a tiny constant number of steps.
* The maximum number of digits of any checked number is at most 3, so computing the digit product takes standard constant time O(1).

Space Complexity:
O(1) Auxiliary Space

* Uses constant extra space for variables.
*/

#include <iostream>

using namespace std;

class Solution {
private:
    int getDigitProduct(int num) {
        int prod = 1;
        while (num > 0) {
            prod *= (num % 10);
            num /= 10;
        }
        return prod;
    }

public:
    int smallestNumber(int n, int t) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        while (true) {
            if (getDigitProduct(n) % t == 0) {
                return n;
            }
            n++;
        }
    }
};