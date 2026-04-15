/*
Problem: 2515. Shortest Distance to Target String in a Circular Array
Link: https://leetcode.com/problems/shortest-distance-to-target-string-in-a-circular-array/

Date: 2026-04-15
Difficulty: Easy
Tags: Array, String

-----------------------------------------------------

🧠 Intuition:
- The problem asks for the shortest path in a circular array. In a circular structure, 
  you can reach any index by moving either clockwise (right) or counter-clockwise (left).
- For any target index `i`, the "right" distance is simply the absolute difference 
  between `i` and `startIndex`.
- The "left" distance (the wrap-around path) is the remaining portion of the array 
  length that isn't covered by the direct absolute distance.
- Since we want the *shortest* distance, for every occurrence of the target, we 
  calculate both paths and keep track of the overall minimum.

-----------------------------------------------------

⚙️ Approach:
1. Initialize `minDistance` to a very large value (or `INT_MAX`).
2. Traverse the `words` array from `i = 0` to `n-1`.
3. If `words[i]` matches the `target`:
   - Calculate the direct distance: `d = abs(i - startIndex)`.
   - Calculate the circular distance: `circular_d = n - d`.
   - The shortest distance to this specific index is `min(d, circular_d)`.
   - Update our global `minDistance` with this value.
4. After checking all indices, if `minDistance` was updated, return it.
5. If `minDistance` remains unchanged, the target was never found; return -1.

-----------------------------------------------------

⏱ Time Complexity:
O(N * L) — where N is the number of strings in the array and L is the average 
length of the strings. We perform a single pass through the array, and each 
string comparison takes O(L) time.

📦 Space Complexity:
O(1) — We only use a few integer variables to store distances and the array size. 
No extra data structures are required.

-----------------------------------------------------
*/

#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int closestTarget(vector<string>& words, string target, int startIndex) {
        int n = words.size();
        int minDistance = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (words[i] == target) {
                // Step 1: Calculate the standard absolute distance
                int absDist = abs(i - startIndex);
                
                // Step 2: Calculate the circular distance (wrapping around the ends)
                // Step 3: Find the minimum of the two possible directions
                int currentDistance = min(absDist, n - absDist);
                
                // Step 4: Update the global minimum distance found so far
                minDistance = min(minDistance, currentDistance);
            }
        }

        // If minDistance is still INT_MAX, the target string doesn't exist in the array
        return (minDistance == INT_MAX) ? -1 : minDistance;
    }
};