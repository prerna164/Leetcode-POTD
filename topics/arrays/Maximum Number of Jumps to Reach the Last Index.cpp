/*
Problem: Maximum Number of Jumps to Reach the Last Index
Link: LeetCode 2770

Date: 2024-05-22
Difficulty: Medium
Tags: Array, Dynamic Programming

Intuition:
We are standing at the start (index 0) and want to reach the end (index n-1)
using the maximum number of steps possible. Each step must satisfy a
specific condition: the difference between the values at the current index
and the next index must be within [-target, target].
Think of this as a "Longest Path" problem in a Directed Acyclic Graph (DAG).
Every index is a node, and a valid jump from index 'i' to 'j' is a directed
edge from i to j.
Because we want the *maximum* number of jumps, if we can reach index 'j'
from multiple previous indices 'i', we should pick the one that already
took the most jumps to reach 'i'.
--------------------------------------------------------
Approach:
1. Let:
n = size of the nums array.
2. Create a DP array `dp` of size n:
- `dp[i]` represents the maximum number of jumps taken to reach index `i`.
- Initialize all elements to -1 (indicating the index is unreachable).
- Set `dp[0] = 0` because we start at the first index with 0 jumps.
3. Iterative DP Calculation:
- Use an outer loop `i` from 0 to n-1 to represent the "current" index.
- If `dp[i] == -1`, it means we can't reach this index from the start,
so we skip it.
- Use an inner loop `j` from i+1 to n-1 to represent the potential "next"
jump.
4. Validation Check:
- For each pair (i, j), check if:
-target <= nums[j] - nums[i] <= target
- If this condition is met, update `dp[j]`:
dp[j] = max(dp[j], dp[i] + 1)
5. Return Result:
- The answer is stored in `dp[n-1]`. If it remains -1, the end is

unreachable.
--------------------------------------------------------
⏱ Time Complexity:
O(n^2)
- We use two nested loops. The outer loop runs n times, and the inner
loop runs up to n times.
- With n = 1000, n^2 = 1,000,000, which easily fits within the 1-second
limit.
Space Complexity:
O(n)
- We only use a single auxiliary DP array of size n to store the
maximum jumps for each index.
*/
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
int maximumJumps(vector<int>& nums, int target) {
int n = nums.size();
// dp[i] stores the max jumps to reach index i from index 0
// Initialize with -1 to represent 'unreachable'
vector<int> dp(n, -1);
// Base case: Starting position
dp[0] = 0;
for (int i = 0; i < n; i++) {
// If current index i cannot be reached, we can't jump from it
if (dp[i] == -1) continue;
for (int j = i + 1; j < n; j++) {
// Condition: abs(nums[j] - nums[i]) <= target
// We use long long for subtraction to prevent overflow
long long diff = (long long)nums[j] - nums[i];
if (diff >= -target && diff <= target) {
// Update dp[j] with the maximum jumps found so far
dp[j] = max(dp[j], dp[i] + 1);
}
}

}
return dp[n - 1];
}
};