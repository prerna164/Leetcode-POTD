/*
Problem: Stone Game IV
Link: LeetCode 1510 - Stone Game IV

Difficulty: Hard
Tags: Math, Dynamic Programming, Game Theory

Intuition:
We are given `n` stones. Two players take turns removing any non-zero perfect square number of stones (1, 4, 9, 16, ...).
The player who cannot make a move (0 stones left) loses.

Let `dp[i]` be a boolean value representing whether the player whose turn it is with `i` stones remaining will WIN (`true`) or LOSE (`false`).

Game Theory Strategy:
- A state `i` is a WINNING state (`dp[i] = true`) if there exists AT LEAST ONE valid move (subtracting `k * k`) that leaves the remaining opponent in a LOSING state (`dp[i - k * k] == false`).
- A state `i` is a LOSING state (`dp[i] = false`) if ALL possible moves leave the remaining opponent in a WINNING state.

---

Approach:

1. Dynamic Programming Table:
   * Create a boolean DP array `dp` of size `n + 1`, initialized to `false`.
   * Base Case: `dp[0] = false` (a player starting with 0 stones cannot make a move and loses).

2. State Transitions:
   * Iterate `i` from `1` to `n`.
   * For each state `i`, test square numbers `k * k` where `k * k <= i`:
     - If `dp[i - k * k] == false`, it means by removing `k * k` stones, we force the opponent into a losing position!
     - Set `dp[i] = true` and `break` early.

3. Result:
   * Return `dp[n]`.

---

⏱ Time Complexity:
O(N * sqrt(N))

* Outer loop runs $N$ times.
* Inner loop runs at most $\sqrt{i}$ times for each $i$.
* Total iterations = $\sum_{i=1}^{N} \sqrt{i} \approx \frac{2}{3} N^{1.5}$.
* For $N = 10^5$, $(10^5)^{1.5} \approx 3.16 \times 10^7$ operations, which executes easily within standard 0.1s limits.

Space Complexity:
O(N) Auxiliary Space

* `dp` vector requires $O(N)$ space.
*/

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    bool winnerSquareGame(int n) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        // dp[i] represents if the current player can force a win starting with i stones
        vector<bool> dp(n + 1, false);

        for (int i = 1; i <= n; ++i) {
            for (int k = 1; k * k <= i; ++k) {
                if (!dp[i - k * k]) {
                    dp[i] = true;
                    break; // Found a winning move, no need to check further
                }
            }
        }

        return dp[n];
    }
};