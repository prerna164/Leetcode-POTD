/*
Problem: Maximum Score From Grid Operations
Link: https://leetcode.com/problems/maximum-score-from-grid-operations/

Date: 2026-04-29
Difficulty: Hard
Tags: Array, Dynamic Programming, Matrix, Prefix Sum

-----------------------------------------------------

🧠 Intuition:
- A cell (i, j) scores points if it is white and an adjacent column (j-1 or j+1) has 
  a black bar covering that same row 'i'.
- Since we color from the top down, each column j has a "height" h_j of black cells.
- The score contributed by column j depends on h_{j-1}, h_j, and h_{j+1}.
- We use a state-based DP to track whether the heights are currently "increasing" 
  or "decreasing" as we move across columns:
    1. Decreasing State: Current height <= Previous height. Column j gains points 
       from the taller black bar in column j-1.
    2. Increasing State: Current height > Previous height. Column j-1 gains points 
       from the taller black bar in column j.

-----------------------------------------------------

⚙️ Approach:
1. Precompute Prefix Sums: Store the sum of grid values column-wise to calculate 
   the sum of any vertical range in O(1).
2. DP State: dp[height][state]
   - state 0 (Decreasing/Valley): We are on a downward slope or at the bottom.
   - state 1 (Increasing/Peak): We are on an upward slope.
3. Transitions:
   - When moving to a new column, we compare the new height (curr_h) with the 
     old height (prev_h).
   - If decreasing, we add the sum of white cells in the current column that 
     are "covered" by the height of the previous column.
   - If increasing, we add the sum of white cells in the previous column that 
     are now "covered" by the current column's height.
4. Final Result: The maximum value across all possible heights in the last column.

-----------------------------------------------------

⏱ Time Complexity:
- O(n^3): We iterate through n columns, and for each column, we nestedly loop 
  through n possible current heights and n previous heights.

📦 Space Complexity:
- O(n^2): Used for the prefix sum table. The DP itself uses O(n) space since 
  we only need the previous column's results to calculate the current one.

-----------------------------------------------------
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long maximumScore(vector<vector<int>>& grid) {
        int n = grid.size();
        
        // 1. Precompute Prefix Sums for column range sum queries
        // pref[j][i] is the sum of grid[0...i-1][j]
        vector<vector<long long>> pref(n, vector<long long>(n + 1, 0));
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < n; ++i) {
                pref[j][i + 1] = pref[j][i] + grid[i][j];
            }
        }

        // dp[height][state]
        // state 0: Decreasing (h_curr <= h_prev)
        // state 1: Increasing (h_curr > h_prev)
        vector<vector<long long>> dp(n + 1, vector<long long>(2, 0));

        // Initializing column 0
        for (int h = 0; h <= n; ++h) {
            dp[h][0] = 0;
            dp[h][1] = 0;
        }

        // 2. DP Transitions across columns
        for (int j = 1; j < n; ++j) {
            vector<vector<long long>> ndp(n + 1, vector<long long>(2, 0));
            
            for (int curr_h = 0; curr_h <= n; ++curr_h) {
                for (int prev_h = 0; prev_h <= n; ++prev_h) {
                    
                    // --- Case: Decreasing Slope (prev_h >= curr_h) ---
                    // Current column j gets points from column j-1's black bar
                    if (prev_h >= curr_h) {
                        long long score_dec = pref[j][prev_h] - pref[j][curr_h];
                        // Transition from either decreasing or increasing (peak)
                        ndp[curr_h][0] = max({ndp[curr_h][0], 
                                              dp[prev_h][0] + score_dec, 
                                              dp[prev_h][1] + score_dec});
                    }

                    // --- Case: Increasing Slope (curr_h > prev_h) ---
                    // Previous column j-1 gets points from current column j's black bar
                    if (curr_h >= prev_h) {
                        long long score_inc = pref[j - 1][curr_h] - pref[j - 1][prev_h];
                        
                        // Continue an increasing climb
                        ndp[curr_h][1] = max(ndp[curr_h][1], dp[prev_h][1] + score_inc);
                        
                        // Valley transition: Start increasing after a decrease
                        // If we start from h=0, we can fully count the new column's height
                        if (prev_h == 0) {
                            ndp[curr_h][1] = max(ndp[curr_h][1], dp[0][0] + score_inc);
                        } else {
                            // If we switch from decreasing to increasing at a non-zero height,
                            // we carry over the best score without immediate double-counting
                            ndp[curr_h][1] = max(ndp[curr_h][1], dp[prev_h][0]);
                        }
                    }
                }
            }
            dp = ndp;
        }

        // 3. Maximize over all heights in the last column
        long long max_score = 0;
        for (int h = 0; h <= n; ++h) {
            max_score = max({max_score, dp[h][0], dp[h][1]});
        }
        
        return max_score;
    }
};