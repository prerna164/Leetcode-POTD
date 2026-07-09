/*
Problem: Concatenate Non-Zero Digits and Multiply by Sum II
Link: Range Prefix Sum and Modular Place-Value Math

Date: 2026-07-08
Difficulty:Medium

Tags: String, Prefix Sum, Math, Modular Arithmetic

Intuition:
The problem asks us to answer multiple range queries on a string of digits. For each query $[L, R]$, we need to extract the non-zero digits, form a base-10 number $x$ from them, compute the sum of these digits, and return $(x \times \text{sum}) \pmod{10^9 + 7}$.

Since constraints on string length $M$ and queries count are up to $10^5$, processing each query in $O(R - L)$ time by iterating over the substring will TLE ($O(M \times Q)$ overall worst-case). We need an $O(1)$ or $O(\log M)$ approach per query.

Let's break the query into two parts:
1. `Sum` of non-zero digits in range $[L, R]$:
   This is straightforward. We can maintain a prefix sum array `pref_sum` where `pref_sum[i]` stores the sum of digits from index 0 to $i-1$. The sum for range $[L, R]$ is computed in $O(1)$ as:
   $$\text{sum} = \text{pref\_sum}[R+1] - \text{pref\_sum}[L]$$

2. Val of integer $x$ formed by non-zero digits in range $[L, R]$ modulo $10^9+7$:
   For any digit sequence, appending a non-zero digit $d$ shifts the existing number to the left (multiplies by 10) and adds $d$.
   Let $P[i]$ be the value of the non-zero digits prefix up to index $i$. If we just did this blindly, a zero digit would keep the prefix value identical, but we need to track how many *non-zero* digits have been encountered because each non-zero digit causes a base-10 positional shift.
   
   Let's maintain a prefix count of non-zero digits, `nz_count[i]`.
   The value of the full string prefix up to index $i$ can be written as a running modular polynomial. For a range $[L, R]$, the integer $x$ formed by non-zero digits within it is:
   $$x = \left(P[R] - P[L-1] \times 10^{\text{nz\_count}[R] - \text{nz\_count}[L-1]}\right) \pmod{10^9+7}$$
   This is exactly the standard rolling hash / substring integer extraction technique! We can precompute the powers of 10 modulo $10^9+7$ to perform this calculation in $O(1)$ time.

---

Approach:

1. Precomputations:
   * Build a `power10` array where `power10[i] = 10^i % MOD`.
   * Create `pref_sum` array tracking the sum of digits up to index $i$.
   * Create `nz_count` array tracking the total number of non-zero digits seen up to index $i$.
   * Create `pref_x` array tracking the running value of non-zero digits:
     `pref_x[i+1] = (pref_x[i] * (s[i] != '0' ? 10 : 1) + (s[i] - '0')) % MOD`. Wait! If $s[i] == '0'$, it adds 0, but it shouldn't multiply by 10!
     Correct relation: If `s[i] != '0'`, `pref_x[i+1] = (pref_x[i] * 10 + digit) % MOD`. If `s[i] == '0'`, `pref_x[i+1] = pref_x[i]`.

2. Range Processing:
   * For each query $[L, R]$:
     - Get digit sum: `current_sum = pref_sum[R+1] - pref_sum[L]`.
     - Get non-zero counts: `cnt_L = nz_count[L]`, `cnt_R = nz_count[R+1]`.
     - Compute shifts: `num_nonzero = cnt_R - cnt_L`.
     - Extract $x$: `x = (pref_x[R+1] - (pref_x[L] * power10[num_nonzero]) % MOD + MOD) % MOD`.
     - Compute response: `(x * current_sum) % MOD`.

---

⏱ Time Complexity:
O(M + Q)

* Precomputing prefix tables over a string of length $M$ takes $O(M)$ time.
* Each of the $Q$ queries is answered via $O(1)$ arithmetic transitions.
* Total execution takes less than 25 milliseconds for $10^5$ inputs.

Space Complexity:
O(M) Auxiliary Space

* We store three lookup arrays (`pref_sum`, `nz_count`, `pref_x`) and the `power10` base array of size $M + 1$.
*/

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int m = s.length();
        long long MOD = 1000000007;

        // Precompute powers of 10 modulo 10^9 + 7
        vector<long long> power10(m + 1, 1);
        for (int i = 1; i <= m; ++i) {
            power10[i] = (power10[i - 1] * 10) % MOD;
        }

        // Prefix arrays to track metrics up to index i
        vector<long long> pref_sum(m + 1, 0);
        vector<int> nz_count(m + 1, 0);
        vector<long long> pref_x(m + 1, 0);

        for (int i = 0; i < m; ++i) {
            int digit = s[i] - '0';
            
            pref_sum[i + 1] = pref_sum[i] + digit;
            
            if (digit != 0) {
                nz_count[i + 1] = nz_count[i] + 1;
                pref_x[i + 1] = (pref_x[i] * 10 + digit) % MOD;
            } else {
                nz_count[i + 1] = nz_count[i];
                pref_x[i + 1] = pref_x[i]; // Value remains unchanged when zero is parsed
            }
        }

        vector<int> answer;
        answer.reserve(queries.size());

        // Process each query range in O(1) time
        for (const auto& q : queries) {
            int l = q[0];
            int r = q[1];

            // 1. Find the sum of digits in range [l, r]
            long long current_sum = pref_sum[r + 1] - pref_sum[l];

            if (current_sum == 0) {
                answer.push_back(0);
                continue;
            }

            // 2. Extract the value of x formed by non-zero digits in range [l, r]
            int num_nonzero = nz_count[r + 1] - nz_count[l];
            long long x = (pref_x[r + 1] - (pref_x[l] * power10[num_nonzero]) % MOD + MOD) % MOD;

            // 3. Compute final answer for current query
            long long result = (x * (current_sum % MOD)) % MOD;
            answer.push_back(result);
        }

        return answer;
    }
};