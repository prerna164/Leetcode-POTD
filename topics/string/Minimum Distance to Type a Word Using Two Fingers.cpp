/*
Problem: 1320. Minimum Distance to Type a Word Using Two Fingers
Link: https://leetcode.com/problems/minimum-distance-to-type-a-word-using-two-fingers/

Difficulty: Hard
Tags: Dynamic Programming, Memoization, String

-----------------------------------------------------

🧠 Intuition:
- At any point in time, one finger must be on the character we just typed (word[i-1]). 
- Therefore, the state of our system only depends on:
  1. The index of the character we need to type next.
  2. The position of the "other" finger (the one not on word[i-1]).
- The first time each finger is used, it can be placed anywhere for free (distance 0). 
- We use a 2D DP table (or memoization) where dp[i][j] is the minimum distance 
  to type word starting from index 'i', given the other finger is at position 'j'.

-----------------------------------------------------

⚙️ Approach:
1. Coordinate Mapping: Convert letters 'A'-'Z' to coordinates (row, col) using:
   row = char_val / 6, col = char_val % 6.
2. Distance Function: Calculate Manhattan distance: |x1 - x2| + |y1 - y2|. 
   If a finger is "unplaced" (represented by index 26), distance is 0.
3. Recursive DP (Memoization):
   - Base Case: If we reached the end of the word, return 0.
   - Transition: For word[idx], we have two choices:
     a) Move the finger currently at word[idx-1] to word[idx].
     b) Move the "other" finger (currently at 'otherFinger') to word[idx].
   - Take the minimum of these two choices and store it.
4. Initialization: Start the recursion from the second character (index 1), with 
   the first finger already on word[0] (cost 0) and the second finger unplaced (26).

-----------------------------------------------------

⏱ Time Complexity:
O(N * 26) - Where N is the length of the word. We explore each state (index, other_finger) 
at most once. With N up to 300, this is roughly 7,800 operations.

📦 Space Complexity:
O(N * 26) - For the memoization table to store results of subproblems.

-----------------------------------------------------
*/

#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;

class Solution {
    int memo[301][27];

    // Calculate Manhattan distance between two finger positions
    int getDist(int from, int to) {
        if (from == 26) return 0; // Finger hasn't been placed yet
        int x1 = from / 6, y1 = from % 6;
        int x2 = to / 6, y2 = to % 6;
        return abs(x1 - x2) + abs(y1 - y2);
    }

    int solve(int idx, int otherFinger, const string& word) {
        // Base case: typed all letters
        if (idx == word.length()) return 0;

        // Memoization check
        if (memo[idx][otherFinger] != -1) return memo[idx][otherFinger];

        int currPos = word[idx] - 'A';
        int prevPos = word[idx - 1] - 'A';

        // Choice 1: Use the finger that typed the previous character
        int cost1 = getDist(prevPos, currPos) + solve(idx + 1, otherFinger, word);

        // Choice 2: Use the "other" finger
        int cost2 = getDist(otherFinger, currPos) + solve(idx + 1, prevPos, word);

        return memo[idx][otherFinger] = min(cost1, cost2);
    }

public:
    int minimumDistance(string word) {
        memset(memo, -1, sizeof(memo));
        
        // Start from index 1. 
        // Finger 1 is at word[0], Finger 2 is "unplaced" (represented by 26).
        return solve(1, 26, word);
    }
};