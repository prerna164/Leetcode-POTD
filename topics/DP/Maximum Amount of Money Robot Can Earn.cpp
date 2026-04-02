/*
Problem: Maximum Amount of Money Robot Can Earn
Link: https://leetcode.com/problems/maximum-amount-of-money-robot-can-earn/

Date: 2026-04-02
Difficulty: Medium
Tags: Array, Dynamic Programming, Matrix

🧠 Intuition:

The robot moves in a grid (Down or Right), which is a classic signal for Dynamic Programming.

The "special ability" (neutralizing 2 robbers) adds a state to our DP. We need to know not just where the robot is, but also how many neutralizations it has already used.

When the robot encounters a negative value (a robber), it has a choice: either pay the penalty or use one of its remaining neutralizations to treat that cell as 0.

⚙️ Approach:

Define a 3D DP table dp[m][n][3], where dp[i][j][k] is the maximum coins at cell (i, j) having used k neutralizations.

Initialize the table with a very small value (negative infinity) since the total coins can be negative.

Iterate through the grid:

For each cell, the robot can arrive from the top (i-1, j) or from the left (i, j-1).

No Neutralization (k): Add the current coins[i][j] to the best previous state that used k neutralizations.

With Neutralization (k > 0): If the current cell is a robber (coins[i][j] < 0), the robot can skip the penalty by using a neutralization. This depends on the best previous state that used k-1 neutralizations.

The final answer is the maximum value found in dp[m-1][n-1][0...2].

⏱ Time Complexity:
O(m * n) - We visit each cell in the m x n grid exactly once, performing a constant amount of work (3 states) for each.

📦 Space Complexity:
O(m * n) - To store the 3D DP table. This can be optimized to O(n) space since each row only depends on the previous row.

*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
int maximumAmount(vector<vector<int>>& coins) {
int m = coins.size();
int n = coins[0].size();

    // dp[i][j][k] = max profit at (i, j) using k neutralizations
    // Using long long to avoid overflow during intermediate calculations
    long long dp[m][n][3];
    long long INF = 1e16;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < 3; k++) {
                dp[i][j][k] = -INF;
            }
        }
    }

    // Base Case: Starting cell (0, 0)
    dp[0][0][0] = coins[0][0];
    if (coins[0][0] < 0) {
        dp[0][0][1] = 0; // Use 1st neutralization
    } else {
        dp[0][0][1] = coins[0][0]; // Neutralization not useful but state exists
    }
    dp[0][0][2] = dp[0][0][1]; // Same logic for 2nd neutralization

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) continue;

            for (int k = 0; k < 3; k++) {
                long long fromPrev = -INF;
                if (i > 0) fromPrev = max(fromPrev, dp[i - 1][j][k]);
                if (j > 0) fromPrev = max(fromPrev, dp[i][j - 1][k]);

                // Option 1: Take the current cell value as is
                if (fromPrev != -INF) {
                    dp[i][j][k] = max(dp[i][j][k], fromPrev + coins[i][j]);
                }

                // Option 2: Use a neutralization (only if k > 0 and current cell is a robber)
                if (k > 0 && coins[i][j] < 0) {
                    long long fromPrevLessK = -INF;
                    if (i > 0) fromPrevLessK = max(fromPrevLessK, dp[i - 1][j][k - 1]);
                    if (j > 0) fromPrevLessK = max(fromPrevLessK, dp[i][j - 1][k - 1]);
                    
                    if (fromPrevLessK != -INF) {
                        dp[i][j][k] = max(dp[i][j][k], fromPrevLessK + 0);
                    }
                } else if (k > 0 && coins[i][j] >= 0) {
                    // If current cell is positive, using k neutralizations 
                    // is effectively the same as taking the best result from k-1 neutralizations
                    long long fromPrevLessK = -INF;
                    if (i > 0) fromPrevLessK = max(fromPrevLessK, dp[i - 1][j][k - 1]);
                    if (j > 0) fromPrevLessK = max(fromPrevLessK, dp[i][j - 1][k - 1]);
                    
                    if (fromPrevLessK != -INF) {
                        dp[i][j][k] = max(dp[i][j][k], fromPrevLessK + coins[i][j]);
                    }
                }
            }
        }
    }

    return (int)max({dp[m - 1][n - 1][0], dp[m - 1][n - 1][1], dp[m - 1][n - 1][2]});
}
};