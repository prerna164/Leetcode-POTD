/*
Problem: 2463. Minimum Total Distance Traveled
Link: https://leetcode.com/problems/minimum-total-distance-traveled/

Date: 2026-04-14
Difficulty: Hard
Tags: Array, Dynamic Programming, Sorting

-----------------------------------------------------

🧠 Intuition:
- The key observation is that if we sort both the robots and the factories by their positions, 
  their relative order will be preserved in the optimal assignment. 
- Specifically, a factory at a smaller position will never "leapfrog" another factory 
  to pick up a robot further down the line if it results in crossing paths. This suggests 
  that each factory repairs a contiguous subsegment of the sorted robots.
- Once the positions are sorted, the problem transforms into a partitioning problem: 
  "How do we divide the sorted array of robots into groups, where each group is 
  assigned to a specific factory in order?"
- This structure is a classic candidate for Dynamic Programming (DP), where we decide 
  for each factory how many robots (from 0 to its limit) it should take.

-----------------------------------------------------

⚙️ Approach:
1. Sort `robot` and `factory` arrays based on their X-axis positions.
2. Define a DP state `dp[i][j]`: the minimum total distance to repair the first `i` 
   robots using the first `j` factories.
3. Transition:
   - For the j-th factory, we can choose to repair k robots (0 <= k <= limit).
   - If this factory repairs k robots, they must be the robots at indices (i-k) 
     through (i-1).
   - The cost for this choice is: dp[i-k][j-1] + sum(distances of these k robots).
4. Base Case:
   - dp[0][j] = 0: 0 robots always cost 0 distance.
   - dp[i][0] = infinity: If there are robots but no factories, it's impossible.
5. Result: The answer is stored in dp[n][m].

-----------------------------------------------------

⏱ Time Complexity:
O(M * N * K) — where N is the number of robots, M is the number of factories, 
and K is the average limit of a factory. In the worst case (K = N), the complexity 
is O(M * N^2). With N, M <= 100, 1,000,000 operations is well within limits.

📦 Space Complexity:
O(N * M) — To store the 2D DP table.

-----------------------------------------------------
*/

#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        // Step 1: Sort robots and factories to maintain optimal order
        sort(robot.begin(), robot.end());
        sort(factory.begin(), factory.end());

        int n = robot.size();
        int m = factory.size();

        // Use a large value for infinity. 1e15 prevents overflow during addition.
        const long long INF = 1e15;
        
        // dp[i][j] = min distance for first i robots using first j factories
        vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, INF));

        // Base case: If there are 0 robots, distance is 0
        for (int j = 0; j <= m; ++j) {
            dp[0][j] = 0;
        }

        // Fill DP table
        for (int j = 1; j <= m; ++j) { // Factory index
            int factoryPos = factory[j - 1][0];
            int factoryLimit = factory[j - 1][1];

            for (int i = 0; i <= n; ++i) { // Robot count
                // Case 1: Current factory repairs zero robots
                dp[i][j] = dp[i][j - 1];

                // Case 2: Current factory repairs k robots (up to its limit)
                long long currentDistSum = 0;
                for (int k = 1; k <= factoryLimit && i - k >= 0; ++k) {
                    // Accumulate distance of the k-th robot assigned to this factory
                    currentDistSum += abs((long long)robot[i - k] - factoryPos);
                    
                    // If the state excluding these k robots was reachable, update
                    if (dp[i - k][j - 1] != INF) {
                        dp[i][j] = min(dp[i][j], dp[i - k][j - 1] + currentDistSum);
                    }
                }
            }
        }

        return dp[n][m];
    }
};