/*
Problem: 2078. Two Furthest Houses With Different Colors
Link: https://leetcode.com/problems/two-furthest-houses-with-different-colors/

Difficulty: Easy
Tags: Array, Greedy

-----------------------------------------------------

🧠 Intuition:
- To maximize the distance abs(i - j), we want the two houses to be as far apart as possible.
- The maximum possible distance in any array is between the first house (index 0) and the last house (index n-1).
- If colors[0] != colors[n-1], the answer is simply the full length of the street minus one.
- If they are the same color, the optimal house must be either:
    1. The furthest house from the left (index 0) that has a different color.
    2. The furthest house from the right (index n-1) that has a different color.
- Since we only need to check these two specific scenarios to find the global maximum, a greedy approach works perfectly.

-----------------------------------------------------

⚙️ Approach:
1. Initialize n as the size of the colors array.
2. Search from Right to Left:
   - Start from the last house (n-1) and move towards index 0.
   - The first house you find that has a different color than colors[0] is the furthest house from the start.
   - Update maxDist and break.
3. Search from Left to Right:
   - Start from the first house (0) and move towards index n-1.
   - The first house you find that has a different color than colors[n-1] is the furthest house from the end.
   - Update maxDist and break.
4. Return the maximum of the two distances found.

-----------------------------------------------------

⏱ Time Complexity:
O(N) - We perform at most two linear passes through the array.

📦 Space Complexity:
O(1) - We use a constant amount of extra space for variables.

-----------------------------------------------------
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxDistance(vector<int>& colors) {
        int n = colors.size();
        int maxDist = 0;

        // Step 1: Check the furthest house from the left endpoint (index 0)
        for (int i = n - 1; i >= 0; i--) {
            if (colors[i] != colors[0]) {
                maxDist = max(maxDist, i);
                break; // Greedy: the first one we hit from the right is the furthest
            }
        }

        // Step 2: Check the furthest house from the right endpoint (index n-1)
        for (int i = 0; i < n; i++) {
            if (colors[i] != colors[n - 1]) {
                maxDist = max(maxDist, (n - 1) - i);
                break; // Greedy: the first one we hit from the left is the furthest
            }
        }

        return maxDist;
    }
};