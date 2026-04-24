/*
Problem: Furthest Point From Origin
Link: https://leetcode.com/problems/furthest-point-from-origin/

Date: 2026-04-24
Difficulty: Easy
Tags: String, Counting, Greedy

-----------------------------------------------------

🧠 Intuition:
- We are moving on a 1D number line.
- 'L' moves us -1, 'R' moves us +1, and '_' is a wildcard that can be either.
- To be as far as possible from zero, we want our final position to have 
  the largest possible absolute value.
- The best strategy is to look at the net difference between fixed 'L' and 'R' 
  moves, then assign ALL wildcards ('_') to the direction that is already 
  further away to maximize that distance.

-----------------------------------------------------

⚙️ Approach:
1. Count the number of 'L' characters (countL).
2. Count the number of 'R' characters (countR).
3. Count the number of '_' characters (wildcards).
4. Calculate the net distance from fixed moves: abs(countL - countR).
5. Add all wildcards to this net distance: 
   Result = abs(countL - countR) + wildcards.

-----------------------------------------------------

⏱ Time Complexity:
- O(n): We iterate through the string 'moves' exactly once to count characters.

📦 Space Complexity:
- O(1): We only use a few integer variables regardless of input size.

-----------------------------------------------------
*/

#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
    int furthestDistanceFromOrigin(string moves) {
        int countL = 0;
        int countR = 0;
        int wildcards = 0;

        // Traverse the string once to collect counts
        for (char c : moves) {
            if (c == 'L') {
                countL++;
            } else if (c == 'R') {
                countR++;
            } else {
                wildcards++;
            }
        }

        // Maximum distance is the bias of fixed moves plus all wildcards
        return abs(countL - countR) + wildcards;
    }
};