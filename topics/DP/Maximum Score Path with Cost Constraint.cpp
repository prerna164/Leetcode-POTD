/*
Problem: Maximum Score Path with Cost Constraint
Link: Custom Problem (Grid Pathfinding)

Date: 2024-05-22
Difficulty: Medium-Hard
Tags: Array, Dynamic Programming, Matrix, Shortest Path

🧠 Intuition:

This problem asks for the maximum score while staying within a specific "budget" (cost k). 
Because the movement is restricted to Right and Down, the grid acts as a Directed Acyclic Graph (DAG). 

In standard grid DP, we usually track only (i, j). However, here, the "score" we can achieve 
depends heavily on how much "cost" we have already spent. Therefore, we must include the 
accumulated cost as a third dimension in our state to ensure we make optimal decisions 
at each step without violating the constraint k.

⚙️ Approach:

Define a 3D DP table dp[m][n][k + 1], where dp[i][j][c] represents the maximum score 
achieved reaching cell (i, j) with an exact cumulative cost of c.

Initialize the table with -1 (representing unreachable states).

Iterate through the grid cell by cell:
1. For each state (i, j, current_cost), check if it is reachable.
2. Calculate the cost of moving into the next cell (Right or Down):
   - If grid[ni][nj] is 0: Cost +0, Score +0
   - If grid[ni][nj] is 1: Cost +1, Score +1
   - If grid[ni][nj] is 2: Cost +1, Score +2
3. If current_cost + move_cost <= k, update the next state:
   dp[ni][nj][c + move_cost] = max(dp[ni][nj][c + move_cost], current_score + move_score)

The final answer is the maximum value found in dp[m-1][n-1][0...k]. If all values are -1, 
return -1.

⏱ Time Complexity:
O(m * n * k) - We iterate through every cell (m*n) and for each cell, we iterate through 
all possible accumulated costs up to k.

📦 Space Complexity:
O(m * n * k) - To store the 3D DP table. For m,n=200 and k=1000, this requires ~40 million 
integers (~160MB), which fits within typical memory limits.

*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxPathScore(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();

        // dp[i][j][cost] = maximum score at cell (i, j) with specific cost
        // Initialize with -1 to indicate the state hasn't been reached
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(k + 1, -1)));

        // Base Case: Starting at (0, 0)
        // grid[0][0] is always 0 based on constraints, so cost is 0 and score is 0
        dp[0][0][0] = 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int c = 0; c <= k; ++c) {
                    // Skip if this specific state (position + cost) is unreachable
                    if (dp[i][j][c] == -1) continue;

                    int currentScore = dp[i][j][c];

                    // Try moving Down and Right
                    int dx[] = {1, 0};
                    int dy[] = {0, 1};

                    for (int d = 0; d < 2; ++d) {
                        int ni = i + dx[d];
                        int nj = j + dy[d];

                        if (ni < m && nj < n) {
                            int val = grid[ni][nj];
                            int nextCost = c + (val > 0 ? 1 : 0);
                            int nextScore = currentScore + val;

                            // Only proceed if we haven't exceeded the total allowed cost k
                            if (nextCost <= k) {
                                dp[ni][nj][nextCost] = max(dp[ni][nj][nextCost], nextScore);
                            }
                        }
                    }
                }
            }
        }

        // Search for the maximum score at the destination across all valid costs
        int result = -1;
        for (int c = 0; c <= k; ++c) {
            result = max(result, dp[m - 1][n - 1][c]);
        }

        return result;
    }
};