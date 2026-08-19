/*
Problem: Stone Game V
Link: LeetCode 1563 - Stone Game V

Difficulty: Hard
Tags: Array, Math, Dynamic Programming, Game Theory

Intuition:
We need to find the maximum score Alice can achieve by dividing the array into two non-empty contiguous subarrays `[i...k]` and `[k+1...j]`.
Bob throws away the subarray with the strictly larger sum. If both sums are equal, Alice gets to choose which one to throw away.

Let `dp[i][j]` be the maximum score Alice can obtain from the subarray `stoneValue[i...j]`.

For a given range `[i, j]`, Alice can pick any partition point `k` where `i <= k < j`:
- Let `left_sum = sum(stoneValue[i...k])`
- Let `right_sum = sum(stoneValue[k+1...j])`

Transitions:
1. `left_sum < right_sum`: Bob throws away the right row.
   Score gain = `left_sum + dp[i][k]`
2. `left_sum > right_sum`: Bob throws away the left row.
   Score gain = `right_sum + dp[k+1][j]`
3. `left_sum == right_sum`: Alice decides which row to keep.
   Score gain = `left_sum + max(dp[i][k], dp[k+1][j])`

We can precompute prefix sums to query `left_sum` and `right_sum` in $O(1)$ time.

---

Approach:

1. Prefix Sum Array:
   * Build `pref` array where `pref[x]` stores the sum of `stoneValue[0...x-1]`.
   * Sum of range `[l, r]` is `pref[r + 1] - pref[l]`.

2. Dynamic Programming (Interval DP):
   * `dp[i][j]` stores the maximum score for subarray range `[i, j]`.
   * Iterate over subsegment lengths `len` from 2 to `N`.
   * For each starting index `i`, set `j = i + len - 1`.
   * Iterate partition index `k` from `i` to `j - 1`:
     - Compare `left_sum` and `right_sum`.
     - Update `dp[i][j]` with the maximum achievable score across all valid partition choices `k`.

3. Result:
   * Return `dp[0][N - 1]`.

---

⏱ Time Complexity:
O(N^3)

* There are $O(N^2)$ states `(i, j)`.
* For each state, we iterate $k$ from $i$ to $j - 1$, taking $O(N)$ operations.
* Total operations: $\approx \frac{N^3}{6}$.
* For $N \le 500$, $500^3 / 6 \approx 2 \times 10^7$ operations, easily running within the time limit.

Space Complexity:
O(N^2) Auxiliary Space

* DP table `dp` of dimensions $N \times N$ uses $O(N^2)$ space.
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = stoneValue.size();
        vector<int> pref(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            pref[i + 1] = pref[i] + stoneValue[i];
        }

        // dp[i][j] stores max score achievable for range stoneValue[i...j]
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // Iterate over length of the subarray
        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i <= n - len; ++i) {
                int j = i + len - 1;

                for (int k = i; k < j; ++k) {
                    int left_sum = pref[k + 1] - pref[i];
                    int right_sum = pref[j + 1] - pref[k + 1];

                    if (left_sum < right_sum) {
                        dp[i][j] = max(dp[i][j], left_sum + dp[i][k]);
                    } else if (left_sum > right_sum) {
                        dp[i][j] = max(dp[i][j], right_sum + dp[k + 1][j]);
                    } else { // left_sum == right_sum
                        dp[i][j] = max(dp[i][j], left_sum + max(dp[i][k], dp[k + 1][j]));
                    }
                }
            }
        }

        return dp[0][n - 1];
    }
};