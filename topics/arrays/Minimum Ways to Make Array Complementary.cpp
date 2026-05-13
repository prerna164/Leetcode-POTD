/*
Problem: Minimum Ways to Make Array Complementary
Link: LeetCode 1674

Date: 2026-05-13
Difficulty: Medium
Tags: Array, Prefix Sum, Difference Array

🧠 Intuition:

We want all pairs (nums[i], nums[n-1-i]) to sum up to the same target value S.
Since each number is between 1 and 'limit', the possible range for S is [2, 2 * limit].

For any single pair (a, b), let's assume a <= b. 
How many moves are needed to make their sum equal to S?

1. To get 0 moves: 
   S must be exactly a + b.

2. To get 1 move:
   We can change either 'a' to something else or 'b' to something else.
   The smallest sum we can get with 1 move is (a + 1) [by changing b to 1].
   The largest sum we can get with 1 move is (b + limit) [by changing a to limit].
   So, 1 move is sufficient if S is in range [min(a, b) + 1, max(a, b) + limit], 
   excluding the case where S = a + b (which is 0 moves).

3. To get 2 moves:
   If S is outside the 1-move range, we must change both numbers.
   This happens if S < min(a, b) + 1 or S > max(a, b) + limit.

Instead of iterating through every possible target S for every pair (which is O(N * Limit)), 
we use a Difference Array to track how many moves are added/subtracted as S increases. 
By calculating the net change at specific boundaries, we can find the total moves 
for all S values in a single sweep.

--------------------------------------------------------

⚙️ Approach:

1. Initialize a difference array `diff` of size 2 * limit + 2.

2. For each pair (a, b) in the first half of the array:
   - Identify the boundaries:
     - Absolute Minimum possible sum: 2
     - 1-move lower bound: min(a, b) + 1
     - The target sum: a + b
     - 1-move upper bound: max(a, b) + limit
     - Absolute Maximum possible sum: 2 * limit

3. Apply updates to the `diff` array:
   - Start by assuming 2 moves for every S in [2, 2 * limit]:
     diff[2] += 2, diff[2 * limit + 1] -= 2.
   - For the 1-move range [min(a, b) + 1, max(a, b) + limit]:
     We need only 1 move instead of 2. So, subtract 1:
     diff[min(a, b) + 1] -= 1, diff[max(a, b) + limit + 1] += 1.
   - For the 0-move point (a + b):
     We need 0 moves instead of 1. So, subtract another 1:
     diff[a + b] -= 1, diff[a + b + 1] += 1.

4. Perform a prefix sum (sweep line) over the `diff` array from 2 to 2 * limit.
   The value at each index 's' represents the total moves required if the target sum is 's'.

5. The answer is the minimum value found during the sweep.

--------------------------------------------------------

⏱ Time Complexity:

O(n + limit)

- We iterate through n/2 pairs to fill the difference array: O(n).
- We iterate through the difference array up to 2 * limit: O(limit).

📦 Space Complexity:

O(limit)

- We use a difference array of size 2 * limit + 2.

*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minMoves(vector<int>& nums, int limit) {
        int n = nums.size();
        // Difference array to track change in moves for each possible target sum S.
        // Range of S is [2, 2 * limit].
        vector<int> diff(2 * limit + 2, 0);

        for (int i = 0; i < n / 2; ++i) {
            int a = nums[i];
            int b = nums[n - 1 - i];

            // 1. Default: 2 moves for all sums in [2, 2 * limit]
            diff[2] += 2;
            diff[2 * limit + 1] -= 2;

            // 2. Reduce to 1 move for the range [min(a, b) + 1, max(a, b) + limit]
            int left = min(a, b) + 1;
            int right = max(a, b) + limit;
            diff[left] -= 1;
            diff[right + 1] += 1;

            // 3. Reduce to 0 moves for the specific point a + b
            diff[a + b] -= 1;
            diff[a + b + 1] += 1;
        }

        int min_moves = n; // Initialize with max possible moves (change all n/2 pairs twice)
        int current_moves = 0;
        
        // Sweep Line: Calculate prefix sum to find the cost for each target sum S
        for (int s = 2; s <= 2 * limit; ++s) {
            current_moves += diff[s];
            min_moves = min(min_moves, current_moves);
        }

        return min_moves;
    }
};