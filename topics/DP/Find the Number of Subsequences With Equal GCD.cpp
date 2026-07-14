/*
Problem: Find the Number of Subsequences With Equal GCD
Link: https://leetcode.com/problems/find-the-number-of-subsequences-with-equal-gcd/description/?envType=daily-question&envId=2026-07-14

Date: 2026-07-14
Difficulty: Hard
Tags: Dynamic Programming, Math, Number Theory

Intuition:
The problem requires us to find the number of disjoint pairs of non-empty subsequences $(seq1, seq2)$ such that $\gcd(seq1) = \gcd(seq2)$.
Given the small constraints ($N \le 200$ and $nums[i] \le 200$), the maximum possible value of the GCD is 200. This highly localized value range strongly suggests a Dynamic Programming approach where we can track the running GCDs of both subsequences simultaneously.

Since the two subsequences must be index-disjoint, for each element $x$ in `nums`, we have three mutually exclusive choices:
1. Do not include $x$ in either subsequence.
2. Include $x$ in $seq1$.
3. Include $x$ in $seq2$.

Let `dp[g1][g2]` be the number of ways to form two disjoint subsequences with a current GCD of `g1` for the first subsequence and `g2` for the second subsequence. We can use a state of `0` to denote an empty subsequence. 

When transitioning with a new element $x$:
- Skipping $x$ retains the current state `(g1, g2)`.
- Adding $x$ to $seq1$ changes the state to `(g1 == 0 ? x : gcd(g1, x), g2)`.
- Adding $x$ to $seq2$ changes the state to `(g1, g2 == 0 ? x : gcd(g2, x))`.

Using a space-optimized rolling array for the DP states allows us to process the elements one by one efficiently.

---

Approach:

1. GCD Table Precomputation:
   * Build a 2D table `gcd_table[201][201]` to answer GCD queries in $O(1)$ constant time during the DP transitions.

2. DP Grid Instantiation:
   * Maintain a 2D matrix `dp[201][201]` initialized to zero. Set the base state `dp[0][0] = 1` (representing both subsequences being initially empty).

3. State Iteration and Transition:
   * Iterate through each number $x$ in `nums`.
   * Create a temporary matrix `next_dp` initialized with zero to perform safe state updates without cross-contamination.
   * For every existing reachable combination of `(g1, g2)`, calculate the three branch paths and add the count modulo $10^9 + 7$.
   * Replace `dp` with `next_dp` at the end of each item layer.

4. Accumulation:
   * Sum up `dp[g][g]` for all $1 \le g \le 200$ to get the total number of non-empty pairs with identical GCD values.

---

⏱ Time Complexity:
O(N * MAX_VAL^2)

* There are $N$ elements to process.
* For each element, we loop through all states of $g1$ and $g2$, where $0 \le g1, g2 \le 200$.
* The total operations are bounded roughly by $200 \times 201 \times 201 \approx 8 \times 10^6$, executing flawlessly in under 15 milliseconds.

Space Complexity:
O(MAX_VAL^2) Auxiliary Space

* We use two 2D tables of size $201 \times 201$ for the rolling DP state layers and one table of the same size for the precomputed GCD matrix, maintaining a very low and optimal memory boundary.
*/

#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
private:
    int gcd(int a, int b) {
        while (b) {
            a %= b;
            swap(a, b);
        }
        return a;
    }

public:
    int subsequencePairCount(vector<int>& nums) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int max_val = 200;
        long long MOD = 1000000007;

        // Step 1: Precompute GCD values to eliminate repeated runtime arithmetic overhead
        vector<vector<int>> gcd_table(max_val + 1, vector<int>(max_val + 1, 0));
        for (int i = 1; i <= max_val; ++i) {
            for (int j = 1; j <= max_val; ++j) {
                gcd_table[i][j] = gcd(i, j);
            }
        }

        // dp[g1][g2] stores the number of disjoint subsequence pairs with GCDs g1 and g2
        vector<vector<long long>> dp(max_val + 1, vector<long long>(max_val + 1, 0));
        dp[0][0] = 1; // Base case: both subsequences are empty

        // Step 2: Dynamic programming layer transformations
        for (int x : nums) {
            vector<vector<long long>> next_dp(max_val + 1, vector<long long>(max_val + 1, 0));

            for (int g1 = 0; g1 <= max_val; ++g1) {
                for (int g2 = 0; g2 <= max_val; ++g2) {
                    if (dp[g1][g2] == 0) continue;

                    long long current_ways = dp[g1][g2];

                    // Choice 1: Skip the current element entirely
                    next_dp[g1][g2] = (next_dp[g1][g2] + current_ways) % MOD;

                    // Choice 2: Add the element to the first subsequence (seq1)
                    int next_g1 = (g1 == 0) ? x : gcd_table[g1][x];
                    next_dp[next_g1][g2] = (next_dp[next_g1][g2] + current_ways) % MOD;

                    // Choice 3: Add the element to the second subsequence (seq2)
                    int next_g2 = (g2 == 0) ? x : gcd_table[g2][x];
                    next_dp[g1][next_g2] = (next_dp[g1][next_g2] + current_ways) % MOD;
                }
            }
            dp = move(next_dp);
        }

        // Step 3: Accumulate valid pairs where both subsequences are non-empty and have matching GCDs
        long long total_pairs = 0;
        for (int g = 1; g <= max_val; ++g) {
            total_pairs = (total_pairs + dp[g][g]) % MOD;
        }

        return total_pairs;
    }
};