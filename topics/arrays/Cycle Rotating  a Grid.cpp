/*
Problem: Cycle Rotating a Grid
Link: LeetCode 1914

Date: 2024-05-24
Difficulty: Medium
Tags: Array, Matrix, Simulation

🧠 Intuition:

The problem asks us to rotate a matrix layer by layer in a counter-clockwise direction. 
A key challenge is the rotation value 'k', which can be as large as 10^9.

The fundamental observation:
Each layer is an independent ring of numbers. Rotating a ring by its total number 
of elements brings it back to its original state. Therefore, we only need to 
perform (k % total_elements_in_layer) actual rotations.

To make the rotation logic simple:
1. "Unroll" each layer into a 1D linear array (flat list).
2. Perform the rotation on this 1D array using the modulo operator.
3. "Roll" the rotated 1D array back into its original 2D coordinates.

This "Flatten -> Rotate -> Reconstruct" strategy avoids complex index math 
associated with shifting values directly within the 2D grid while handling 
the boundary logic (top, right, bottom, left).

--------------------------------------------------------

⚙️ Approach:

1. Identify the number of layers: min(m, n) / 2.
2. For each layer (starting from the outermost layer = 0):

   a. Extract elements in Counter-Clockwise order:
      - Top Row: [layer][layer ... n-layer-2]
      - Right Column: [layer ... m-layer-2][n-layer-1]
      - Bottom Row: [m-layer-1][n-layer-1 ... layer+1]
      - Left Column: [m-layer-1 ... layer+1][layer]

   b. Calculate effective rotation: 
      - The number of elements in the current layer 'L' is its length.
      - net_k = k % L.

   c. Rotate:
      - Create a new list where every element i comes from (i + net_k) % L 
        of the unrolled list.

   d. Re-insert elements:
      - Traverse the same path used in step (a) and overwrite the grid values 
        using the rotated list.

3. Return the modified grid.

--------------------------------------------------------

⏱ Time Complexity:

O(m * n)

- We visit every cell in the matrix twice: once to read into a 1D list and 
  once to write back after rotation.
- Even if k is 10^9, the modulo operation makes the rotation O(L) per layer.
- Total operations are proportional to the number of elements.

📦 Space Complexity:

O(m + n)

- For each layer, we store its elements in a temporary 1D vector.
- The largest possible layer is the outermost one, which has 2*(m+n)-4 elements.
- We do not count the output grid as extra space as it is modified in-place 
  or required for the result.

*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int numLayers = min(m, n) / 2;

        for (int layer = 0; layer < numLayers; ++layer) {
            // 1. Extract the current layer elements in counter-clockwise order
            vector<int> elements;
            
            // Top row (left to right)
            for (int j = layer; j < n - layer - 1; ++j) elements.push_back(grid[layer][j]);
            // Right column (top to bottom)
            for (int i = layer; i < m - layer - 1; ++i) elements.push_back(grid[i][n - layer - 1]);
            // Bottom row (right to left)
            for (int j = n - layer - 1; j > layer; --j) elements.push_back(grid[m - layer - 1][j]);
            // Left column (bottom to top)
            for (int i = m - layer - 1; i > layer; --i) elements.push_back(grid[i][layer]);

            // 2. Calculate effective rotations
            int len = elements.size();
            int netK = k % len;
            
            if (netK == 0) continue;

            // 3. Rotate the 1D array (Counter-clockwise rotation)
            vector<int> rotated(len);
            for (int i = 0; i < len; ++i) {
                rotated[i] = elements[(i + netK) % len];
            }

            // 4. Put the rotated elements back into the grid
            int idx = 0;
            for (int j = layer; j < n - layer - 1; ++j) grid[layer][j] = rotated[idx++];
            for (int i = layer; i < m - layer - 1; ++i) grid[i][n - layer - 1] = rotated[idx++];
            for (int j = n - layer - 1; j > layer; --j) grid[m - layer - 1][j] = rotated[idx++];
            for (int i = m - layer - 1; i > layer; --i) grid[i][layer] = rotated[idx++];
        }

        return grid;
    }
};