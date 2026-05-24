/*
Problem: Jump Game V
Link: LeetCode 1340

Date: 2026-05-24
Difficulty: Hard
Tags: Array, Dynamic Programming, Memoization, Graph

🧠 Intuition:
The problem states that from a given index `i`, we can jump left or right up to a maximum distance `d`. However, a crucial constraint is that we can only jump to a lower height (`arr[i] > arr[j]`), and there must be no blocking elements that are greater than or equal to `arr[i]` between `i` and `j`.

This requirement forms a Directed Acyclic Graph (DAG) of choices, because you can only move from a strictly larger value to a strictly smaller value. Since there are no cycles, this can be beautifully and efficiently solved using Dynamic Programming (DP) with Memoization.

For any index `i`, the maximum indices we can visit starting from it is:
`1 + max(maxJumps(j))` for all valid indices `j` reachable from `i`.

If we compute this value for an index once, we can store it in a `memo` table so that subsequent queries take O(1) time. We can try starting at every possible index and find the global maximum.

--------------------------------------------------------

⚙️ Approach:
1. Initialize a `memo` array of size `n` with `-1` to keep track of the results for each index.
2. Define a recursive helper function `solve(i, arr, d, memo)`:
   - If `memo[i] != -1`, return its precalculated value.
   - Start with a baseline answer `ans = 1` (since we can always visit at least the current index `i`).
   - **Look Right:** Iterate `j` from `i + 1` up to `min(n - 1, i + d)`:
     - If `arr[j] >= arr[i]`, a building blocks our path. We must `break` immediately because we cannot jump past or onto it.
     - Otherwise (`arr[j] < arr[i]`), it's a valid jump destination. Recursively call `1 + solve(j, arr, d, memo)` and maximize `ans`.
   - **Look Left:** Iterate `j` from `i - 1` down to `max(0, i - d)`:
     - If `arr[j] >= arr[i]`, a building blocks our path. `break` immediately.
     - Otherwise (`arr[j] < arr[i]`), recursively call `1 + solve(j, arr, d, memo)` and maximize `ans`.
   - Store `ans` in `memo[i]` and return it.
3. In the main function, iterate through every index from `0` to `n - 1`, call `solve` for each, and track the maximum results returned.
4. Return the maximum value found.

--------------------------------------------------------

⏱ Time Complexity:
O(n * d)
- There are `n` unique states (one for each index in the array).
- For each state, we look up to `d` steps to the right and `d` steps to the left.
- With memoization, each state is evaluated exactly once, yielding an upper bound of O(n * d) operations. Given n <= 1000 and d <= 1000, this comfortably runs in a few milliseconds.

📦 Space Complexity:
O(n)
- The `memo` array requires O(n) space.
- The recursion call stack can go up to a maximum depth of O(n) in the worst-case scenario.

*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    int solve(int i, vector<int>& arr, int d, vector<int>& memo) {
        // Return cached result if already computed
        if (memo[i] != -1) {
            return memo[i];
        }
        
        int n = arr.size();
        int ans = 1; // Base case: visiting just the current index
        
        // 1. Explore valid jumps to the right
        for (int j = i + 1; j <= min(n - 1, i + d); j++) {
            if (arr[j] >= arr[i]) {
                break; // Blocked by an equal or taller element
            }
            ans = max(ans, 1 + solve(j, arr, d, memo));
        }
        
        // 2. Explore valid jumps to the left
        for (int j = i - 1; j >= max(0, i - d); j--) {
            if (arr[j] >= arr[i]) {
                break; // Blocked by an equal or taller element
            }
            ans = max(ans, 1 + solve(j, arr, d, memo));
        }
        
        return memo[i] = ans;
    }

public:
    int maxJumps(vector<int>& arr, int d) {
        int n = arr.size();
        vector<int> memo(n, -1);
        int maxVisited = 0;
        
        // Try starting the jump sequence from every possible index
        for (int i = 0; i < n; i++) {
            maxVisited = max(maxVisited, solve(i, arr, d, memo));
        }
        
        return maxVisited;
    }
};