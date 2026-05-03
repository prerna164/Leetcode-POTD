/*
Problem: Rotate String
Link: LeetCode 796

Date: 2026-05-03
Difficulty: Easy
Tags: String, String Matching

🧠 Intuition:

A rotation of a string involves taking a prefix and moving it to the end. 
For example, if s = "abcde":
- Shift 1: "bcdea"
- Shift 2: "cdeab"
- Shift 3: "deabc"
- ... and so on.

The fundamental property of a circular rotation is that if you concatenate 
a string with itself (s + s), the resulting string contains every possible 
rotation as a contiguous substring.

Example:
s = "abcde"
s + s = "abcdeabcde"
        ^^^^^ (Rotation 0)
         ^^^^^ (Rotation 1)
          ^^^^^ (Rotation 2)

If the 'goal' string is a valid rotation of 's', it MUST be a substring 
of 's + s', provided that both strings are of the same length.

--------------------------------------------------------

⚙️ Approach:

1. Length Check:
   If the length of string 's' is not equal to the length of 'goal', 
   it is impossible for 's' to become 'goal' through shifts. Return false.

2. Concatenation:
   Create a new string 'doubled' which is s + s.

3. Substring Search:
   Check if 'goal' exists within 'doubled'. In C++, we use the 
   string::find() method. If the result is not string::npos, 
   the goal is found.

4. Return Result:
   Return true if found, otherwise return false.

--------------------------------------------------------

⏱ Time Complexity:

O(N)

- Concatenating two strings of length N takes O(N).
- The find() function in C++ typically uses an optimized search 
  (like a simplified Boyer-Moore or KMP-based logic) which performs 
  in O(N) time for this scale.

📦 Space Complexity:

O(N)

- We create a new string 'doubled' that stores 2 * N characters.

*/

#include <string>
using namespace std;

class Solution {
public:
    bool rotateString(string s, string goal) {
        // Step 1: Check if lengths are the same
        if (s.length() != goal.length()) {
            return false;
        }

        // Step 2: Concatenate s with itself to cover all rotation possibilities
        string doubled = s + s;

        // Step 3: Check if goal is a substring of the doubled string
        // string::find returns the starting index or string::npos if not found
        if (doubled.find(goal) != string::npos) {
            return true;
        }

        return false;
    }
};