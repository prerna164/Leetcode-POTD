/*
Problem: Rotate The Box
Link: LeetCode 1861

Date: 2026-05-06
Difficulty: Medium
Tags: Array, Two Pointers, Matrix, Simulation

🧠 Intuition:

At first glance, the problem looks like it requires two separate operations:

1. Rotate the box 90 degrees clockwise.
2. Apply gravity so that stones '#' fall downward.

A straightforward mind thinks:
"First rotate everything, then move each stone down."

But there is a smarter geometric observation:

After a 90-degree clockwise rotation, the downward gravity direction becomes
the RIGHT direction in the original matrix.

That means instead of:
- rotating first,
- then simulating gravity,

we can directly simulate gravity in every original row by pushing stones '#'
toward the right side inside each obstacle-separated segment.

Why obstacle-separated segment?

Because stones cannot pass through obstacles '*'. So every obstacle divides
the row into independent compartments, and inside each compartment all stones
will settle at the farthest right positions.

Once a stone or obstacle reaches its final horizontal resting place in the
original row, we immediately write it into its rotated position in the answer matrix.

This avoids doing two full simulations and gives us a much cleaner one-pass solution.

--------------------------------------------------------

⚙️ Approach:

1. Let:
   m = number of rows
   n = number of columns

2. Create an answer matrix `ans` of size n x m filled with '.'.

3. Traverse each row of `boxGrid` independently.

4. For every row, maintain a pointer `empty = n - 1`:
   This pointer stores the rightmost available location where the next stone
   can settle in the current obstacle-free segment.

5. Traverse columns from right to left:

   Case A: If current cell is an obstacle '*'
           - Obstacles do not move.
           - Place obstacle directly into rotated position.
           - Reset `empty = j - 1` because stones on the left cannot cross it.

   Case B: If current cell is a stone '#'
           - Place this stone at the current `empty` position in rotated matrix.
           - Decrement `empty--`.

   Case C: If current cell is '.'
           - Do nothing.

6. Rotation mapping used:

   Any original position (i, col) becomes:
   (col, m - 1 - i)

   This is the standard 90-degree clockwise matrix rotation formula.

7. Return the final answer matrix.

--------------------------------------------------------

⏱ Time Complexity:

O(m * n)

- We visit every cell exactly once.
- Each operation inside the loop is O(1).

Therefore total time is linear in terms of number of cells.

📦 Space Complexity:

O(m * n)

- We create one result matrix of size n x m.
- No other major extra space is used.

*/

#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& boxGrid) {
        int m = boxGrid.size();
        int n = boxGrid[0].size();

        vector<vector<char>> ans(n, vector<char>(m, '.'));

        for(int i = 0; i < m; i++) {
            int empty = n - 1;

            for(int j = n - 1; j >= 0; j--) {

                if(boxGrid[i][j] == '*') {
                    ans[j][m - 1 - i] = '*';
                    empty = j - 1;
                }
                else if(boxGrid[i][j] == '#') {
                    ans[empty][m - 1 - i] = '#';
                    empty--;
                }
            }
        }

        return ans;
    }
};
