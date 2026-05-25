/*
Problem: Jump Game VII
Link: LeetCode 1871

Date: 2026-05-25
Difficulty: Medium
Tags: String, Dynamic Programming, Breadth-First Search, Sliding Window

🧠 Intuition:
We start at index 0 and want to find out if we can reach the last index (n - 1). From any index `i`, we can transition to an index `j` if `j` is within the range [i + minJump, min(i + maxJump, n - 1)] and s[j] == '0'.

If we use a standard Breadth-First Search (BFS) or Dynamic Programming, we would look through every index in the range for every valid `i`. In the worst-case scenario, this results in an O(n * (maxJump - minJump)) time complexity, which will result in a Time Limit Exceeded (TLE) because n can be up to 10^5.

To make this efficient, we must avoid processing the same indices multiple times. We can introduce a variable `far` that keeps track of the maximum index we have already added to our BFS queue or examined. 

When we are at an index `i`, instead of starting our scan from `i + minJump`, we can start from `max(i + minJump, far + 1)`. This simple constraint guarantees that every index in the string is looked at and added to the queue at most once, transforming our algorithm into a highly efficient linear-time solution.

--------------------------------------------------------

⚙️ Approach:
1. First, check if the last character of the string `s[n - 1]` is '1'. If it is, it's impossible to reach, so return `false` immediately.
2. Initialize a standard BFS queue `q` and push the starting index `0` onto it.
3. Maintain a variable `far = 0` to store the highest index that has been considered for exploration so far.
4. While the queue is not empty:
   - Pop the current index `curr` from the front of the queue.
   - If `curr` equals `n - 1`, we have successfully reached the destination, so return `true`.
   - Calculate the valid jumping window boundaries:
     - `start = max(curr + minJump, far + 1)` : This prevents re-scanning segments already processed by previous states.
     - `end = min(curr + maxJump, n - 1)`
   - Loop `j` from `start` to `end`:
     - If `s[j] == '0'`, it's a valid, reachable zero. Push `j` into the queue.
   - Update `far = max(far, curr + maxJump)` to ensure future nodes do not overlap with the range we just covered.
5. If the queue becomes empty and the last index hasn't been reached, return `false`.

--------------------------------------------------------

⏱ Time Complexity:
O(n)
- Every index from `0` to `n - 1` is pushed to and popped from the queue at most once.
- The tracking variable `far` ensures that the inner loop's lower bound continually shifts forward, preventing redundant visits. Thus, the inner loop pointer moves across the string linearly, taking O(n) total time.

📦 Space Complexity:
O(n)
- In the worst-case scenario, the BFS queue can store up to O(n) indices simultaneously.

*/

#include <string>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.length();
        // If the target destination is blocked, it's unreachable
        if (s[n - 1] == '1') {
            return false;
        }

        queue<int> q;
        q.push(0);
        
        // 'far' keeps track of the furthest index we have already evaluated/passed
        int far = 0;

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            // Successfully reached the final index
            if (curr == n - 1) {
                return true;
            }

            // Set bounds for the sliding window jump zone
            // We start from max(curr + minJump, far + 1) to completely skip redundant checks
            int start = max(curr + minJump, far + 1);
            int end = min(curr + maxJump, n - 1);

            // Enqueue all valid and unvisited indices within the jump range
            for (int j = start; j <= end; ++j) {
                if (s[j] == '0') {
                    q.push(j);
                }
            }

            // Update the furthest boundary covered by the current position's max range
            far = max(far, curr + maxJump);
        }

        return false;
    }
};