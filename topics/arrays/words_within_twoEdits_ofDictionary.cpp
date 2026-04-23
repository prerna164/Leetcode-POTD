/*
Problem: 2452. daily/2026-04/2026-04-22.cpp
Link: https://leetcode.com/problems/words-within-two-edits-of-dictionary/

Difficulty: Medium
Tags: Array, String, Simulation

-----------------------------------------------------

🧠 Intuition:
- We are looking for query words that are "close enough" to any word in the dictionary. 
- "Close enough" is defined as having a Hamming distance (number of positions with different characters) of 2 or less.
- Since all words in both arrays have the same length n, we can perform a direct index-by-index comparison.
- If a query word matches even one dictionary word within the allowed 2 edits, it's a valid result. 

-----------------------------------------------------

⚙️ Approach:
1. Outer Loop: Iterate through each word `q` in the `queries` array.
2. Inner Loop: For each `q`, iterate through each word `d` in the `dictionary`.
3. Character Comparison: Compare `q` and `d` character by character.
   - Maintain a counter `diffs` for mismatched characters.
   - Optimization: If `diffs` exceeds 2, stop comparing the current dictionary word `d` and move to the next one.
4. Validation: If the loop finishes and `diffs <= 2`, the query word `q` is valid. Add it to the result list and break the inner loop.

-----------------------------------------------------

⏱ Time Complexity:
O(Q * D * N) - where Q is queries length, D is dictionary length, and N is word length.
With constraints (100 * 100 * 100), this is ~10^6 operations.

📦 Space Complexity:
O(1) - Excluding the space used by the result vector.

-----------------------------------------------------
*/

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> twoEditWords(vector<string>& queries, vector<string>& dictionary) {
        vector<string> result;
        
        // Iterate through each word in queries
        for (const string& q : queries) {
            bool foundMatch = false;
            
            // Check against every word in the dictionary
            for (const string& d : dictionary) {
                int diffs = 0;
                
                // Compare characters at each index
                for (int i = 0; i < q.length(); ++i) {
                    if (q[i] != d[i]) {
                        diffs++;
                    }
                    
                    // Early exit if edits required are already more than 2
                    if (diffs > 2) break;
                }
                
                // If the word matches within the 2-edit limit
                if (diffs <= 2) {
                    foundMatch = true;
                    break;
                }
            }
            
            // If at least one dictionary word was within 2 edits
            if (foundMatch) {
                result.push_back(q);
            }
        }
        
        return result;
    }
};