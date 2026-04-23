/*
Problem: Robot Collisions
Link: https://leetcode.com/problems/robot-collisions/

Date: 2026-04-01
Difficulty: Hard
Tags: Array, Stack, Sorting, Simulation

-----------------------------------------------------

🧠 Intuition:
- Robots only collide if they are moving toward each other (a Right-moving robot followed by a Left-moving robot).
- Since robots are given in arbitrary order, the first step is to process them based on their actual positions on the line.
- A stack is perfect here: it stores robots moving Right that haven't been "resolved" yet. When we encounter a robot moving Left, it potentially collides with everything in our stack.

-----------------------------------------------------

⚙️ Approach:
1. Create an index array and sort it based on the 'positions' array to process robots from left to right.
2. Use a stack to keep track of indices of robots moving Right ('R').
3. For every robot moving Left ('L'):
    - Compare its health with the robot at the top of the stack (the nearest 'R' robot).
    - If 'L' health > 'R' health: 'R' is destroyed (pop), 'L' health decreases by 1, and it continues to the next 'R' in stack.
    - If 'L' health < 'R' health: 'R' health decreases by 1, 'L' is destroyed.
    - If healths are equal: Both are destroyed.
4. Finally, iterate through the original healths array and collect values > 0 to maintain the original input order.

-----------------------------------------------------

⏱ Time Complexity:
O(n log n) - primarily due to sorting the indices based on positions. The simulation itself is O(n).

📦 Space Complexity:
O(n) - to store the indices and the stack for the simulation.

-----------------------------------------------------
*/

#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <stack>

using namespace std;

class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        int n = positions.size();
        vector<int> indices(n);
        
        // Initialize indices to represent original robot IDs
        iota(indices.begin(), indices.end(), 0);
        
        // Sort indices based on their positions on the line
        sort(indices.begin(), indices.end(), [&](int a, int b) {
            return positions[a] < positions[b];
        });
        
        stack<int> st; // Stores indices of robots moving Right ('R')
        
        for (int i : indices) {
            if (directions[i] == 'R') {
                st.push(i);
            } else {
                // Current robot is moving Left ('L'), check for collisions
                while (!st.empty() && healths[i] > 0) {
                    int topIdx = st.top();
                    
                    if (healths[i] > healths[topIdx]) {
                        // Left-moving robot wins the collision
                        healths[topIdx] = 0;
                        healths[i] -= 1;
                        st.pop();
                    } else if (healths[i] < healths[topIdx]) {
                        // Right-moving robot wins the collision
                        healths[topIdx] -= 1;
                        healths[i] = 0;
                    } else {
                        // Both robots have equal health, both are destroyed
                        healths[i] = 0;
                        healths[topIdx] = 0;
                        st.pop();
                    }
                }
            }
        }
        
        // Collect health of survivors in the order they were originally provided
        vector<int> result;
        for (int h : healths) {
            if (h > 0) {
                result.push_back(h);
            }
        }
        
        return result;
    }
};