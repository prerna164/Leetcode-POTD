/*
Problem: Shift 2D Grid
Link: https://leetcode.com/problems/shift-2d-grid/

Date: 2026-07-20
Difficulty: Easy
Tags: Array, Matrix, Simulation

Intuition:
Shifting elements in a 2D grid follows the same logic as shifting elements in a 1D array. 
If we flatten the 2D grid of size m x n into a single 1D array of size (m * n), a single shift 
operation shifts every element to the right by 1 index, wrapping the last element to the front.

Instead of performing the shifting process step-by-step k times, we can calculate the final 
flattened 1D index position for each cell directly. For an element at position (i, j), its 1D 
index is `i * n + j`. After k shifts, its new 1D index will be `(i * n + j + k) % (m * n)`. 
We can then reconstruct the shifted coordinates back into 2D format using division and modulo operations.

---

Approach:

1. Setup Matrix Parameters:
   * Retrieve the number of rows `m` and columns `n`. Total elements in the matrix equals `total_cells = m * n`.
   * Optimize the number of shifts by taking `k = k % total_cells` since shifting `total_cells` times results in the original grid.

2. Matrix Transformation:
   * Initialize a new result grid of size m x n.
   * Traverse every cell `(i, j)` in the original grid.
   * Calculate its absolute 1D index position: `current_1D_index = i * n + j`.
   * Compute the destination index after shift logic: `new_1D_index = (current_1D_index + k) % total_cells`.
   * Map the 1D destination index back to its 2D coordinates: `new_row = new_1D_index / n` and `new_col = new_1D_index % n`.
   * Place the element `grid[i][j]` into `result[new_row][new_col]`.

3. Finalization:
   * Return the updated `result` grid.

---

⏱ Time Complexity:
O(m * n)

* We iterate through each element of the m x n grid exactly once to place it into its respective position in the new grid.
* The execution speed is highly efficient and completes in O(M * N) total linear operations relative to matrix size.

Space Complexity:
O(m * n) Auxiliary Space

* We create a new 2D grid `result` of size m x n to store the shifted values and avoid overwriting data prematurely.
*/

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int m = grid.size();
        int n = grid[0].size();
        int total_cells = m * n;

        // Reduce redundant full rotations
        k = k % total_cells;

        // Create a result matrix initialized with the same dimensions
        vector<vector<int>> result(m, vector<int>(n));

        // Map every element from the original grid directly to its final destination
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                // Flatten 2D coordinate to 1D index
                int current_1d = i * n + j;
                
                // Calculate new 1D index after shifting k times
                int new_1d = (current_1d + k) % total_cells;
                
                // Convert back from 1D to 2D matrix coordinates
                int new_row = new_1d / n;
                int new_col = new_1d % n;
                
                result[new_row][new_col] = grid[i][j];
            }
        }

        return result;
    }
};