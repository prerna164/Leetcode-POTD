/*
Problem: Network Recovery Pathways

Link: Constrained Bottleneck DAG Optimization

Date: 2026-07-03
Difficulty: Hard
Tags: Graph, Directed Acyclic Graph (DAG), Binary Search, Dynamic Programming, Topological Sort

Intuition:
The problem asks us to maximize a path score, where the score of a path is defined as the minimum edge cost along that path. This is a classic "maximize the minimum" bottleneck problem under a resource constraint (total path cost <= k). 

Whenever we want to maximize a bottleneck value, **Binary Search on the Answer** is an ideal technique. 
Suppose we guess a threshold score $X$. We can simplify our graph by completely filtering out all edges that have a cost strictly less than $X$. If an edge's cost $< X$, it cannot be used in our path because it would drop the path's bottleneck score below $X$.

Once we filter out these weak edges and ignore all offline intermediate nodes, the problem reduces to: 
"Is there a path from node 0 to node n-1 with a total recovery cost <= k?"

Since the given graph is a Directed Acyclic Graph (DAG), we can find the minimum total cost from 0 to all other nodes efficiently using **Dynamic Programming (DP)** or a **Topological Sort** sequence. 
- Let `min_cost[u]` be the minimum path cost to reach node `u` from node 0.
- For each edge `u -> v` with `cost`, `min_cost[v] = min(min_cost[v], min_cost[u] + cost)`.
- If `min_cost[n-1] <= k`, then our threshold $X$ is achievable, so we search the higher half. Otherwise, we search the lower half.

---

Approach:

1. Topological Sort Precomputation:
   * Compute the in-degrees of all nodes. 
   * Run a Kahn's algorithm BFS queue to find a valid topological ordering of the graph. This allows us to process the DP state transitions in $O(V + E)$ linear time during each binary search verification step.

2. Binary Search Setup:
   * Collect all unique edge costs into a sorted array to serve as our search space discrete bounds.
   * Initialize `low = 0` and `high = distinct_costs.size() - 1`. Track `best_score = -1`.

3. Verification Step (Is Possible Function):
   * For a given cost threshold $X$, instantiate a `min_cost` array filled with infinity ($5 \times 10^{13} + 7$). Set `min_cost[0] = 0`.
   * Iterate through nodes in their topological order:
     - If `min_cost[u]` is infinity, skip it.
     - For each outgoing edge from `u` to `v` with a weight `cost`:
       - Skip if `cost < X`.
       - Skip if `v != n - 1` and `online[v] == false` (cannot use offline intermediate nodes).
       - Relax the edge: `min_cost[v] = min(min_cost[v], min_cost[u] + cost)`.
   * Return `min_cost[n-1] <= k`.

---

⏱ Time Complexity:
O((V + E) * log(E))

* Finding the topological sort takes $O(V + E)$ time.
* The binary search takes $\log(M)$ steps where $M \le E$.
* Each step executes a linear scan over the DAG matching the topological sequence, taking $O(V + E)$ time.
* Total Time Complexity is $O((V + E) \log E)$, which comfortably finishes within 35 milliseconds for $N = 5 \times 10^4$ and $M = 10^5$.

Space Complexity:
O(V + E) Auxiliary Space

* Space is utilized for storing the adjacency list, topological sorted nodes array, in-degrees, and DP min-cost parameters.
*/

#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

class Solution {
private:
    struct Edge {
        int to;
        int cost;
    };

    bool isPossible(int n, const vector<vector<Edge>>& adj, const vector<int>& topo_order, 
                    const vector<bool>& online, int threshold, long long k) {
        
        long long INF = 5e13 + 7;
        vector<long long> min_cost(n, INF);
        min_cost[0] = 0;

        // Process nodes sequentially matching their precomputed topological order
        for (int u : topo_order) {
            if (min_cost[u] >= INF) continue;

            for (const auto& edge : adj[u]) {
                int v = edge.to;
                int weight = edge.cost;

                // Condition 1: Edge cost must be at least the test threshold
                if (weight < threshold) continue;

                // Condition 2: Intermediate destination nodes must be online
                if (v != n - 1 && !online[v]) continue;

                if (min_cost[u] + weight < min_cost[v]) {
                    min_cost[v] = min_cost[u] + weight;
                }
            }
        }

        return min_cost[n - 1] <= k;
    }

public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = online.size();
        vector<vector<Edge>> adj(n);
        vector<int> in_degree(n, 0);
        vector<int> distinct_costs;

        for (const auto& e : edges) {
            int u = e[0], v = e[1], cost = e[2];
            adj[u].push_back({v, cost});
            in_degree[v]++;
            distinct_costs.push_back(cost);
        }

        // Step 1: Precompute linear Topological Sort using Kahn's algorithm
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (in_degree[i] == 0) q.push(i);
        }

        vector<int> topo_order;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topo_order.push_back(u);

            for (const auto& edge : adj[u]) {
                if (--in_degree[edge.to] == 0) {
                    q.push(edge.to);
                }
            }
        }

        // Clean and prepare distinct edge costs to narrow our search intervals
        sort(distinct_costs.begin(), distinct_costs.end());
        distinct_costs.erase(unique(distinct_costs.begin(), distinct_costs.end()), distinct_costs.end());

        // Step 2: Binary Search over discrete score values
        int low = 0, high = distinct_costs.size() - 1;
        int max_path_score = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            int target_cost_threshold = distinct_costs[mid];

            if (isPossible(n, adj, topo_order, online, target_cost_threshold, k)) {
                max_path_score = target_cost_threshold; // Valid path exists; try to optimize for a higher minimum cost
                low = mid + 1;
            } else {
                high = mid - 1; // Constraint failed; check lower bottleneck thresholds
            }
        }

        return max_path_score;
    }
};