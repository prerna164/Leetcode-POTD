/*
Problem: Concatenate Non-Zero Digits and Multiply by Sum
Link: Digit Processing String Math Simulation

Date: 2026-07-07
Difficulty: Easy
Tags: Math, Simulation, String

Intuition:
The problem requires us to filter out all zeros from a number, combine the remaining digits into a new number $x$, find the sum of these digits, and return $x \times \text{sum}$.

Since $n \le 10^9$, we can easily extract its digits by converting the integer to a string or by using standard modulo (`% 10`) and division (`/ 10`) arithmetic. 
1. If we use string manipulation, we parse the digits from left to right. We can build the new number $x$ and accumulate the sum of digits simultaneously.
2. If $n = 0$ or contains only zeros, $x = 0$ and the sum will be $0$. The product will be $0$.
3. Since $x$ can grow up to $10^9 - 1$ and the sum can be up to $9 \times 9 = 81$, the product $x \times \text{sum}$ can easily fit within a 64-bit integer (`long long`).

---

Approach:

1. Base Condition check:
   * If $n == 0$, return 0 immediately.

2. Digit Parsing Loop:
   * Convert $n$ to a string representation to preserve the original order naturally from left to right.
   * Initialize `x = 0` and `digit_sum = 0`.
   * Loop through each character `c` in the string:
     - Convert `c` to its integer digit value `digit = c - '0'`.
     - If `digit != 0`:
       - Append it to $x$: `x = x * 10 + digit`.
       - Add it to the cumulative sum: `digit_sum += digit`.

3. Result Generation:
   * Return the product `x * digit_sum`.

---

⏱ Time Complexity:
O(log_10(N))

* Converting the number to a string takes time proportional to the number of digits, which is at most 10 iterations for $N \le 10^9$.
* The linear loop through these digits runs in $O(\log_{10} N)$ constant iterations, executing in less than 1 millisecond.

Space Complexity:
O(log_10(N)) Auxiliary Space

* The space is dominated by the string representation of $n$, which holds at most 10 characters, maintaining an entirely negligible memory footprint.
*/

#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
    long long sumAndMultiply(int n) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        if (n == 0) {
            return 0;
        }

        string s = to_string(n);
        long long x = 0;
        long long digit_sum = 0;

        // Extract non-zero digits preserving their original sequence configuration order
        for (char c : s) {
            int digit = c - '0';
            if (digit != 0) {
                x = x * 10 + digit;
                digit_sum += digit;
            }
        }

        return x * digit_sum;
    }
};