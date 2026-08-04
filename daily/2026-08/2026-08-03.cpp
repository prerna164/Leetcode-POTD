/*
Problem: Stone Game III
Link: LeetCode 1406 - Stone Game III

Difficulty: Hard
Tags: Array, Math, Dynamic Programming, Game Theory

Intuition:
We are given an array `stoneValue` representing stones in a row.
Two players (Alice and Bob) take turns. On each turn, a player can pick 1, 2, or 3 stones from the remaining front of the array.
Alice goes first. Both players play optimally to maximize their own final score.

Instead of tracking both players' total scores independently, we can reformulate the problem using relative score differences:
  Net Score = (Current Player's Score) - (Opponent's Score)

Let `dp[i]` be the maximum net score difference the player whose turn it is can achieve starting from index `i` to the end of the array `stoneValue`.

At index `i`, the current player can choose to take:
1. 1 stone (`stoneValue[i]`):
   Net difference = `stoneValue[i] - dp[i + 1]`
2. 2 stones (`stoneValue[i] + stoneValue[i + 1]`):
   Net difference = `stoneValue[i] + stoneValue[i + 1] - dp[i + 2]`
3. 3 stones (`stoneValue[i] + stoneValue[i + 1] + stoneValue[i + 2]`):
   Net difference = `stoneValue[i] + stoneValue[i + 1] + stoneValue[i + 2] - dp[i + 3]`

The player will choose the move (taking 1, 2, or 3 stones) that maximizes this net difference.

---

Approach:

1. Dynamic Programming (Bottom-Up):
   * Iterate backwards from index `i = N - 1` down to `0`.
   * Maintain the DP state for the next 3 steps (`dp[i+1]`, `dp[i+2]`, `dp[i+3]`).
   * We can optimize memory to O(1) space using an array/variables of size 4 or simple state variables.

2. Base Case:
   * Beyond the end of the array (`i >= N`), `dp[i] = 0`.

3. Result Evaluation:
   * Evaluate `dp[0]` (Alice's max relative score difference starting from index 0):
     - If `dp[0] > 0`: Alice wins -> return `"Alice"`
     - If `dp[0] < 0`: Bob wins -> return `"Bob"`
     - If `dp[0] == 0`: It's a draw -> return `"Tie"`

---

⏱ Time Complexity:
O(N)

* We iterate through the array of length N once from right to left.
* At each position `i`, we examine at most 3 choices (O(1) operations).

Space Complexity:
O(1) Auxiliary Space

* Space optimized DP using a size-4 array to track states.
*/

#include <string>
#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>

using namespace std;

class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = stoneValue.size();
        
        // dp[i] represents max relative score starting at index i
        // We only need 4 states: dp[i], dp[i+1], dp[i+2], dp[i+3]
        vector<int> dp(4, 0);

        for (int i = n - 1; i >= 0; --i) {
            int maxDiff = INT_MIN;
            int currentSum = 0;

            // Try taking 1, 2, or 3 stones
            for (int k = 1; k <= 3 && i + k <= n; ++k) {
                currentSum += stoneValue[i + k - 1];
                int opponentDiff = dp[(i + k) % 4];
                maxDiff = max(maxDiff, currentSum - opponentDiff);
            }

            dp[i % 4] = maxDiff;
        }

        int aliceDiff = dp[0];

        if (aliceDiff > 0) return "Alice";
        if (aliceDiff < 0) return "Bob";
        return "Tie";
    }
};