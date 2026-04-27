/*
Problem: Check if There is a Valid Path in a Grid

Link: https://leetcode.com/problems/check-if-there-is-a-valid-path-in-a-grid/

Date: 2026-04-27
Difficulty: Medium
Tags: Array, Breadth-First Search, Depth-First Search, Union Find, Matrix
-----------------------------------------------------

🧠 Intuition:
- The grid consists of different "pipe" shapes. For a path to exist, the exit
of
one pipe must align perfectly with the entrance of the next pipe.
- This is a reachability problem in a graph. Each cell is a node, and a valid
connection between two cells is an undirected edge.
- A path is only valid if both pipes "mutually" connect to each other. For
example,
if cell A says it connects to the Right, cell B (to its right) must say it
connects to the Left.
-----------------------------------------------------

⚙️ Approach:
1. Define the possible directions for each street type (1-6).
- 0: Up, 1: Down, 2: Left, 3: Right.
2. Use BFS (or DFS) starting from (0, 0).
3. For the current cell, check its allowed exit directions based on its type.
4. For each exit direction, find the neighbor and check:
- Is it within grid boundaries?
- Does the neighbor's pipe type have an entrance that matches our exit?
(e.g., if we exit Right, the neighbor must have a Left connection).
5. If the neighbor is valid and not visited, add it to the queue.
6. If we ever reach (m-1, n-1), return true.
-----------------------------------------------------
⏱ Time Complexity:
- O(M × N): We visit each cell at most once during the BFS/DFS traversal.

📦 Space Complexity:
- O(M × N): Used for the 'visited' array and the BFS queue/DFS recursion stack.
-----------------------------------------------------
*/
#include <vector>
#include <queue>
using namespace std;
class Solution {
public:
    bool hasValidPath(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
   
        vector<vector<int>> streetConnections = {
            {},      
            {2, 3},    
            {0, 1},    
            {2, 1},    
            {3, 1}, 
            {2, 0},   
            {3, 0}
        };
        queue<pair<int, int>> q;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        
        q.push({0, 0});
        visited[0][0] = true;

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            if (r == m - 1 && c == n - 1) return true;

            int streetType = grid[r][c];
            for (int dir : streetConnections[streetType]) {
                int nr = r + dr[dir];
                int nc = c + dc[dir];

                if (nr >= 0 && nr < m && nc >= 0 && nc < n && !visited[nr][nc]) {
                    int nextStreet = grid[nr][nc];
                    bool canConnect = false;
                    
                    int backDir = dir ^ 1;
                    
                    for (int nDir : streetConnections[nextStreet]) {
                        if (nDir == backDir) {
                            canConnect = true;
                            break;
                        }
                    }

                    if (canConnect) {
                        visited[nr][nc] = true;
                        q.push({nr, nc});
                    }
                }
            }
        }
        
        return false;
    }
};