/*
Problem: XOR After Range Multiplication Queries II
Link: https://leetcode.com/problems/xor-after-range-multiplication-queries-ii/

Date: 2026-04-09
Difficulty: Hard
Tags: Array, Math, Sqrt Decomposition, Prefix, Modular Arithmetic

-----------------------------------------------------

🧠 Intuition:

- Each query updates elements in a "jump pattern":
  i = l, l + k, l + 2k, ..., ≤ r

- Brute force fails because:
  → For small k (like k = 1, 2), we touch too many elements repeatedly → TLE

- Key Idea:
  👉 Split queries based on k using sqrt decomposition

  1. Large k (k ≥ √n):
     - Very few elements affected → safe to simulate directly

  2. Small k (k < √n):
     - Many elements affected → group queries smartly

- For small k:
  - Indices follow pattern: i % k = remainder
  - So we group queries by (k, remainder)

- Then for each group:
  - Convert indices into a compressed "chain"
    (like rem, rem+k, rem+2k...)
  - Apply range multiplication using a difference array

- Use modular inverse to "undo" multiplication after range ends

-----------------------------------------------------

⚙️ Approach:

1. Define threshold B = sqrt(n)

2. Process queries:
   - If k ≥ B:
       → Directly update nums[i] for i = l to r with step k
   - Else:
       → Store query in store[k][l % k]

3. For each small k:
   - For each remainder rem:
       → Build chain: indices = rem, rem+k, rem+2k...
       → Create diff array for range multiplication

       For each query (l, r, v):
           - Map l, r → chain indices:
               start = ceil((l - rem) / k)
               end   = floor((r - rem) / k)

           - Apply:
               diff[start] *= v
               diff[end+1] *= inverse(v)

4. Apply prefix multiplication on diff array:
   - Compute cumulative product
   - Update original nums accordingly

5. Compute XOR of final array

-----------------------------------------------------

⏱ Time Complexity:

- Large k queries: O(n / k) each → total ≈ O(n √n)
- Small k queries: processed in grouped manner → O(n √n)

👉 Overall: O(n √n)

-----------------------------------------------------

📦 Space Complexity:

- store array: O(n √n) worst case
- diff arrays: O(n)

👉 Overall: O(n √n)

-----------------------------------------------------
*/

#include <vector>
#include <cmath>
using namespace std;

class Solution {
public:
    static const int MOD = 1e9 + 7;

    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        int B = sqrt(n) + 1;

        // store[k][rem] -> list of {l, r, v}
        vector<vector<vector<vector<int>>>> store(B, vector<vector<vector<int>>>(B));

        // Step 1: Process queries
        for (auto &q : queries) {
            int l = q[0], r = q[1], k = q[2], v = q[3];

            if (k >= B) {
                // Large k → direct simulation
                for (int i = l; i <= r; i += k) {
                    nums[i] = (1LL * nums[i] * v) % MOD;
                }
            } else {
                // Small k → store for grouped processing
                int rem = l % k;
                store[k][rem].push_back({l, r, v});
            }
        }

        // Step 2: Process small k
        for (int k = 1; k < B; k++) {
            for (int rem = 0; rem < k; rem++) {

                if (store[k][rem].empty()) continue;

                int chainLen = (n - rem + k - 1) / k;

                vector<long long> diff(chainLen + 1, 1);

                for (auto &q : store[k][rem]) {
                    int l = q[0], r = q[1], v = q[2];

                    // Map original indices → chain indices
                    int start = (l <= rem) ? 0 : (l - rem + k - 1) / k;
                    int end   = (r < rem) ? -1 : (r - rem) / k;

                    if (start <= end && start < chainLen) {
                        end = min(end, chainLen - 1);

                        diff[start] = (diff[start] * v) % MOD;
                        if (end + 1 < chainLen) {
                            diff[end + 1] = (diff[end + 1] * modInverse(v)) % MOD;
                        }
                    }
                }

                // Apply prefix multiplication
                long long curr = 1;
                for (int i = 0; i < chainLen; i++) {
                    curr = (curr * diff[i]) % MOD;
                    int idx = rem + i * k;
                    nums[idx] = (1LL * nums[idx] * curr) % MOD;
                }
            }
        }

        // Step 3: Final XOR
        int res = 0;
        for (int x : nums) res ^= x;

        return res;
    }

    // Modular inverse using Fermat’s Theorem
    long long modInverse(long long a) {
        return power(a, MOD - 2);
    }

    // Fast exponentiation
    long long power(long long a, long long b) {
        long long res = 1;
        while (b) {
            if (b & 1) res = res * a % MOD;
            a = a * a % MOD;
            b >>= 1;
        }
        return res;
    }
};