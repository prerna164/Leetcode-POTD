/*
Problem: Decode the Slanted Ciphertext
Link: https://leetcode.com/problems/decode-the-slanted-ciphertext/

Date: 2026-04-04
Difficulty: Medium
Tags: String, Simulation, Matrix

-----------------------------------------------------

🧠 Intuition:
- The encoded string represents a 2D matrix read row-by-row.
- The original text was placed diagonally starting from the first row.
- To decode, we need to find the number of columns and traverse the 
  matrix diagonally: from (r, c) to (r+1, c+1).

-----------------------------------------------------

⚙️ Approach:
1. Calculate columns: cols = encodedText.length() / rows.
2. Iterate through each possible starting column `i` in the top row (row 0).
3. For each starting column, move diagonally by incrementing both 
   row `r` and column `c` until boundaries are hit.
4. Use the formula `index = r * cols + c` to access the 1D string as a 2D grid.
5. Trim trailing spaces from the final result.

-----------------------------------------------------

⏱ Time Complexity:
O(N) - where N is the length of encodedText. We visit each character once.

📦 Space Complexity:
O(N) - to store and return the decoded string.

-----------------------------------------------------
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string decodeCiphertext(string encodedText, int rows) {
        if (rows == 1) return encodedText;

        int n = encodedText.length();
        int cols = n / rows;
        string res = "";

        // Start from each column in the first row
        for (int i = 0; i < cols; ++i) {
            // Traverse diagonally down-right
            for (int r = 0, c = i; r < rows && c < cols; ++r, ++c) {
                res += encodedText[r * cols + c];
            }
        }

        // Remove trailing spaces from the end of the original text
        while (!res.empty() && res.back() == ' ') {
            res.pop_back();
        }

        return res;
    }
};