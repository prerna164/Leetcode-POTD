/*
Problem: Walking Robot Simulation II
Link: https://leetcode.com/problems/walking-robot-simulation-ii/

Date: 2026-04-07
Difficulty: Medium
Tags: Design, Math, Simulation

-----------------------------------------------------

🧠 Intuition:
- The robot always stays on the outer boundary of the width x height grid.
- Instead of simulating every step (up to 10^5), we treat the boundary as 
  a 1D loop of length P = 2*(w-1) + 2*(h-1).
- We use the modulo operator (%) to find the effective position on this loop.
- A critical edge case: If the robot moves a full lap and ends at (0,0), 
  its direction is "South" because it "attempted" to move West and hit 
  the boundary at the very last step.

-----------------------------------------------------

⚙️ Approach:
1. Store width (w), height (h), and the total perimeter (2w + 2h - 4).
2. Keep a `pos` variable representing the total steps taken % perimeter.
3. Use a `moved` flag to distinguish between the starting "East" at (0,0) 
   and the post-movement "South" at (0,0).
4. Mapping `pos` to (x, y):
   - 0 <= pos < w: Bottom edge
   - w-1 < pos < w+h-1: Right edge
   - w+h-2 < pos < 2w+h-2: Top edge
   - else: Left edge

-----------------------------------------------------

⏱ Time Complexity:
O(1) per operation. 'step', 'getPos', and 'getDir' all run in constant time 
regardless of the number of steps or grid size.

📦 Space Complexity:
O(1). We only store a few integer variables.

-----------------------------------------------------
*/

#include <vector>
#include <string>

using namespace std;

class Robot {
private:
    int w, h, perimeter;
    int pos = 0;
    bool moved = false;

public:
    Robot(int width, int height) {
        w = width;
        h = height;
        // The number of unique boundary cells is the perimeter
        perimeter = 2 * (w - 1) + 2 * (h - 1);
    }
    
    void step(int num) {
        moved = true;
        // Modulo handles multiple laps efficiently
        pos = (pos + num) % perimeter;
    }
    
    vector<int> getPos() {
        // Determine segment of the perimeter based on 'pos'
        if (pos <= w - 1) {
            return {pos, 0}; // Bottom side
        } else if (pos <= (w - 1) + (h - 1)) {
            return {w - 1, pos - (w - 1)}; // Right side
        } else if (pos <= 2 * (w - 1) + (h - 1)) {
            return {(w - 1) - (pos - (w - 1) - (h - 1)), h - 1}; // Top side
        } else {
            return {0, (h - 1) - (pos - 2 * (w - 1) - (h - 1))}; // Left side
        }
    }
    
    string getDir() {
        // Case 1: Hasn't moved yet
        if (!moved) return "East";
        
        // Case 2: At origin after moving (full lap)
        if (pos == 0) return "South";
        
        // Case 3: Standard boundary checks
        if (pos > 0 && pos <= w - 1) {
            return "East";
        } else if (pos > w - 1 && pos <= (w - 1) + (h - 1)) {
            return "North";
        } else if (pos > (w - 1) + (h - 1) && pos <= 2 * (w - 1) + (h - 1)) {
            return "West";
        } else {
            return "South";
        }
    }
};

/**
 * Your Robot object will be instantiated and called as such:
 * Robot* obj = new Robot(width, height);
 * obj->step(num);
 * vector<int> param_2 = obj->getPos();
 * string param_3 = obj->getDir();
 */