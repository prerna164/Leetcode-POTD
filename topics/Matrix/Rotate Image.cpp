/*
Problem: Rotate Image (90 Degrees Clockwise)
Link: LeetCode 48

Date: 2026-05-04
Difficulty: Medium
Tags: Array, Math, Matrix

🧠 Intuition:

Rotating a matrix by 90 degrees clockwise manually is easy to visualize but 
tricky to code "in-place" without a helper matrix. However, there is a 
geometric pattern we can exploit:

A 90-degree clockwise rotation is equivalent to:
1. Transposing the matrix (swapping rows with columns).
2. Reversing each row.

Example for a 3x3 matrix:
Original:
1 2 3
4 5 6
7 8 9

Step 1: Transpose (swap matrix[i][j] with matrix[j][i])
1 4 7
2 5 8
3 6 9

Step 2: Reverse each row
7 4 1
8 5 2
9 6 3

This matches the expected 90-degree clockwise rotation. By doing it this way, 
 we avoid complex "four-way swaps" and maintain O(1) extra space.

--------------------------------------------------------

⚙️ Approach:

1. Transpose:
   Iterate through the matrix using nested loops. To avoid swapping elements 
   twice (which would put them back in their original place), the inner loop 
   should start from the current row index (`j = i`). Swap `matrix[i][j]` 
   with `matrix[j][i]`.

2. Reverse:
   Iterate through each row of the transposed matrix and reverse the elements. 
   In C++, we can use the built-in `std::reverse` function or a simple 
   two-pointer swap.

--------------------------------------------------------

⏱ Time Complexity:

O(N²)

- Transposing takes O(N²/2) swaps.
- Reversing each row takes O(N * N/2) swaps.
- Total operations are proportional to the number of elements in the matrix.

📦 Space Complexity:

O(1)

- The transformation is done entirely in-place by swapping existing elements. 
- No additional data structures are used.

*/

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();

        // Step 1: Transpose the matrix
        // We only iterate over the upper triangle to swap with the lower triangle
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }

        // Step 2: Reverse each row
        for (int i = 0; i < n; i++) {
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};