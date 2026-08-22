/*
Problem: Kth Smallest Amount With Single Denomination Combination
Link: LeetCode 3116 - Kth Smallest Amount With Single Denomination Combination

Difficulty: Hard
Tags: Array, Math, Binary Search, Bit Manipulation, Inclusion-Exclusion Principle, Number Theory

Intuition:
We need to find the $k$-th smallest number that is a multiple of at least one coin in the given `coins` array.
Since we want to find a threshold value $X$ such that the total number of valid amounts $\le X$ is at least $k$, this function is monotonic, allowing us to perform **Binary Search on Answer**.

For a fixed value $X$:
- The count of multiples of a single coin $c$ that are $\le X$ is $\lfloor X / c \rfloor$.
- When combining multiple coins, simply summing their individual counts overcounts numbers that are multiples of multiple coins.
- By the **Inclusion-Exclusion Principle (IEP)**, the total number of unique multiples $\le X$ formed by any coin is:
  $$\text{Count}(X) = \sum_{S \subseteq \text{coins}, S \neq \emptyset} (-1)^{|S| - 1} \cdot \left\lfloor \frac{X}{\text{lcm}(S)} \right\rfloor$$

Given $N = \text{coins.length} \le 15$, there are at most $2^{15} - 1 = 32,767$ subsets, making IEP fast enough to evaluate for each binary search step.

---

Approach:

1. Binary Search Range:
   * Low: $1$
   * High: $k \cdot \min(\text{coins})$

2. Inclusion-Exclusion Function `count_multiples(X)`:
   * Iterate through all non-empty subsets of `coins` using bitwise masks ($1$ to $2^N - 1$).
   * Calculate the LCM of the subset.
   * If bit count is odd, add $\lfloor X / \text{lcm} \rfloor$; if even, subtract $\lfloor X / \text{lcm} \rfloor$.

3. Binary Search Step:
   * Compute `mid`.
   * If `count_multiples(mid) >= k`, record `ans = mid` and search the left half (`high = mid - 1`).
   * Otherwise, search the right half (`low = mid + 1`).

---

⏱ Time Complexity:
O(2^N * log(k * min_coin))

* $N \le 15 \implies 2^{15} \approx 3.2 \times 10^4$ operations per count evaluation.
* Binary search range is up to $2 \cdot 10^9 \cdot 25 = 5 \cdot 10^{10}$, taking $\approx 36$ binary search steps.
* Total Runtime: $36 \times 32767 \approx 1.1 \times 10^6$ operations, executing well within milliseconds.

Space Complexity:
O(1) Auxiliary Space

* Only constant extra space is used.
*/

#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
private:
    // Greatest Common Divisor helper
    long long gcd(long long a, long long b) {
        while (b) {
            a %= b;
            swap(a, b);
        }
        return a;
    }

    // Least Common Multiple helper
    long long lcm(long long a, long long b) {
        if (a == 0 || b == 0) return 0;
        return (a / gcd(a, b)) * b;
    }

    // Counts how many positive integers <= x are divisible by at least one coin in coins
    long long count_multiples(long long x, const vector<int>& coins) {
        int n = coins.size();
        long long total = 0;

        // Iterate through all non-empty subsets using bitmask
        for (int mask = 1; mask < (1 << n); ++mask) {
            long long current_lcm = 1;
            int bit_count = 0;

            for (int i = 0; i < n; ++i) {
                if ((mask >> i) & 1) {
                    bit_count++;
                    current_lcm = lcm(current_lcm, coins[i]);
                    // Break early if current_lcm exceeds x to prevent overflow
                    if (current_lcm > x) break;
                }
            }

            if (current_lcm <= x) {
                if (bit_count % 2 == 1) {
                    total += x / current_lcm;
                } else {
                    total -= x / current_lcm;
                }
            }
        }

        return total;
    }

public:
    long long findKthSmallest(vector<int>& coins, int k) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int min_coin = *min_element(coins.begin(), coins.end());

        long long low = 1;
        long long high = 1LL * min_coin * k;
        long long ans = high;

        // Binary search on answer
        while (low <= high) {
            long long mid = low + (high - low) / 2;

            if (count_multiples(mid, coins) >= k) {
                ans = mid;
                high = mid - 1; // Try to find a smaller valid amount
            } else {
                low = mid + 1;  // Need a larger amount to reach k multiples
            }
        }

        return ans;
    }
};