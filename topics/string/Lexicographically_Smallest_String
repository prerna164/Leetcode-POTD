/*Problem: Lexicographically Smallest Generated String 
Link: https://leetcode.com/problems/lexicographically-smallest-generated-string/

Date: 2026-03-31
Difficulty: Hard
Tags: String, Greedy

------------------------------------------------------------
🧠 Intuition:
To solve this problem, we need to balance three things:
1. Fixed requirements ('T')
2. Forbidden patterns ('F')
3. Lexicographically smallest result

- 'T' constraints are strict → we MUST match str2
- 'F' constraints are flexible → we must AVOID matching str2

Since we want the smallest string, we try to use 'a' everywhere.
But blindly doing this may accidentally create forbidden matches.

So the idea is:
1. First satisfy all 'T' constraints (non-negotiable)
2. Then ensure 'F' constraints are not violated
3. Finally fill remaining positions greedily with smallest characters

-----------------------------------------------------

⚙️ Approach:

🔹 Phase 1: Build Fixed Skeleton
- Create result string of size (n + m - 1) filled with '?'
- For every index i where str1[i] == 'T':
  → Place str2 starting at index i
  → If conflict occurs → return ""

-----------------------------------------------------

🔹 Phase 2: Pre-check 'F'
- For every index i where str1[i] == 'F':
  → If substring already fully equals str2 (no '?')
  → Return "" (invalid)

-----------------------------------------------------

🔹 Phase 3: Greedy Filling
- Traverse result string
- For each '?' position:
  1. Try placing 'a'
  2. Check if it creates forbidden match for any 'F'
  3. If safe → keep 'a'
  4. Else → place 'b' (breaks pattern)

-----------------------------------------------------

⏱ Time Complexity:
O(n * m)

- Filling 'T': O(n * m)
- Checking 'F' and greedy fill: O(n * m)

-----------------------------------------------------

📦 Space Complexity:
O(n + m)

- Result string of size (n + m - 1)

-----------------------------------------------------

💡 Why only 'a' and 'b' are enough?

If placing 'a' creates a forbidden match (equals str2),
then changing that character to 'b' will definitely break the match.

So:
- 'a' → for lexicographically smallest
- 'b' → for breaking invalid patterns

No need for 'c', 'd', etc.

-----------------------------------------------------
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string generateString(string str1, string str2) {
        int n = str1.length();
        int m = str2.length();
        int totalLen = n + m - 1;
        string res(totalLen, '?');

        // Step 1: Fill all 'T' constraints
        for (int i = 0; i < n; ++i) {
            if (str1[i] == 'T') {
                for (int j = 0; j < m; ++j) {
                    if (res[i + j] != '?' && res[i + j] != str2[j]) {
                        return ""; // Contradiction between 'T's
                    }
                    res[i + j] = str2[j];
                }
            }
        }

        // Step 2: Preliminary check for 'F' constraints already filled by 'T's
        for (int i = 0; i < n; ++i) {
            if (str1[i] == 'F') {
                bool match = true;
                bool hasQuestion = false;
                for (int j = 0; j < m; ++j) {
                    if (res[i + j] == '?') {
                        hasQuestion = true;
                        match = false;
                        break;
                    }
                    if (res[i + j] != str2[j]) {
                        match = false;
                        break;
                    }
                }
                if (match && !hasQuestion) return ""; // 'F' violated by 'T' placements
            }
        }

        // Step 3: Greedy fill remaining '?'
        for (int i = 0; i < totalLen; ++i) {
            if (res[i] == '?') {
                // Try 'a'
                res[i] = 'a';
                if (isValid(res, str1, str2, i)) {
                    continue;
                }
                // If 'a' fails, try 'b'
                res[i] = 'b';
                if (isValid(res, str1, str2, i)) {
                    continue;
                }
                // If both fail, impossible
                return "";
            }
        }

        return res;
    }

private:
    // Checks if the character placed at res[currIdx] violates any 'F' constraints
    bool isValid(const string& res, const string& str1, const string& str2, int currIdx) {
        int n = str1.size();
        int m = str2.size();
        
        // We only need to check 'F' constraints that overlap with the current index
        int start = max(0, currIdx - m + 1);
        int end = min(n - 1, currIdx);

        for (int i = start; i <= end; ++i) {
            if (str1[i] == 'F') {
                bool match = true;
                for (int j = 0; j < m; ++j) {
                    if (res[i + j] == '?' || res[i + j] != str2[j]) {
                        match = false;
                        break;
                    }
                }
                if (match) return false;
            }
        }
        return true;
    }
};