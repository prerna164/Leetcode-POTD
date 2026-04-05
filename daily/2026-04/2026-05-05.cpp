/*
Problem: Robot Return to Origin
Link: https://leetcode.com/problems/robot-return-to-origin/

Date: 2026-04-05
Difficulty: Easy
Tags: String, Simulation

-----------------------------------------------------

🧠 Intuition:
- The robot moves on a 2D coordinate plane starting at (0, 0).
- For the robot to return to the origin, every move in one direction 
  must be neutralized by a move in the opposite direction.
- Specifically:
  1. Every 'Up' (U) must have a corresponding 'Down' (D).
  2. Every 'Right' (R) must have a corresponding 'Left' (L).
- The order of moves doesn't matter; only the total net change in 
  the X and Y axes matters.

-----------------------------------------------------

⚙️ Approach:
1. Initialize two variables, `x` and `y`, to 0 to represent the coordinates.
2. Iterate through the string `moves`:
   - If move is 'U', increment `y` (move up).
   - If move is 'D', decrement `y` (move down).
   - If move is 'R', increment `x` (move right).
   - If move is 'L', decrement `x` (move left).
3. After the loop, check if both `x` and `y` are back to 0.
4. Return `true` if (x == 0 and y == 0), otherwise return `false`.

-----------------------------------------------------

⏱ Time Complexity:
O(N) - where N is the number of moves. We traverse the string exactly once.

📦 Space Complexity:
O(1) - We only use two integer variables regardless of the input size.

-----------------------------------------------------
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    bool judgeCircle(string moves) {
        int x = 0; // Horizontal axis
        int y = 0; // Vertical axis

        // Process each move to update coordinates
        for (char move : moves) {
            if (move == 'U') {
                y++;
            } else if (move == 'D') {
                y--;
            } else if (move == 'R') {
                x++;
            } else if (move == 'L') {
                x--;
            }
        }

        // The robot returns to origin only if net displacement is zero
        return (x == 0 && y == 0);
    }
};