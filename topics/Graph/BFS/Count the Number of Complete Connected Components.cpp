/*
Problem: Count the Number of Complete Connected Components
Link: Graph Component Topology Verification

Date: 2026-07-11
Difficulty: Medium
Tags: Graph, Breadth-First Search (BFS), Depth-First Search (DFS), Graph Theory

Intuition:
A connected component is complete if an undirected edge connects every single pair of its unique vertices. In graph theory, a complete graph (or clique) with V vertices contains exactly V * (V - 1) / 2 edges. 

Alternatively, we can look at the degrees of the vertices. In a complete component, each vertex must be directly connected to all other vertices in that component. This means every vertex in the component must have a degree exactly equal to V - 1. 

By summing up the degrees of all vertices belonging to a specific component, we obtain E_sum. Because each undirected edge is shared by two endpoints, E_sum counts every internal edge exactly twice. Therefore, for a component to be fully complete, it must strictly satisfy the following equality:
E_sum = V * (V - 1)

If a component passes this degree validation check, we can securely mark it as a complete connected component.

---

Approach:

1. Graph Representation:
   * Construct an adjacency list `adj` from the given `edges` array to efficiently access neighboring nodes.

2. Component Traversal (BFS):
   * Maintain a `visited` boolean array tracking explored vertices to prevent infinite loops and handle disconnected subgraphs.
   * For every unvisited node, trigger a standard Breadth-First Search (BFS) layer to isolate its connected component.
   * Inside the BFS queue loop, increment a counter `vertexCount` for each popped node and add its total degree (`adj[curr].size()`) to a tracking variable `totalEdgesSum`.

3. Structural Completeness Check:
   * Once the BFS queue goes empty, check the invariant rule: `totalEdgesSum == vertexCount * (vertexCount - 1)`. 
   * Increment our global complete component counter if the mathematical equality evaluates to true.

---

⏱ Time Complexity:
O(V + E)

* **Graph Construction**: Takes O(E) linear time to parse and append edges into the adjacency structures.
* **Component Extraction**: Each vertex and edge is visited exactly once via the global BFS loops, consuming O(V + E) processing time.
* Given the strict constraint N <= 50, the operations run near-instantaneously (under 1 millisecond).

Space Complexity:
O(V + E) Auxiliary Space

* The memory footprint is bounded linearly by the adjacency list holding V vector instances with a combined size of 2E element values.
* The BFS queue and `visited` list take at most O(V) auxiliary space allocations.
*/

#include <vector>
#include <queue>
#include <iostream>

using namespace std;

class Solution {
public:
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        // Step 1: Build the adjacency list representation of the graph
        vector<vector<int>> adj(n);
        for (const auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        vector<bool> visited(n, false);
        int completeComponentsCount = 0;

        // Step 2: Traverse each unvisited vertex to identify isolated components
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                int vertexCount = 0;
                int totalEdgesSum = 0;

                // Execute BFS traversal to sweep the current component space
                queue<int> q;
                q.push(i);
                visited[i] = true;

                while (!q.empty()) {
                    int curr = q.front();
                    q.pop();

                    vertexCount++;
                    totalEdgesSum += adj[curr].size(); // Accumulate degree counts

                    for (int neighbor : adj[curr]) {
                        if (!visited[neighbor]) {
                            visited[neighbor] = true;
                            q.push(neighbor);
                        }
                    }
                }

                // Step 3: Verify component completeness
                // In a complete subgraph, the sum of internal degrees must exactly equal V * (V - 1)
                if (totalEdgesSum == vertexCount * (vertexCount - 1)) {
                    completeComponentsCount++;
                }
            }
        }

        return completeComponentsCount;
    }
};