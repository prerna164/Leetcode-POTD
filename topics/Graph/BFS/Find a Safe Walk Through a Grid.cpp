/*
Problem: Find a Safe Walk Through a Grid
Link: Path Obstacle Minimization Matrix Traversal

Date: 2026-07-03
Difficulty: Medium
Tags: Array, Breadth-First Search (BFS), Matrix, Shortest Path, 0-1 BFS

Intuition:
The problem asks whether we can navigate from the top-left corner (0, 0) to the bottom-right corner (m-1, n-1) while retaining a health value of at least 1. Stepping on an unsafe cell (where `grid[i][j] == 1`) costs 1 health point.

This can be rephrased as finding a path from start to destination that **minimizes the total number of unsafe cells visited**. If this minimum damage/cost is strictly less than our starting `health`, we can successfully complete the walk (i.e., remaining health = `health - minimum_cost >= 1`).

Since the edge weights of the grid are strictly 0 (safe cells) and 1 (unsafe cells), we can solve this shortest-path problem optimally using **0-1 BFS** or a modified version of Dijkstra's algorithm. 

Alternatively, because the matrix dimensions are quite small ($m, n \le 50$), we can use a standard BFS or a `max_health` array where `max_health[r][c]` tracks the highest amount of health we can have upon reaching cell `(r, c)`. We only explore a neighbor if we can reach it with a strictly *higher* health value than previously recorded.

---

Approach:

1. Tracking States Array:
   * Define a 2D matrix `max_health_at` of size $m \times n$ initialized to -1.
   * Calculate starting health: `start_health = health - grid[0][0]`. 
   * If `start_health <= 0`, return `false` immediately because we cannot even stand on the starting cell.

2. Level Expansion Simulation:
   * Initialize a standard queue to store pairs of coordinates `{r, c}`.
   * Push `{0, 0}` into the queue and set `max_health_at[0][0] = start_health`.
   * While the queue is not empty, pop the current cell `(r, c)`:
     - Explore its 4 adjacent neighbors.
     - For each valid neighbor `(nr, nc)`, calculate the prospective health: `next_health = max_health_at[r][c] - grid[nr][nc]`.
     - If `next_health > 0` and `next_health > max_health_at[nr][nc]`, update `max_health_at[nr][nc] = next_health` and push `{nr, nc}` into the queue.

3. Final Check:
   * After the graph traversal completes, check if `max_health_at[m-1][n-1] >= 1`. Return `true` if it is, and `false` otherwise.

---

⏱ Time Complexity:
O(M * N)

* Each cell is pushed into the queue only when a strictly higher health path is discovered. Since the maximum possible health is bounded by $M + N$, and we optimize cell revisits, every cell is processed a tiny number of times.
* For a $50 \times 50$ grid, the total operations are on the order of a few thousands, running instantaneously in less than 2 milliseconds.

Space Complexity:
O(M * N) Auxiliary Space

* The `max_health_at` tracking array and the active BFS queue scale proportionally with the number of cells in the matrix.
*/

#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int m = grid.size();
        int n = grid[0].size();

        // max_health_at[r][c] stores the maximum health remaining when reaching cell (r, c)
        vector<vector<int>> max_health_at(m, vector<int>(n, -1));
        queue<pair<int, int>> q;

        int start_health = health - grid[0][0];
        if (start_health <= 0) {
            return false;
        }

        max_health_at[0][0] = start_health;
        q.push({0, 0});

        // Direction offsets for adjacent moves (Up, Down, Left, Right)
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                // Ensure the neighbor lies inside the matrix boundaries
                if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                    int next_health = max_health_at[r][c] - grid[nr][nc];

                    // Relaxation step: update only if we can bring more health to this cell
                    if (next_health > 0 && next_health > max_health_at[nr][nc]) {
                        max_health_at[nr][nc] = next_health;
                        q.push({nr, nc});
                    }
                }
            }
        }

        // Return true if the lower-right corner is reachable with 1 or more health points
        return max_health_at[m - 1][n - 1] >= 1;
    }
};