/*
Problem: Number of Paths with Max Score
Link: Grid Backward Dynamic Programming Matrix

Date: 2026-07-05
Difficulty: Hard
Tags: Dynamic Programming, Matrix

Intuition:
We need to move from the bottom-right corner 'S' to the top-left corner 'E' maximizing the sum of numeric characters collected along the path, while also counting how many distinct paths achieve this maximum sum.
Since the allowed moves are only Up, Left, and Up-Left (diagonally), this is a classic Directed Acyclic Graph (DAG) state progression problem that can be handled efficiently with Dynamic Programming.

To align nicely with standard iterative DP, we can reverse the perspective and compute from 'E' (top-left) down to 'S' (bottom-right), or compute backwards from 'S' to 'E'. Let's build a grid DP starting backwards from 'S' (at $n-1, n-1$) to 'E' (at $0, 0$).

For any cell $(r, c)$:
- If `board[r][c] == 'X'`, it's an obstacle, so it remains unreachable.
- The cell can receive transitions from three valid directions: 
  1. Down: $(r+1, c)$
  2. Right: $(r, c+1)$
  3. Diagonal Down-Right: $(r+1, c+1)$

Let `dp_sum[r][c]` be the maximum score achievable from 'S' to $(r, c)$.
Let `dp_count[r][c]` be the number of distinct paths achieving that maximum score.

For a cell $(r, c)$, we look at its three possible source neighbors. We find the maximum score among those neighbors that are actually reachable. 
- If a neighbor is reachable, its max score + the current cell's numeric value forms a candidate sum.
- If this candidate sum is strictly greater than our current best `dp_sum[r][c]`, we update the sum and overwrite the path count with the neighbor's path count.
- If it is exactly equal, we add the neighbor's path count to `dp_count[r][c]` modulo $10^9 + 7$.

---

Approach:

1. Initialization:
   * Let $n$ be the board length.
   * Create `dp_sum` initialized to 0 and `dp_count` initialized to 0.
   * Set base case at the start: `dp_count[n-1][n-1] = 1`.

2. Bottom-up Processing:
   * Iterate backwards from $r = n-1$ down to 0, and $c = n-1$ down to 0.
   * If `dp_count[r][c] == 0`, it means this cell cannot be reached from 'S'; skip processing its transitions to avoid extending invalid paths.
   * For the current cell $(r, c)$, evaluate its 3 target neighbors: $(r-1, c)$, $(r, c-1)$, and $(r-1, c-1)$.
   * For each valid neighbor that is not an obstacle 'X':
     - Calculate `value = (board[nr][nc] == 'E') ? 0 : (board[nr][nc] - '0')`.
     - Update `dp_sum[nr][nc]` and `dp_count[nr][nc]` based on whether `dp_sum[r][c] + value` is greater than or equal to the existing best score at the neighbor.

3. Result Extraction:
   * Look at the final destination `(0, 0)`. If `dp_count[0][0] == 0`, return `[0, 0]`. Otherwise, return `[dp_sum[0][0], dp_count[0][0]]`.

---

⏱ Time Complexity:
O(N^2)

* We look at each cell of the $N \times N$ matrix exactly once.
* For each cell, we perform a constant number of operations (checking 3 directions), which takes $O(1)$ time.
* For $N \le 100$, $N^2 = 10,000$, which finishes processing in less than 2 milliseconds.

Space Complexity:
O(N^2) Auxiliary Space

* The space is determined by the two tracking arrays `dp_sum` and `dp_count` of size $N \times N$.
*/

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = board.size();
        long long MOD = 1e9 + 7;

        // dp_sum[r][c] tracks the maximum score to reach cell (r, c) from 'S'
        vector<vector<int>> dp_sum(n, vector<int>(n, 0));
        // dp_count[r][c] tracks the number of paths achieving that maximum score
        vector<vector<int>> dp_count(n, vector<int>(n, 0));

        // Base case: starting at the bottom-right corner 'S'
        dp_count[n - 1][n - 1] = 1;

        // Direction offsets to move Up, Left, and Up-Left diagonally
        int dr[] = {-1, 0, -1};
        int dc[] = {0, -1, -1};

        // Traverse backwards from 'S' to 'E'
        for (int r = n - 1; r >= 0; --r) {
            for (int c = n - 1; c >= 0; --c) {
                // If this square cannot be reached from 'S', skip it
                if (dp_count[r][c] == 0 || board[r][c] == 'X') {
                    continue;
                }

                // Propagate forward to allowed neighbors
                for (int i = 0; i < 3; ++i) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];

                    // Check boundaries and handle obstacle avoidance
                    if (nr >= 0 && nc >= 0 && board[nr][nc] != 'X') {
                        int cell_value = (board[nr][nc] == 'E') ? 0 : (board[nr][nc] - '0');
                        int prospective_sum = dp_sum[r][c] + cell_value;

                        if (prospective_sum > dp_sum[nr][nc]) {
                            // Found a strictly better path to neighbor
                            dp_sum[nr][nc] = prospective_sum;
                            dp_count[nr][nc] = dp_count[r][c];
                        } else if (prospective_sum == dp_sum[nr][nc]) {
                            // Found an alternative path with the same maximum score
                            dp_count[nr][nc] = (dp_count[nr][nc] + dp_count[r][c]) % MOD;
                        }
                    }
                }
            }
        }

        // If the top-left corner 'E' is unreachable, return [0, 0]
        if (dp_count[0][0] == 0) {
            return {0, 0};
        }

        return {dp_sum[0][0], dp_count[0][0]};
    }
};