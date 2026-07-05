/*
Problem: Minimum Score of a Path Between Two Cities
Link: Graph Component Minimum Edge Selection

Date: 2026-07-04
Difficulty: Medium
Tags: Graph, Breadth-First Search (BFS), Depth-First Search (DFS), Union Find

Intuition:
The problem asks us to find a path from city 1 to city n that minimizes the "score", where the score of a path is defined as the minimum weight of any road traversed on that path. 

A crucial detail in the note states: "It is allowed for a path to contain the same road multiple times, and you can visit cities 1 and n multiple times along the path."

This completely simplifies the problem! Because we can traverse any edge multiple times and return back to our path, **we can visit absolutely any edge that belongs to the connected component containing city 1 and city n.** Since it's guaranteed that a path exists between 1 and n, they are part of the same connected component. 

Therefore, the problem reduces to:
Finding the **minimum weight of any edge** within the entire connected component that contains city 1 (and consequently city n).

We can use either a simple Breadth-First Search (BFS), Depth-First Search (DFS), or Disjoint Set Union (DSU) to explore all nodes reachable from city 1, and continuously keep track of the minimum road distance encountered along the way.

---

Approach:

1. Adjacency List Construction:
   * Build a standard bidirectional adjacency list from the `roads` array, where each entry stores the destination neighbor and the weight of the road.

2. Connected Component Exploration (BFS):
   * Initialize a `min_road_score = INT_MAX`.
   * Initialize a boolean tracking array `visited` of size $n + 1$ set to `false`.
   * Use a standard FIFO queue for BFS, beginning by pushing node `1` into it and setting `visited[1] = true`.

3. Traversal and Minimum Tracking:
   * While the queue is not empty, pop the current node `u`.
   * For each neighbor `v` connected to `u` via an edge of weight `w`:
     - Update `min_road_score = min(min_road_score, w)`.
     - If `v` has not been visited yet, mark it visited and push it into the queue.

4. Return Value:
   * Return the overall calculated `min_road_score`.

---

⏱ Time Complexity:
O(V + E)

* We traverse each reachable vertex $V$ and examine each connected edge $E$ exactly once during the BFS execution.
* Given $N \le 10^5$ and $roads.length \le 10^5$, the total operations are around $2 \times 10^5$, which executes in less than 15 milliseconds.

Space Complexity:
O(V + E) Auxiliary Space

* Storing the graph inside the adjacency list maps to $O(V + E)$ memory space. The `visited` array and BFS queue require $O(V)$ auxiliary space.
*/

#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <climits>

using namespace std;

class Solution {
public:
    int minScore(int n, vector<vector<int>>& roads) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        // Step 1: Construct the graph representation (Adjacency List)
        vector<vector<pair<int, int>>> adj(n + 1);
        for (const auto& road : roads) {
            int u = road[0];
            int v = road[1];
            int w = road[2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        int min_road_score = INT_MAX;
        vector<bool> visited(n + 1, false);
        queue<int> q;

        // Step 2: Start BFS traversal from city 1
        q.push(1);
        visited[1] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            // Step 3: Check all roads connected to the current node
            for (const auto& edge : adj[u]) {
                int v = edge.first;
                int w = edge.second;

                // Track the absolute minimum road weight found anywhere in this component
                min_road_score = min(min_road_score, w);

                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }

        return min_road_score;
    }
};