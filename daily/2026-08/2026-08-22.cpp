/*
Problem: Check Divisibility by Digit Sum and Product
Link: LeetCode 3622 - Check Divisibility by Digit Sum and Product

Difficulty: Easy
Tags: Math, Implementation

Intuition:
We need to determine if a positive integer `n` is divisible by the sum of its:
1. Digit Sum: The sum of all individual digits of `n`.
2. Digit Product: The product of all individual digits of `n`.

Let:
- `sum_digits` = sum of digits of `n`
- `product_digits` = product of digits of `n`
- `total_sum` = `sum_digits + product_digits`

If `n % total_sum == 0`, then `n` is divisible, so we return `true`. Otherwise, return `false`.

---

Approach:

1. Extract Digits:
   * Maintain `sum_digits = 0` and `product_digits = 1`.
   * Extract each digit using modulo 10 (`temp % 10`).
   * Add to `sum_digits` and multiply into `product_digits`.
   * Divide `temp` by 10 (`temp /= 10`).

2. Check Divisibility:
   * Calculate `total = sum_digits + product_digits`.
   * Return `n % total == 0`.

---

⏱ Time Complexity:
O(log10(N))

* The number of digits in `n` is at most 7 (since N <= 10^6).
* Processing takes at most 7 iterations, executing in O(1) constant time.

Space Complexity:
O(1) Auxiliary Space

* Uses only a few integer variables.
*/

#include <iostream>

using namespace std;

class Solution {
public:
    bool checkDivisibility(int n) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int sum_digits = 0;
        long long product_digits = 1;

        int temp = n;
        while (temp > 0) {
            int digit = temp % 10;
            sum_digits += digit;
            product_digits *= digit;
            temp /= 10;
        }

        long long total = sum_digits + product_digits;

        return (n % total == 0);
    }
};