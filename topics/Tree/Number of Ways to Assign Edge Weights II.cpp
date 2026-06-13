/*
Problem: Number of Ways to Assign Edge Weights II
Link: Tree Path Parity Optimization with Multiple Queries

Date: 2026-06-13
Difficulty: Medium-Hard
Tags: Tree, Lowest Common Ancestor, Binary Lifting, Combinatorics, Math, Vector Optimization

Intuition:
The problem focuses on finding the number of valid weight assignments (1 or 2) for edges on a unique path between two nodes `u` and `v` across multiple independent queries. Let the number of edges on the path between `u` and `v` be L (the path length). Any edges outside this specific path are explicitly ignored per query.

For the total cost of the path to be odd, we need an odd number of edges to be assigned the weight 1. The remaining edges will automatically be assigned the weight 2 (which contributes 0 to the odd/even parity). This means we are summing the combinations: 
  Total Valid Configurations = C(L, 1) + C(L, 3) + C(L, 5) + ... 

By combinatorial identities, for any positive integer L, the sum of all odd-indexed binomial coefficients is exactly half of the total power set combinations (2^L):
  Total Valid Configurations = 2^(L - 1)

However, if L = 0 (the path from a node to itself), the sum is 0 (even), resulting in 0 valid configurations.

Therefore, the problem simplifies down to two clear goals for each query:
1. Find the distance L (number of edges) between nodes `u` and `v` efficiently. In a tree, the distance between two nodes can be computed using their depths and the depth of their Lowest Common Ancestor (LCA):
   L = depth[u] + depth[v] - 2 * depth[LCA(u, v)]
2. If L > 0, compute 2^(L - 1) modulo 10^9 + 7 using fast modular binary exponentiation. If L = 0, return 0.

---

Approach:

1. Graph Construction:
   * Represent the tree using an adjacency list `adj` built from the given `edges` array. Since the graph is undirected, add edges bidirectionally.

2. Tree Precomputation & Binary Lifting:
   * Perform a Depth First Search (DFS) starting from the root (Node 1) to compute the initial `depth` array and the first ancestor jump table (`up[node][0]`).
   * Fill the binary lifting sparse table `up[node][i]` which stores the (2^i)-th ancestor of each node. This allows us to jump up the tree in logarithmic time.

3. Answering Queries via LCA:
   * For each query `[u, v]`, if `u == v`, the distance is 0, so the answer is 0.
   * Otherwise, lift the deeper node to match the depth of the shallower node. Then, lift both nodes concurrently until their parent matches, which identifies the `LCA(u, v)`.
   * Calculate the path length `L` and evaluate `2^(L - 1) % (10^9 + 7)` via binary exponentiation.

---

⏱ Time Complexity:
O((N + Q) * log N)

* Building the adjacency list takes O(N) time since a tree with N nodes contains exactly N - 1 edges.
* The preprocessing DFS and binary lifting table initialization visits every node and fills log(N) states, taking O(N log N) time.
* Each of the Q queries takes O(log N) time to find the LCA and O(log L) time for fast binary exponentiation.
* The overall execution scales logarithmically per query, efficiently processing up to 10^5 nodes and queries within the time limit.

Space Complexity:
O(N * log N)

* The adjacency list requires O(N) space to store the tree connections.
* The binary lifting matrix `up` requires O(N log N) space to track ancestor states up to depth ceil(log2(N)).
* The `depth` array takes O(N) space.
* The recursive call stack for DFS requires up to O(N) space in the worst-case scenario of a completely skewed tree.
*/

#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
private:
    int n;
    int LOG;
    vector<vector<int>> adj;
    vector<vector<int>> up;
    vector<int> depth;

    // DFS function to precompute depths and immediate ancestors (2^0)
    void dfs(int node, int parent, int current_depth) {
        depth[node] = current_depth;
        up[node][0] = parent;
        
        // Populate binary lifting ancestors for the current node
        for (int i = 1; i < LOG; ++i) {
            if (up[node][i - 1] != -1) {
                up[node][i] = up[up[node][i - 1]][i - 1];
            } else {
                up[node][i] = -1;
            }
        }

        for (int neighbor : adj[node]) {
            if (neighbor != parent) {
                dfs(neighbor, node, current_depth + 1);
            }
        }
    }

    // Function to compute the Lowest Common Ancestor (LCA) using Binary Lifting
    int getLCA(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);

        // Bring both nodes to the same depth level
        int diff = depth[u] - depth[v];
        for (int i = 0; i < LOG; ++i) {
            if ((diff >> i) & 1) {
                u = up[u][i];
            }
        }

        if (u == v) return u;

        // Lift both nodes simultaneously until they are just below their LCA
        for (int i = LOG - 1; i >= 0; --i) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }

        return up[u][0];
    }

    // Helper function for binary modular exponentiation: (base^exp) % mod
    long long power(long long base, long long exp, long long mod) {
        long long res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp % 2 == 1) res = (res * base) % mod;
            base = (base * base) % mod;
            exp /= 2;
        }
        return res;
    }

public:
    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        n = edges.size() + 1;
        LOG = ceil(log2(n)) + 1;

        // Step 1: Allocate exact memory tracking structures
        adj.assign(n + 1, vector<int>());
        up.assign(n + 1, vector<int>(LOG, -1));
        depth.assign(n + 1, 0);

        // Populate tree connections bidirectionally (1-indexed base nodes)
        for (const auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        // Step 2: Trigger tree-wide traversal and precomputations from root Node 1
        dfs(1, -1, 0);

        long long MOD = 1000000007;
        vector<int> answer;
        answer.reserve(queries.size());

        // Step 3: Process queries sequentially
        for (const auto& query : queries) {
            int u = query[0];
            int v = query[1];

            // A path from a node to itself contains 0 edges -> 0 odd configurations possible
            if (u == v) {
                answer.push_back(0);
                continue;
            }

            int lca = getLCA(u, v);
            int pathLength = depth[u] + depth[v] - 2 * depth[lca];

            // Compute total valid configurations: 2^(pathLength - 1) % MOD
            long long ways = power(2, pathLength - 1, MOD);
            answer.push_back(ways);
        }

        return answer;
    }
};