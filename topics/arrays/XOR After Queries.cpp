/*
Problem: XOR After Queries
Link: (Custom / Similar to LeetCode-style problem)

Date: 2026-04-08
Difficulty: Medium
Tags: Array, Simulation, Math

-----------------------------------------------------

🧠 Intuition:
- Each query updates elements in a "jump pattern":
  starting from index `l`, then `l + k`, `l + 2k`, ... up to `r`.
- Since constraints are small (n, q ≤ 1000), we can directly simulate.
- After applying all queries, we compute the XOR of the final array.

-----------------------------------------------------

⚙️ Approach:
1. Iterate through each query:
   - Extract l, r, k, v
   - Start from index = l
   - While index <= r:
       → Multiply nums[index] by v
       → Take modulo (1e9 + 7)
       → Move index += k
2. After processing all queries:
   - Compute XOR of all elements in nums
3. Return the final XOR result

-----------------------------------------------------

⏱ Time Complexity:
- Each query processes ~O(n/k) elements → worst case O(n)
- Total complexity: O(n * q) ≤ 10^6 (acceptable)

📦 Space Complexity:
- O(1), in-place updates

-----------------------------------------------------
*/

#include <vector>

using namespace std;

class Solution {
public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        const int MOD = 1e9 + 7;

        // Process each query
        for (auto &q : queries) {
            int l = q[0];
            int r = q[1];
            int k = q[2];
            int v = q[3];

            int idx = l;
            while (idx <= r) {
                nums[idx] = (1LL * nums[idx] * v) % MOD;
                idx += k;
            }
        }

        // Compute XOR of final array
        int result = 0;
        for (int num : nums) {
            result ^= num;
        }

        return result;
    }
};