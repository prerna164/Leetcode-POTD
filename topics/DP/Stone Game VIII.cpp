/*
Problem: Stone Game VIII
Link: LeetCode 1872 - Stone Game VIII

Difficulty: Hard
Tags: Array, Dynamic Programming, Math, Prefix Sum, Game Theory

Intuition:
Notice that whenever a player removes the leftmost `x` stones and replaces them with a new stone 
equal to their sum, the value of this new stone is simply the prefix sum `pref[x - 1]`.

Furthermore, taking the first `x` stones means the next player can choose any index `y > x` 
and take prefix sum `pref[y - 1]`.

Let `dp[i]` be the maximum score difference (current player's score - opponent's score) 
if a player can choose any prefix index from `i` to `n - 1`.

For a choice at index `i` (where $1 \le i < n$):
1. The current player takes `pref[i]` points.
2. The remaining choices for the opponent start from index `i + 1`. 
   So the opponent gets optimal difference `dp[i + 1]`.
3. Thus, taking index `i` yields net score difference: `pref[i] - dp[i + 1]`.

Alternatively, the current player can skip index `i` and choose from `i + 1` onward, 
getting result `dp[i + 1]`.

Therefore, the recurrence relation is:
`dp[i] = max(dp[i + 1], pref[i] - dp[i + 1])`

Base Case:
For `i = n - 1` (the last element), the player MUST pick all stones:
`dp[n - 1] = pref[n - 1]`

We can compute this DP backwards from `n - 2` down to `1`. The answer is `dp[1]` 
because Alice must pick at least 2 stones ($x > 1$, which corresponds to index $i \ge 1$).

---

Approach:

1. Calculate Prefix Sums:
   * Build prefix sum array `pref` of length `n`.

2. Dynamic Programming Space Optimization:
   * Keep a running scalar variable `max_diff = pref[n - 1]` representing `dp[n - 1]`.
   * Iterate `i` backwards from `n - 2` down to `1`.
   * Update: `max_diff = max(max_diff, pref[i] - max_diff)`.

3. Return `max_diff`.

---

⏱ Time Complexity:
O(N)

* A single pass computes the prefix sums, and a second pass computes the DP values.
* Total Runtime: O(N) linear time.

Space Complexity:
O(N) or O(1) Auxiliary Space

* We use O(N) space for the prefix sums (or O(1) if modified in-place).
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int stoneGameVIII(vector<int>& stones) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = stones.size();
        vector<long long> pref(n, 0);
        pref[0] = stones[0];
        for (int i = 1; i < n; ++i) {
            pref[i] = pref[i - 1] + stones[i];
        }

        // Base case: dp[n - 1] = pref[n - 1]
        long long max_diff = pref[n - 1];

        // Iterate backwards from n - 2 down to 1 (since x > 1, index i >= 1)
        for (int i = n - 2; i >= 1; --i) {
            max_diff = max(max_diff, pref[i] - max_diff);
        }

        return max_diff;
    }
};