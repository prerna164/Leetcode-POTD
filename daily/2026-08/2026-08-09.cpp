/*
Problem: Stone Game II
Link: LeetCode 1140 - Stone Game II

Difficulty: Medium
Tags: Array, Dynamic Programming, Math, Game Theory

Intuition:
We are given an array `piles` where each element represents the number of stones in a pile.
Alice and Bob take turns taking $X$ piles from the front, where $1 \le X \le 2M$, and after taking $X$ piles, $M$ updates to $\max(M, X)$. Initially, $M = 1$.

Let `dp[i][M]` represent the maximum stones the CURRENT player can collect starting from pile index `i` with current state `M`.

For a given state $(i, M)$:
1. Total remaining stones from index `i` to the end can be calculated using a suffix sum: `suffixSum[i]`.
2. If the current player can take ALL remaining piles ($i + 2M \ge N$), they should greedily take them all, yielding `suffixSum[i]` stones.
3. Otherwise, if they choose to take $X$ piles ($1 \le X \le 2M$), the opponent will be left with state $(i + X, \max(M, X))$.
   - The opponent will play optimally to get `dp[i + X][max(M, X)]` stones.
   - Therefore, the current player receives:
     `suffixSum[i] - dp[i + X][max(M, X)]`
4. The current player will pick $X$ to maximize their share.

---

Approach:

1. Precompute Suffix Sums:
   * Create a `suffixSum` array where `suffixSum[i]` holds the total sum of stones from index `i` to $N - 1$.

2. Dynamic Programming / Memoization:
   * Use a 2D memoization table `memo[i][M]`.
   * Base Case: If $i + 2M \ge N$, return `suffixSum[i]`.
   * Transitions: Loop $X$ from $1$ to $2M$, computing `suffixSum[i] - solve(i + X, max(M, X))` and storing the maximum result.

3. Result:
   * Call `solve(0, 1)` and return the maximum stones Alice can collect.

---

⏱ Time Complexity:
O(N^3)

* State space is defined by index `i` ($0 \le i < N$) and parameter `M` ($1 \le M \le N$). Total states = $O(N^2)$.
* For each state, we iterate $X$ up to $2M \le 2N$, which takes $O(N)$ operations.
* Total Runtime: $O(N^3)$. Given $N \le 100$, $100^3 = 10^6$ operations, which runs easily within milliseconds.

Space Complexity:
O(N^2) Auxiliary Space

* Space required for the `memo` table of size $N \times N$.
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
private:
    int n;
    vector<int> suffixSum;
    vector<vector<int>> memo;

    int solve(int i, int m) {
        // Base case: If remaining piles can all be taken in one turn
        if (i + 2 * m >= n) {
            return suffixSum[i];
        }

        if (memo[i][m] != -1) {
            return memo[i][m];
        }

        int maxStones = 0;
        for (int x = 1; x <= 2 * m; ++x) {
            int nextM = max(m, x);
            int opponentStones = solve(i + x, nextM);
            int currentStones = suffixSum[i] - opponentStones;
            maxStones = max(maxStones, currentStones);
        }

        return memo[i][m] = maxStones;
    }

public:
    int stoneGameII(vector<int>& piles) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        n = piles.size();
        suffixSum.assign(n, 0);
        memo.assign(n, vector<int>(n + 1, -1));

        // Precompute suffix sums
        suffixSum[n - 1] = piles[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            suffixSum[i] = suffixSum[i + 1] + piles[i];
        }

        return solve(0, 1);
    }
};