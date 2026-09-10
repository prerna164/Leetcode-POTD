/*
Problem: Distinct Subsequences
Link: LeetCode 115 - Distinct Subsequences

Difficulty: Hard
Tags: String, Dynamic Programming

Intuition:
Let `dp[i][j]` represent the number of distinct subsequences of `s[0...i-1]` that equal `t[0...j-1]`.

Transitions:
1. If `s[i - 1] == t[j - 1]`:
   We have two options:
   - Match `s[i - 1]` with `t[j - 1]`, which leaves us finding `t[0...j-2]` in `s[0...i-2]` -> `dp[i - 1][j - 1]`.
   - Skip `s[i - 1]` and find `t[0...j-1]` in `s[0...i-2]` -> `dp[i - 1][j]`.
   Total: `dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j]`

2. If `s[i - 1] != t[j - 1]`:
   We must skip `s[i - 1]`:
   `dp[i][j] = dp[i - 1][j]`

Base Case:
- `dp[i][0] = 1`: An empty target string `t` can be formed by 1 empty subsequence from any prefix of `s`.
- `dp[0][j] = 0` for `j > 0`: An empty string `s` cannot form a non-empty target `t`.

Space Optimization:
Notice that `dp[i][j]` only depends on values from the previous row (`i - 1`).
We can reduce the space to a 1D array `dp` of size `m + 1` (where `m = t.length()`) and iterate backwards over `j` from `m` down to `1`.

---

Approach:

1. Initialization:
   * Let `n = s.length()` and `m = t.length()`.
   * Create a 1D vector `dp` of size `m + 1` initialized to `0`.
   * Set `dp[0] = 1` (empty string target match).

2. Dynamic Programming State Updates:
   * Outer loop `ch` over characters in `s`.
   * Inner loop `j` backwards from `m` down to `1`:
     - If `s[i] == t[j - 1]`, update `dp[j] = (dp[j] + dp[j - 1]) % UINT_MAX` (or `unsigned long long` to prevent integer overflow intermediate calculation before fitting in 32-bit int).

3. Return `dp[m]`.

---

⏱ Time Complexity:
O(N * M)

* `N = s.length()` and `M = t.length()`.
* Nested loop runs $N \times M$ times.
* Total Runtime: O(N * M) time.

Space Complexity:
O(M) Auxiliary Space

* 1D DP vector of size `M + 1`.
*/

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int numDistinct(string s, string t) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = s.length();
        int m = t.length();

        // If target is longer than source, impossible to form subequence
        if (n < m) return 0;

        // dp[j] stores number of subsequences in s matching prefix t[0...j-1]
        vector<unsigned int> dp(m + 1, 0);
        dp[0] = 1; // Empty string target can always be matched in 1 way

        for (int i = 0; i < n; ++i) {
            for (int j = m; j >= 1; --j) {
                if (s[i] == t[j - 1]) {
                    dp[j] += dp[j - 1];
                }
            }
        }

        return dp[m];
    }
};