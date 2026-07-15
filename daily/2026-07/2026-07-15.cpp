/*
Problem: GCD of Sums of First N Odd and Even Numbers
Link: Mathematical Sequence GCD Optimization

Date: 2026-07-15
Difficulty: Easy
Tags: Math, Number Theory

Intuition:
Let's analyze the mathematical formulas for the sum of the first $n$ positive odd and even numbers:
1. The sum of the first $n$ positive odd numbers (`sumOdd`) is a well-known arithmetic progression property:
   $$sumOdd = 1 + 3 + 5 + \dots + (2n - 1) = n^2$$

2. The sum of the first $n$ positive even numbers (`sumEven`) is given by:
   $$sumEven = 2 + 4 + 6 + \dots + 2n = 2 \times (1 + 2 + 3 + \dots + n) = 2 \times \frac{n(n + 1)}{2} = n(n + 1)$$

We need to find the Greatest Common Divisor (GCD) of these two sums:
   $$\gcd(sumOdd, sumEven) = \gcd(n^2, n(n + 1))$$

By factoring out $n$ from both terms using the property $\gcd(a \cdot k, b \cdot k) = k \cdot \gcd(a, b)$:
   $$\gcd(n^2, n(n + 1)) = n \cdot \gcd(n, n + 1)$$

Since $n$ and $n + 1$ are consecutive integers, they are always coprime, meaning $\gcd(n, n + 1) = 1$.
Therefore:
   $$\gcd(sumOdd, sumEven) = n \cdot 1 = n$$

The mathematical reduction simplifies the entire execution down to simply returning the input integer $n$ itself!

---

Approach:

1. Direct Formula Application:
   * The mathematical evaluation proves that $\gcd(sumOdd, sumEven)$ always equals $n$.
   * Directly return `n`.

---

⏱ Time Complexity:
O(1)

* The calculation takes absolute constant time because it completely bypasses explicit sequence summation loops and GCD divisions.

Space Complexity:
O(1) Auxiliary Space

* The operation runs fully in-place requiring zero memory allocations.
*/

#include <iostream>

using namespace std;

class Solution {
public:
    long long gcdOddEvenSums(int n) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        // Based on the mathematical reduction: GCD(n^2, n*(n+1)) = n
        return n;
    }
};