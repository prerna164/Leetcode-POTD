/*
Problem: Remove Methods From Projects
Link: LeetCode 3282 / Problem 3286 - Find the Remaining Methods

Difficulty: Medium
Tags: Depth-First Search, Breadth-First Search, Graph, Directed Graph

Intuition:
We are given `n` methods represented as nodes in a directed graph.
An edge `a -> b` in `invocations` means method `a` invokes method `b`.
Method `k` contains a bug. Any method reachable from `k` (directly or indirectly) is considered suspicious.

Key Rules:
1. Identify all suspicious methods: Find all nodes reachable starting from node `k`.
2. Check removal eligibility: Suspicious methods can ONLY be removed if NO non-suspicious method invokes ANY suspicious method.
3. If any non-suspicious method has a directed edge pointing to a suspicious method, we CANNOT remove any suspicious method (return all nodes `0` to `n-1`).
4. Otherwise, remove all suspicious methods and return all remaining non-suspicious methods.

---

Approach:

1. Graph Construction:
   * Build an adjacency list `adj` representing directed edges `a -> b`.

2. Find Suspicious Methods (DFS/BFS):
   * Traversal from node `k` marks all reachable nodes as suspicious using a boolean array `isSuspicious`.

3. Check Outer Invocations:
   * Iterate over all edges `[u, v]` in `invocations`:
     - If `!isSuspicious[u]` and `isSuspicious[v]`, then a non-suspicious method invokes a suspicious one.
     - In this case, no methods can be removed. Return all methods `[0, 1, ..., n-1]`.

4. Collect Remaining Methods:
   * If the condition is met, collect all nodes `i` where `!isSuspicious[i]`.

---

⏱ Time Complexity:
O(N + E)

* Graph construction takes O(E) where E = invocations.length.
* DFS/BFS traversal takes O(N + E) time.
* Checking edge conditions takes O(E) time.
* Total Runtime: O(N + E) linear time.

Space Complexity:
O(N + E) Auxiliary Space

* Adjacency list requires O(N + E) space.
* `isSuspicious` boolean array and recursion stack require O(N) space.
*/

#include <vector>
#include <numeric>
#include <iostream>

using namespace std;

class Solution {
private:
    void dfs(int u, const vector<vector<int>>& adj, vector<bool>& isSuspicious) {
        isSuspicious[u] = true;
        for (int v : adj[u]) {
            if (!isSuspicious[v]) {
                dfs(v, adj, isSuspicious);
            }
        }
    }

public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        vector<vector<int>> adj(n);
        for (const auto& edge : invocations) {
            adj[edge[0]].push_back(edge[1]);
        }

        // Step 1: Identify all suspicious methods starting from k
        vector<bool> isSuspicious(n, false);
        dfs(k, adj, isSuspicious);

        // Step 2: Check if any non-suspicious method invokes a suspicious method
        for (const auto& edge : invocations) {
            int u = edge[0];
            int v = edge[1];
            if (!isSuspicious[u] && isSuspicious[v]) {
                // Cannot remove suspicious methods; return all methods
                vector<int> allMethods(n);
                iota(allMethods.begin(), allMethods.end(), 0);
                return allMethods;
            }
        }

        // Step 3: Collect all non-suspicious methods
        vector<int> remaining;
        for (int i = 0; i < n; ++i) {
            if (!isSuspicious[i]) {
                remaining.push_back(i);
            }
        }

        return remaining;
    }
};