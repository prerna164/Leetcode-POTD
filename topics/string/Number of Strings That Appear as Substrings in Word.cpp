/*
Problem: Number of Strings That Appear as Substrings in Word
Link: Contiguous Sequence String Pattern Matching

Date: 2026-06-29
Difficulty: Easy
Tags: String, Simulation

Intuition:
The problem asks us to count how many strings in the `patterns` array exist as substrings within a given string `word`. 
A substring is a contiguous block of characters. 

In C++, the standard string class provides a built-in function `word.find(p)`. 
- If `p` is found inside `word`, it returns the starting index position of the match.
- If `p` is not found, it returns the constant value `string::npos`.

Given the highly constrained input sizes (lengths up to 100), we can safely iterate through each pattern string `p` in the `patterns` vector and check if `word.find(p) != string::npos`. If it matches, we increment our tracking counter.

---

Approach:

1. Initialization:
   * Maintain a count variable `matching_substrings = 0`.

2. String Search Simulation:
   * Use a range-based loop to inspect each string `p` inside the `patterns` array.
   * Perform the substring query: `if (word.find(p) != string::npos)`.
   * Increment `matching_substrings` upon finding a valid match.

3. Return Payload:
   * Return the accumulated `matching_substrings` count.

---

⏱ Time Complexity:
O(M * N)

* Let M be the number of patterns and N be the maximum length of `word` or `patterns[i]`.
* For each pattern, the `std::string::find` function searches for a match in $O(N)$ time in the worst case.
* With $M \le 100$ and $N \le 100$, the total number of character comparison operations is bounded roughly around $10^4$, running instantaneously in less than 1 millisecond.

Space Complexity:
O(1) Auxiliary Space

* The checking is done in-place without generating copies or creating supplementary lookup maps, keeping the storage completely constant.
*/

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
    int numOfStrings(vector<string>& patterns, string word) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int matching_substrings = 0;

        // Sequentially evaluate if each individual pattern can be found inside the word
        for (const string& p : patterns) {
            if (word.find(p) != string::npos) {
                matching_substrings++;
            }
        }

        return matching_substrings;
    }
};