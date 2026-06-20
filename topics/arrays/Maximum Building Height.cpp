/*
Problem: Maximum Building Height
Link: Constrained Slope Optimization

Date: 2026-06-20
Difficulty: Hard
Tags: Array, Sorting, Greedy, Math

Intuition:
The problem asks us to find the maximum possible height of any building among $n$ buildings, given that building 1 has height 0, and the absolute height difference between any two adjacent buildings is at most 1. There are also specific upper bounds given for some buildings.

This is a structural slope optimization problem. The restriction $|h_i - h_j| \le |i - j|$ must hold for all pairs of buildings. This means any constraint on a building propagates to its neighbors, capping their maximum potential heights as well. 

We can solve this efficiently using a two-pass line sweep approach similar to the logic used in Dijkstra or the Pass-Filter propagation method:
1. Implicit Bounds: Add building 1 with a height of 0, and building $n$ with an initial restriction of $n - 1$ to simplify calculations.
2. Sort: Sort all restrictions by their building IDs.
3. Left-to-Right Pass: Propagate the restrictions from left to right. The maximum height of a building is limited by its left neighbor: 
   `r[i][1] = min(r[i][1], r[i-1][1] + (r[i][0] - r[i-1][0]))`
4. Right-to-Left Pass: Propagate restrictions from right to left. The maximum height of a building is similarly limited by its right neighbor:
   `r[i][1] = min(r[i][1], r[i+1][1] + (r[i+1][0] - r[i][0]))`

After both passes, the maximum height values recorded at each restricted index are fully resolved and optimized. For any two adjacent restricted buildings $A$ and $B$, the maximum peak height they can reach between them forms a triangular roof shape. The maximum peak between index $idx_A$ and $idx_B$ with optimized heights $h_A$ and $h_B$ can be calculated directly with the formula:
  $$\text{Peak Height} = \frac{h_A + h_B + (idx_B - idx_A)}{2}$$

---

Approach:

1. Base Configurations:
   * Insert the initial boundary condition `[1, 0]` into the restrictions list.
   * Sort the list based on the building IDs.
   * If the last building $n$ is not in restrictions, push `[n, n - 1]` to easily process the trailing end.

2. Double Pass Propagation:
   * Run a forward loop from `i = 1` to `m - 1` to adjust the maximum bounds using left neighbors.
   * Run a backward loop from `i = m - 2` down to 0 to adjust the maximum bounds using right neighbors.

3. Peak Peak Collection:
   * Iterate through every adjacent pair of restrictions. Compute the maximum middle peak using the mathematical midpoint formula and track the absolute maximum.

---

⏱ Time Complexity:
O(M log M)

* Let M be the length of the `restrictions` array.
* Sorting the restrictions dominates the timeline, requiring O(M log M) operations.
* The forward pass, backward pass, and peak scanning loops process the array linearly in O(M) time.
* Given $M \le 10^5$, this runs well within 25 milliseconds, completely bypassing the massive $n = 10^9$ constraint.

Space Complexity:
O(M) Auxiliary Space

* Space is needed to store the explicit boundaries within the `restrictions` vector. No large structures sizing up to $n$ are initialized.
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int maxBuilding(int n, vector<vector<int>>& restrictions) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        // Step 1: Add boundary base conditions
        restrictions.push_back({1, 0});
        sort(restrictions.begin(), restrictions.end());
        
        // Handle the last building boundary implicitly if not restricted
        if (restrictions.back()[0] != n) {
            restrictions.push_back({n, n - 1});
        }

        int m = restrictions.size();

        // Step 2: Forward pass (Left to Right propagation)
        for (int i = 1; i < m; ++i) {
            int dist = restrictions[i][0] - restrictions[i - 1][0];
            restrictions[i][1] = min(restrictions[i][1], restrictions[i - 1][1] + dist);
        }

        // Step 3: Backward pass (Right to Left propagation)
        for (int i = m - 2; i >= 0; --i) {
            int dist = restrictions[i + 1][0] - restrictions[i][0];
            restrictions[i][1] = min(restrictions[i][1], restrictions[i + 1][1] + dist);
        }

        // Step 4: Maximize peak heights between all adjacent restriction nodes
        int max_height = 0;
        for (int i = 0; i < m - 1; ++i) {
            int id1 = restrictions[i][0], h1 = restrictions[i][1];
            int id2 = restrictions[i + 1][0], h2 = restrictions[i + 1][1];
            
            // Mathematical peak formula between two constrained slope points
            int peak = (h1 + h2 + (id2 - id1)) / 2;
            max_height = max(max_height, peak);
        }

        return max_height;
    }
};