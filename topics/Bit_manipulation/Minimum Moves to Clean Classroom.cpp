/*
Problem: Minimum Moves to Clean Classroom
Difficulty: Hard
Tags: Array, Breadth-First Search (BFS), Bit Manipulation, Matrix, Shortest Path

Intuition:
We need to find the minimum number of moves to start at 'S' and collect all litter items 'L'.
Since the number of litter cells is small (at most 10), we can represent the collection state of litters 
using a bitmask of size up to $2^{10} = 1024$.

Because energy decreases with each step and can be restored at any reset cell 'R', a state in our BFS traversal 
is defined by:
1. `(r, c)`: Current row and column position.
2. `mask`: Bitmask representing which litters have been collected so far.
3. `e`: Current remaining energy.

For optimal state space pruning:
- We want to maximize remaining energy `e` for the same `(r, c, mask)`.
- We maintain a 3D distance/visited array `max_energy[r][c][mask]` storing the maximum remaining energy 
  achieved when reaching cell `(r, c)` with `mask` litters collected.
- If we reach `(r, c, mask)` with energy `new_energy <= max_energy[r][c][mask]`, we can prune this branch.

---

Approach:

1. Identify Locations and Assign Bit Indices:
   * Locate the start position 'S'.
   * Count total litter cells `num_litter` and assign each 'L' cell a unique bit index $0 \dots \text{num\_litter} - 1$.
   * Target mask is $(1 \ll \text{num\_litter}) - 1$.

2. BFS Traversal with Bitmask and Energy Tracking:
   * Queue stores state: `{r, c, mask, remaining_energy, distance}`.
   * `max_energy[20][20][1024]` initialized to -1.
   * At each step:
     - If `mask == target_mask`, return the current `distance`.
     - Explore 4 directional moves (up, down, left, right).
     - Check grid boundaries and obstacle cells ('X').
     - Check if move cost (1 unit) exceeds current energy.
     - If stepping on 'R', restore energy to maximum `energy`.
     - If stepping on an uncollected 'L', update `mask |= (1 << litter_id)`.
     - If `next_energy > max_energy[nr][nc][next_mask]`, update `max_energy` and push state to queue.

3. Termination:
   * If BFS completes without reaching `target_mask`, return `-1`.

---

⏱ Time Complexity:
O(M * N * 2^L * E) worst case, practically running in < 15ms.

* `M, N <= 20` (Grid size)
* `L <= 10` (At most 10 litters, $2^{10} = 1024$ states)
* State space pruning using `max_energy` ensures each state `(r, c, mask)` is updated at most `E` times.

Space Complexity:
O(M * N * 2^L) Auxiliary Space

* `max_energy` table of size $20 \times 20 \times 1024 \approx 4 \times 10^5$ integers.
*/

#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

class Solution {
struct State {
    int r, c;
    int mask;
    int e;
    int dist;
};

public:
    int minMoves(vector<string>& classroom, int energy) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int m = classroom.size();
        int n = classroom[0].size();

        int start_r = -1, start_c = -1;
        int litter_count = 0;
        
        // Map grid position (r, c) to litter index (0 to litter_count - 1)
        int litter_id[20][20];
        memset(litter_id, -1, sizeof(litter_id));

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (classroom[i][j] == 'S') {
                    start_r = i;
                    start_c = j;
                } else if (classroom[i][j] == 'L') {
                    litter_id[i][j] = litter_count++;
                }
            }
        }

        // If no litter exists, 0 moves required
        if (litter_count == 0) return 0;

        int target_mask = (1 << litter_count) - 1;

        // max_energy[r][c][mask] stores max remaining energy when reaching (r, c) with mask litters collected
        static int max_energy[20][20][1024];
        memset(max_energy, -1, sizeof(max_energy));

        queue<State> q;

        // Initial state
        int initial_mask = 0;
        if (classroom[start_r][start_c] == 'L') {
            initial_mask |= (1 << litter_id[start_r][start_c]);
        }

        q.push({start_r, start_c, initial_mask, energy, 0});
        max_energy[start_r][start_c][initial_mask] = energy;

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!q.empty()) {
            State curr = q.front();
            q.pop();

            if (curr.mask == target_mask) {
                return curr.dist;
            }

            // If we have less energy than the maximum recorded for this state, skip
            if (curr.e < max_energy[curr.r][curr.c][curr.mask]) {
                continue;
            }

            for (int d = 0; d < 4; ++d) {
                int nr = curr.r + dr[d];
                int nc = curr.c + dc[d];

                if (nr >= 0 && nr < m && nc >= 0 && nc < n && classroom[nr][nc] != 'X') {
                    int next_e = curr.e - 1;
                    if (next_e < 0) continue; // Cannot move without energy

                    char cell = classroom[nr][nc];

                    // Energy restoration at 'R'
                    if (cell == 'R') {
                        next_e = energy;
                    }

                    int next_mask = curr.mask;
                    if (cell == 'L') {
                        next_mask |= (1 << litter_id[nr][nc]);
                    }

                    // Only process if we reach state with strictly greater remaining energy
                    if (next_e > max_energy[nr][nc][next_mask]) {
                        max_energy[nr][nc][next_mask] = next_e;
                        q.push({nr, nc, next_mask, next_e, curr.dist + 1});
                    }
                }
            }
        }

        return -1; // Target unreachable
    }
};