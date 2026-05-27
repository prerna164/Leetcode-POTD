/*
Problem: Count the number of special characters II (Find Special Substrings / Number of Special Letters)
Link: LeetCode 3121

Date: 2026-05-27
Difficulty: Medium
Tags: String, Hash Table, Array

Intuition:
A lowercase letter is "special" if and only if:
1. It appears in the string in lowercase format.
2. It appears in the string in uppercase format.
3. Every lowercase occurrence happens strictly before the FIRST uppercase occurrence.

Instead of tracking all occurrences, we only need to look at two critical positions for each character from 'a' to 'z':
- The *last* index where the lowercase character appears. If there are multiple lowercase letters, the last one is the most critical because it is closest to any uppercase letters.
- The *first* index where the uppercase character appears. Any subsequent uppercase characters don't restrict lowercase characters further; only the first uppercase character sets the strict boundary.

If a letter satisfies both conditions (found in both cases) and the index of its last lowercase occurrence is strictly smaller than the index of its first uppercase occurrence, then all lowercase occurrences inherently appear before any uppercase occurrence.

--------------------------------------------------------
Approach:
1. Initialize two lookup tables/arrays of size 26 with a sentinel value (like -1):
   - `last_lower`: to keep track of the *last seen* index of each lowercase letter.
   - `first_upper`: to keep track of the *first seen* index of each uppercase letter.
2. Traverse the string `word` from left to right:
   - If the character `c` is lowercase, update `last_lower[c - 'a'] = i`. This naturally overwrites previous indices, leaving the absolute last index at the end of the loop.
   - If the character `c` is uppercase, check if `first_upper[c - 'A']` is still -1. If it is, update it to `i`. If it's already set, ignore it to preserve the *first* occurrence.
3. Initialize a counter `specialCount = 0`.
4. Loop through all 26 alphabets (from 0 to 25):
   - Check if the character exists in both forms: `last_lower[i] != -1 && first_upper[i] != -1`.
   - Check if the condition holds: `last_lower[i] < first_upper[i]`.
   - If both are true, increment `specialCount`.
5. Return `specialCount`.

--------------------------------------------------------
⏱ Time Complexity:
O(n)
- We iterate through the string of length `n` exactly once to log the indices.
- Afterwards, we run a constant-time loop of 26 iterations to check the criteria. This yields a linear time complexity proportional to the size of the string.

Space Complexity:
O(1)
- The auxiliary storage used consists of two arrays (`last_lower` and `first_upper`), each of fixed size 26. Since the memory allocation does not scale with the size of the input string `word`, space complexity is strictly constant.
*/

#include <string>
#include <vector>
#include <cctype>
using namespace std;

class Solution {
public:
    int numberOfSpecialChars(string word) {
        // Vectors initialized to -1 to represent "not found"
        vector<int> last_lower(26, -1);
        vector<int> first_upper(26, -1);
        
        // Single pass to record positions
        for (int i = 0; i < word.length(); ++i) {
            char c = word[i];
            if (islower(c)) {
                last_lower[c - 'a'] = i; // Always update to get the LAST occurrence
            } else if (isupper(c)) {
                if (first_upper[c - 'A'] == -1) {
                    first_upper[c - 'A'] = i; // Only update if it's the FIRST occurrence
                }
            }
        }
        
        int specialCount = 0;
        
        // Check conditions for all 26 letters
        for (int i = 0; i < 26; ++i) {
            if (last_lower[i] != -1 && first_upper[i] != -1 && last_lower[i] < first_upper[i]) {
                specialCount++;
            }
        }
        
        return specialCount;
    }
};