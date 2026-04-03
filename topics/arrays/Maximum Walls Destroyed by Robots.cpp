/*
Problem: Maximum Walls Destroyed by Robots
Link: https://leetcode.com/problems/maximum-walls-destroyed-by-robots/

Date: 2026-04-02
Difficulty: Hard
Tags: Array, Binary Search, Dynamic Programming, Sorting

-----------------------------------------------------

🧠 Intuition :-
- Each robot has exactly one bullet and can shoot either LEFT or RIGHT.
- While shooting, the bullet stops if it hits another robot, so each robot’s effective range is limited by its adjacent robots.
- The tricky part is that different robots' shooting ranges can overlap, leading to double counting of walls.
- So, we need a way to:
  1. Choose direction (LEFT or RIGHT) for each robot
  2. Maximize total unique walls destroyed
- This leads to a DP approach where we track the best result depending on the previous robot’s decision.

-----------------------------------------------------

⚙️ Approach:
1. Pair each robot with its distance and sort them based on position.
2. Sort the walls array for binary search.

3. For each robot:
    - Restrict LEFT range:
        [max(prev_robot + 1, robot - dist), robot]
    - Restrict RIGHT range:
        [robot, min(next_robot - 1, robot + dist)]

4. Use binary search to count:
    - L = number of walls destroyed if shooting LEFT
    - R = number of walls destroyed if shooting RIGHT

5. Maintain two DP states:
    - left  = max walls if current robot shoots LEFT
    - right = max walls if current robot shoots RIGHT

6. Handle overlap:
    - If previous robot shot RIGHT and current shoots LEFT,
      overlapping walls must not be double counted.
    - overlap = max(0, previous_right_boundary - current_left_start)

7. Transition:
    - newLeft  = max(left + L, right + L - overlap)
    - newRight = max(left, right) + R

8. Update states and continue.

9. Final answer = max(left, right)

-----------------------------------------------------

⏱ Time Complexity:
O(n log n + m log m)
- Sorting robots and walls
- Binary search per robot

📦 Space Complexity:
O(n)
- For storing robot-distance pairs

-----------------------------------------------------
*/

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxWalls(vector<int>& robots, vector<int>& distance, vector<int>& walls) {
        int n = robots.size();

        // pair robots with distance
        vector<pair<long long, long long>> z;
        for(int i = 0; i < n; i++) {
            z.push_back({robots[i], distance[i]});
        }

        sort(z.begin(), z.end());
        sort(walls.begin(), walls.end());

        long long left = 0, right = 0;
        long long ri = 0; // right boundary index of previous robot

        for(int i = 0; i < n; i++) {
            long long robot = z[i].first;
            long long dist = z[i].second;

            long long prev = (i > 0 ? z[i - 1].first : 0);
            long long next = (i < n - 1 ? z[i + 1].first : (long long)2e9);

            // LEFT interval
            long long leftStart = max(prev + 1, robot - dist);
            int l = lower_bound(walls.begin(), walls.end(), leftStart) - walls.begin();
            int ml = upper_bound(walls.begin(), walls.end(), robot) - walls.begin();

            long long L = ml - l;

            // RIGHT interval
            long long rightEnd = min(next - 1, robot + dist);
            int mr = lower_bound(walls.begin(), walls.end(), robot) - walls.begin();
            int r = upper_bound(walls.begin(), walls.end(), rightEnd) - walls.begin();

            long long R = r - mr;

            // overlap handling
            long long overlap = max(0LL, ri - l);

            long long newLeft = max(left + L, right + L - overlap);
            long long newRight = max(left, right) + R;

            left = newLeft;
            right = newRight;
            ri = r; // update right boundary
        }

        return (int)max(left, right);
    }
};