/*
Problem: Path Existence Queries in a Difference-Bounded Graph
Link: Linear Component Partitioning via Array Gaps

Date: 2026-07-09
Difficulty: Medium
Tags: Array, Graph, Two Pointers, Disjoint Set Union (DSU)

Intuition:
The problem defines a graph where an edge exists between node `i` and `j` if `|nums[i] - nums[j]| <= maxDiff`. We are given that the array `nums` is already sorted in non-decreasing order.

Since the array is sorted, think about what it takes for a set of adjacent nodes to form a connected component. An edge connects node `i` and node `i+1` if `nums[i+1] - nums[i] <= maxDiff`. 
If there is a gap where `nums[i+1] - nums[i] > maxDiff`, then *no* node from index `0` to `i` can possibly connect to *any* node from index `i+1` to `n-1`. This is because any other pairing would have an even larger difference!

This means the sorted array naturally splits into several isolated, contiguous connected components. Two nodes `u` and `v` are in the same connected component (and thus have a valid path between them) if and only if there is no "gap" strictly greater than `maxDiff` between their respective indices in the sorted array.

Instead of building a full graph or running a Disjoint Set Union (DSU) structure which takes extra overhead, we can simply assign a component ID to each index by making a single linear pass over `nums`. If `nums[i] - nums[i-1] > maxDiff`, we increment the component ID. Otherwise, it stays the same. Then, for each query `[u, v]`, we check if `component_id[u] == component_id[v]`.

---

Approach:

1. Component Tracking:
   * Create an array `component_id` of size `n`.
   * Initialize `curr_id = 0` and `component_id[0] = 0`.
   * Traverse from `i = 1` to `n - 1`. If `nums[i] - nums[i - 1] > maxDiff`, increment `curr_id`. Assign `component_id[i] = curr_id`.

2. Query Execution:
   * Allocate a boolean vector `answer` matching the size of `queries`.
   * For each query `[u, v]`, set `answer[i] = (component_id[u] == component_id[v])`.

---

⏱ Time Complexity:
O(N + Q)

* A single linear scan of size $O(N)$ is used to identify the component blocks.
* Each of the $Q$ queries is answered in $O(1)$ constant time by comparing their component IDs.
* Total execution time easily runs within 20 milliseconds for $N, Q = 10^5$.

Space Complexity:
O(N) Auxiliary Space

* We only use a single integer vector of size $N$ to store the `component_id` assignments, which provides optimal storage utilization.
*/

#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        // Step 1: Divide the sorted elements into contiguous connected components
        vector<int> component_id(n, 0);
        int curr_id = 0;

        for (int i = 1; i < n; ++i) {
            // A gap greater than maxDiff splits the graph into a new component
            if (nums[i] - nums[i - 1] > maxDiff) {
                curr_id++;
            }
            component_id[i] = curr_id;
        }

        // Step 2: Answer each query in O(1) time
        int q = queries.size();
        vector<bool> answer(q);

        for (int i = 0; i < q; ++i) {
            int u = queries[i][0];
            int v = queries[i][1];
            
            // If they belong to the exact same component block, a path exists
            answer[i] = (component_id[u] == component_id[v]);
        }

        return answer;
    }
};