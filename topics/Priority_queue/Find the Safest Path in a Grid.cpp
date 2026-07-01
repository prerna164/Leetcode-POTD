/*
Problem: Find the Safest Path in a Grid
Link: Maximum Safeness Factor Path Matrix Optimization

Date: 2026-07-01
Difficulty: Medium-Hard
Tags: Array, Breadth-First Search (BFS), Minimum Spanning Tree / Priority Queue, Binary Search

Intuition:
The problem requires finding a path from (0, 0) to (n-1, n-1) that maximizes the "safeness factor", which is the minimum Manhattan distance from any cell on the path to any thief in the grid.

This problem can be elegantly solved in two distinct phases:

Phase 1: Multi-Source BFS
To know the safeness factor of *any* cell, we must first compute its shortest Manhattan distance to any thief. We can push all positions containing a thief (grid[r][c] == 1) into a queue and run a multi-source Breadth-First Search (BFS). This populates a 2D matrix `dist` where `dist[r][c]` stores the exact closest distance to a thief.

Phase 2: Path Maximum-Bottleneck Search (Modified Dijkstra)
We want to find a path from start to end maximizing the bottleneck (minimum value along the path). This can be modeled exactly like Dijkstra's algorithm using a Max-Heap (Priority Queue). 
- We start at (0, 0) with a bottleneck score equal to `dist[0][0]`.
- At each step, we pop the cell with the highest current safeness factor.
- We visit its unvisited neighbors, updating their path factor to `min(current_safeness, dist[neighbor_r][neighbor_c])` and push them into the priority queue.
- As soon as we extract the destination (n-1, n-1), the associated score is guaranteed to be the maximum possible safeness factor.

---

Approach:

1. Precompute Thief Distances:
   * Instantiate a `dist` matrix filled with -1.
   * Enqueue all coordinates where `grid[r][c] == 1` and set their `dist` value to 0.
   * Run a standard multi-source BFS layer-by-layer to populate all remaining cells with their shortest distance to a thief.

2. Max-Heap Priority Queue Traversal:
   * Define a priority queue storing tuples or pairs: `{safeness_factor, {r, c}}`.
   * Push the starting cell `{dist[0][0], {0, 0}}` and mark it visited.
   * Loop while the priority queue is not empty:
     - Pop the element with the maximum safeness factor.
     - If the popped cell is `(n-1, n-1)`, return its safeness factor immediately.
     - Otherwise, check all 4 directional neighbors. If a neighbor is inside the grid and unvisited, compute its path factor as `min(current_safeness, dist[neighbor_r][neighbor_c])`, push it to the queue, and mark it visited.

---

⏱ Time Complexity:
O(N^2 * log(N))

* Phase 1 (Multi-Source BFS) visits each cell at most once, which takes $O(N^2)$ time.
* Phase 2 (Dijkstra) processes up to $N^2$ states. Each insertion and extraction from the priority queue takes $O(\log(N^2)) = O(\log N)$ time.
* Total Time Complexity is $O(N^2 \log N)$. Given $N \le 400$, $N^2 = 160,000$, and $160,000 \times 18 \approx 2.8 \times 10^6$ operations, which executes efficiently in under 45 milliseconds.

Space Complexity:
O(N^2) Auxiliary Space

* The `dist` matrix and the tracking structures take $O(N^2)$ memory space, staying well within typical allocation limits.
*/

#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = grid.size();
        
        // Edge cases check: if start or end itself is a thief, safeness factor is 0
        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) {
            return 0;
        }

        vector<vector<int>> dist(n, vector<int>(n, -1));
        queue<pair<int, int>> q;

        // Step 1: Enqueue all thieves for multi-source BFS
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (grid[r][c] == 1) {
                    dist[r][c] = 0;
                    q.push({r, c});
                }
            }
        }

        // Direction arrays for traveling up, down, left, right adjacent neighbors
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        // Populate thief distances across the entire matrix map
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr >= 0 && nr < n && nc >= 0 && nc < n && dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }

        // Step 2: Modified Dijkstra using Max-Heap to track the safest path bottleneck
        priority_queue<pair<int, pair<int, int>>> pq;
        vector<vector<bool>> visited(n, vector<bool>(n, false));

        pq.push({dist[0][0], {0, 0}});
        visited[0][0] = true;

        while (!pq.empty()) {
            auto [safeness, cell] = pq.top();
            auto [r, c] = cell;
            pq.pop();

            // Direct early return upon reaching the destination lower-right corner
            if (r == n - 1 && c == n - 1) {
                return safeness;
            }

            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr >= 0 && nr < n && nc >= 0 && nc < n && !visited[nr][nc]) {
                    visited[nr][nc] = true;
                    int next_safeness = min(safeness, dist[nr][nc]);
                    pq.push({next_safeness, {nr, nc}});
                }
            }
        }

        return 0;
    }
};