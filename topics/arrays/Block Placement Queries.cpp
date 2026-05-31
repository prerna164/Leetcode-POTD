/*/*
Problem: Block Placement Queries
Link: LeetCode 3161 - Block Placement Queries

Date: 2026-05-31
Difficulty: Hard
Tags: Array, Segment Tree, Binary Search, Ordered Set

Intuition:
Imagine the infinite number line as a long highway. Every time a query of Type 1 places an obstacle, a section of the highway is split into two smaller segments. 

To answer a query of Type 2 ("Can a block of size sz fit before x?"), we need to find the single largest open stretch of highway available anywhere between 0 and x. 

This maximum open stretch can hide in one of two places:
1. Between existing obstacles that are completely to the left of or at x.
2. The "tail" end, which is the gap between the very last obstacle before x and x itself.

Since obstacles are dynamically added, we need a data structure that can quickly tell us the maximum gap in a specific range [0, x] while letting us update gaps when new obstacles are placed. A Segment Tree combined with a balanced BST (std::set) is perfect for this because it can update and query ranges in logarithmic time O(log M).

---

Approach:

1. Coordinate Scope Tracking: First scan the queries to identify the highest coordinate bound `max_x`. This allows us to size our Segment Tree precisely to the problem's actual workspace range [0, max_x + 1].
2. Ordered Obstacle Tracking: Maintain a `std::set<int>` populated initially with the origin (0) and a bounding sentinel (`max_x + 1`). This allows us to instantly find the immediate neighbors (left and right) of any point using binary search (`std::upper_bound`).
3. Segment Tree for Gaps: The tree tracks coordinates. For any coordinate `i` where an obstacle exists, the tree stores the value `(distance to its left neighbor)`. If no obstacle exists at `i`, the value is 0. Internal tree nodes maintain the running maximum gap (`max`).
4. Query Processing:
   * Type 1 [1, x]: Locate its immediate neighbors in the set (`prev_obs` and `next_obs`). Update the segment tree at position `x` with its new left-gap (`x - prev_obs`), and update the position at `next_obs` with its shortened left-gap (`next_obs - x`). Insert `x` into the set.
   * Type 2 [2, x, sz]: Query the segment tree for the absolute maximum gap of any obstacle fully contained in the range [0, x]. Also calculate the dynamic "tail" gap from the last obstacle before `x` up to `x` itself. Take the maximum of both values and verify if it satisfies `>= sz`.

---

⏱ Time Complexity:
O(Q * log(M))

* We iterate through each of the Q queries sequentially.
* For Type 1 queries, lookups and insertions in the `std::set` take O(log Q), and point updates in the segment tree take O(log M), where M is the maximum coordinate value.
* For Type 2 queries, finding the previous obstacle takes O(log Q) and the segment tree range maximum query takes O(log M).
* Given that M <= min(5 * 10^4, 3 * Q), the maximum coordinate space is bounded tightly, ensuring highly optimized logarithmic operations per query.

Space Complexity:
O(M + Q)

* The Segment Tree array takes a static size of 4 * M space.
* The `std::set` holds at most Q elements to track unique active obstacles.
* Memory usage remains exceptionally flat and scales linearly with the input domain.
*/

#include <vector>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
private:
    vector<int> tree;
    int n;

    // Standard Segment Tree Point Update to modify maximum values
    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
            return;
        }
        int mid = start + (end - start) / 2;
        if (idx <= mid) {
            update(2 * node, start, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }

    // Standard Segment Tree Range Maximum Query
    int queryMax(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return 0; // Out of bounds segment returns identity element 0
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = start + (end - start) / 2;
        return max(queryMax(2 * node, start, mid, l, r),
                   queryMax(2 * node + 1, mid + 1, end, l, r));
    }

public:
    vector<bool> getResults(vector<vector<int>>& queries) {
        // Optimize standard input/output streams for execution environments
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int max_x = 0;
        for (const auto& q : queries) {
            max_x = max(max_x, q[1]);
        }
        
        // Size the coordinate boundaries appropriately
        n = max_x + 1;
        tree.assign(4 * n, 0);

        // Ordered container to easily track obstacle adjacencies
        set<int> obstacles;
        obstacles.insert(0);
        obstacles.insert(n); // Boundary sentinel representing the far-right end

        vector<bool> results;

        for (const auto& q : queries) {
            int type = q[0];
            if (type == 1) {
                int x = q[1];
                
                auto it = obstacles.upper_bound(x);
                int next_obs = *it;
                int prev_obs = *prev(it);

                // Update the gap for the newly inserted obstacle
                update(1, 0, n, x, x - prev_obs);
                
                // Readjust the gap for the next obstacle downstream
                update(1, 0, n, next_obs, next_obs - x);

                obstacles.insert(x);
            } else {
                int x = q[1];
                int sz = q[2];

                // Case A: Query the tree for largest gap between obstacles strictly within [0, x]
                int max_gap = queryMax(1, 0, n, 0, x);

                // Case B: Calculate the un-tracked dynamic trailing distance up to x
                auto it = obstacles.upper_bound(x);
                int prev_obs = *prev(it);
                max_gap = max(max_gap, x - prev_obs);

                // Evaluate if the maximum valid available block space meets the size requirement
                results.push_back(max_gap >= sz);
            }
        }

        return results;
    }
};*/