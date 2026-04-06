/*
Problem: Walking Robot Simulation
Link: https://leetcode.com/problems/walking-robot-simulation/

Date: 2026-04-06
Difficulty: Medium
Tags: Array, Hash Table, Simulation

-----------------------------------------------------

🧠 Intuition:
- The robot moves on an infinite grid. We track (x, y) and direction.
- To maintain O(n) performance, we need O(1) obstacle lookups.
- We map (x, y) coordinates to a unique 64-bit integer (long long) to 
  use a Hash Table (unordered_set).

-----------------------------------------------------

⚙️ Approach:
1. Define directions: North {0,1}, East {1,0}, South {0,-1}, West {-1,0}.
2. Use `unordered_set<long long>` to store obstacles. 
   Hash formula: (x + 30000) << 16 | (y + 30000). This handles the 
   coordinate range constraints efficiently.
3. For each command:
   - -2: Left turn -> (dir + 3) % 4.
   - -1: Right turn -> (dir + 1) % 4.
   - k: Move step-by-step. If the next hashed coordinate exists in the 
     unordered_set, stop.
4. Track the maximum x^2 + y^2 at every step.

-----------------------------------------------------

⏱ Time Complexity:
O(n) - where n = (number of commands + number of obstacles). 
The unordered_set allows for O(1) average time lookups.

📦 Space Complexity:
O(n) - specifically O(O) to store obstacles in the hash table.

-----------------------------------------------------
*/

#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        // Directions: North, East, South, West
        int dx[] = {0, 1, 0, -1};
        int dy[] = {1, 0, -1, 0};
        
        // Use unordered_set for O(1) average lookup
        unordered_set<long long> obstacleSet;
        for (const auto& obs : obstacles) {
            // Hash x and y into a single long long
            // Offset by 30000 to ensure positive values before bit-shifting
            long long hashedCoord = ((long long)obs[0] + 30000) << 16 | ((long long)obs[1] + 30000);
            obstacleSet.insert(hashedCoord);
        }
        
        int x = 0, y = 0, dir = 0;
        int maxDistSq = 0;
        
        for (int cmd : commands) {
            if (cmd == -2) {
                dir = (dir + 3) % 4; // Turn Left
            } else if (cmd == -1) {
                dir = (dir + 1) % 4; // Turn Right
            } else {
                for (int i = 0; i < cmd; ++i) {
                    int nextX = x + dx[dir];
                    int nextY = y + dy[dir];
                    
                    long long nextHash = ((long long)nextX + 30000) << 16 | ((long long)nextY + 30000);
                    
                    if (obstacleSet.find(nextHash) == obstacleSet.end()) {
                        x = nextX;
                        y = nextY;
                        maxDistSq = max(maxDistSq, x * x + y * y);
                    } else {
                        break; // Blocked
                    }
                }
            }
        }
        
        return maxDistSq;
    }
};