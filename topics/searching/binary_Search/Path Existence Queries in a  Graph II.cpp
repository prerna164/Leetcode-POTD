/*
Problem: Path Existence Queries in a  Graph II
Link: Greedy Jump Optimization via Binary Lifting

Date: 2026-07-10
Difficulty: Hard
Tags: Array, Binary Lifting, Sparse Table, Binary Search, Graph

Intuition:
The problem specifies that an unweighted edge exists between two nodes if the absolute difference between their values is at most `maxDiff`. We need to calculate the *minimum distance* (shortest path) between pairs of nodes for multiple queries. 

Unlike a simple connectivity check, finding the exact shortest path requires tracking the optimal step hops. If we sort the unique values present in the graph, an optimal step to bridge the distance between a smaller value and a larger value is always a **greedy choice**: from any given value, we want to jump to the largest possible value that is still within `maxDiff` range. 

Because this greedy choice is deterministic and always leaps as far to the right as possible, we can model transitions through the unique sorted array as a directed functional graph. Simulating this step-by-step would yield a slow linear scanning time per query. Instead, we can optimize these greedy transitions using **Binary Lifting** (similar to finding the Lowest Common Ancestor in trees or solving the Jump Game). By precomputing jumps of power-of-two lengths ($2^0, 2^1, 2^2, \dots$), we can jump across the values exponentially fast.

---

Approach:

1. Value Compression and Sorting:
   * Isolate the unique numbers from `nums`, sort them, and remove duplicates. This leaves us with an ordered array `unique_vals` of size `m`.

2. Base Jump Initialization ($2^0$):
   * For every unique value index `i`, calculate the maximum reachable value $target = unique\_vals[i] + maxDiff$.
   * Use `upper_bound` to locate the largest value index `next_idx` that satisfies this constraint. If `next_idx > i`, then `up[i][0] = next_idx`, which sets our baseline greedy jump.

3. Sparse Table Expansion:
   * Populate the binary lifting table `up[i][j]` using the recurrence relation: `up[i][j] = up[up[i][j - 1]][j - 1]`. This means a jump of $2^j$ steps is equivalent to taking two consecutive jumps of $2^{j-1}$ steps.

4. Logarithmic Distance Evaluation:
   * For each query, match the indices of the values in `unique_vals`.
   * Iterate downwards from the maximum bit down to 0. If a jump of size $2^j$ keeps us strictly below the target destination, accumulate the jump count and shift our position.
   * Check if one final single step ($2^0$) bridges or overshoots to the exact destination to finalize the shortest distance.

---

⏱ Time Complexity:
$O((N + Q) \log N)$

* **Sorting & Compression**: Done in $O(N \log N)$ time.
* **Sparse Table Construction**: Requires $O(M \log M)$ operations, where $M \le N$.
* **Query Evaluation**: Each query executes a binary search look-up and a binary lifting traversal, which costs $O(\log M)$ time per query. For $Q$ queries, this computes efficiently within $O(Q \log N)$.

Space Complexity:
$O(N \log N)$ Auxiliary Space

* The space is dominated by the 2D sparse table matrix `up` of size $M \times \log_2(M)$, storing the precomputed exponential jump jumps.
*/

#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        // Step 1: Extract and sort unique values present in the graph
        vector<int> unique_vals = nums;
        sort(unique_vals.begin(), unique_vals.end());
        unique_vals.erase(unique(unique_vals.begin(), unique_vals.end()), unique_vals.end());
        
        int m = unique_vals.size();
        int max_log = log2(m) + 2;
        
        // up[i][j] stores the index reached from unique index i after 2^j greedy right jumps
        vector<vector<int>> up(m, vector<int>(max_log, -1));
        
        // Step 2: Initialize the base step jump (2^0 = 1 jump) for each element
        for (int i = 0; i < m; ++i) {
            long long target = (long long)unique_vals[i] + maxDiff;
            // Binary search the furthest unique element reachable within maxDiff boundary
            auto it = upper_bound(unique_vals.begin(), unique_vals.end(), target);
            int next_idx = distance(unique_vals.begin(), it) - 1;
            
            if (next_idx > i) {
                up[i][0] = next_idx;
            } else {
                up[i][0] = -1; 
            }
        }
        
        // Step 3: Build the binary lifting table for power-of-two hops
        for (int j = 1; j < max_log; ++j) {
            for (int i = 0; i < m; ++i) {
                if (up[i][j - 1] != -1) {
                    up[i][j] = up[up[i][j - 1]][j - 1];
                } else {
                    up[i][j] = -1;
                }
            }
        }
        
        // Lambda to compute the minimal jumps needed between two value indices
        auto getDistance = [&](int src, int dest) {
            if (src == dest) return 0;
            int jumps = 0;
            
            // Lift the index towards the destination using large chunks whenever possible
            for (int j = max_log - 1; j >= 0; --j) {
                if (up[src][j] != -1 && up[src][j] < dest) {
                    jumps += (1 << j);
                    src = up[src][j];
                }
            }
            
            // Check if one final single step reaches or spans past the destination
            if (up[src][0] != -1 && up[src][0] >= dest) {
                return jumps + 1;
            }
            
            return -1; // Node is completely isolated or blocked
        };
        
        // Step 4: Resolve queries using the precomputed jump paths
        vector<int> answer;
        answer.reserve(queries.size());
        
        for (const auto& query : queries) {
            int u = query[0];
            int v = query[1];
            
            if (u == v) {
                answer.push_back(0);
                continue;
            }
            
            int valU = nums[u];
            int valV = nums[v];
            
            if (valU == valV) {
                answer.push_back(1);
                continue;
            }
            
            // Translate the node values to their corresponding sorted unique positions
            int idxU = lower_bound(unique_vals.begin(), unique_vals.end(), valU) - unique_vals.begin();
            int idxV = lower_bound(unique_vals.begin(), unique_vals.end(), valV) - unique_vals.begin();
            
            // The graph is undirected, distance from U to V is identical to V to U
            if (idxU > idxV) {
                swap(idxU, idxV);
            }
            
            answer.push_back(getDistance(idxU, idxV));
        }
        
        return answer;
    }
};