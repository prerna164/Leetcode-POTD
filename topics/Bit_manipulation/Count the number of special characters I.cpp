/*
Problem: Count the number of special characters I (Check if All A's Appear Before All B's / Number of Special Characters I)
Link: LeetCode 3120

Date: 2026-05-26
Difficulty: Easy
Tags: Hash Table, String, Bit Manipulation

🧠 Intuition:
A character is deemed "special" if it co-exists in both its lowercase and uppercase forms anywhere inside the given string. The actual positions or the relative order of these characters do not matter; only their mutual presence is required.

To solve this optimally, we can decouple the problem into 26 distinct slots (corresponding to 'a' through 'z'). If we can track whether the lowercase version has been spotted and whether the uppercase version has been spotted, we can simply count how many slots have both flags toggled to true.

Since there are only 26 English letters, we don't need a heavy, dynamically resizing hash map. A couple of fixed-size boolean frequency arrays or lookup vectors will give us clean, fast, and highly predictable operations.

---

⚙️ Approach:

1. Initialize two boolean arrays/vectors, `hasLower` and `hasUpper`, both of size 26, initialized completely to `false`.
2. Iterate through each character `c` in the string `word`:
* If `c` is a lowercase letter (`'a'` to `'z'`), calculate its alphabet index using `c - 'a'` and set `hasLower[index] = true`.
* If `c` is an uppercase letter (`'A'` to `'Z'`), calculate its alphabet index using `c - 'A'` and set `hasUpper[index] = true`.


3. Initialize a counter `specialCount = 0`.
4. Run a loop from `0` to `25`. For each index `i`, check if both `hasLower[i]` and `hasUpper[i]` are `true`. If they are, increment `specialCount`.
5. Return the final `specialCount`.

---

⏱ Time Complexity:
O(n)

* We iterate through the string `word` of length `n` exactly once to log character occurrences, which takes O(n) time.
* Afterwards, we run a fixed-size loop of exactly 26 iterations to gather the results, which runs in O(1) constant time. Thus, the total time complexity scales linearly with the input size.

📦 Space Complexity:
O(1)

* The memory allocation is limited to two boolean vectors of a constant size 26. Because this auxiliary space does not scale with the size of the input string, the space complexity remains completely stable at O(1).

*/

#include 
#include 
#include 

using namespace std;

class Solution {
public:
int numberOfSpecialChars(string word) {
// Trackers for lowercase and uppercase occurrences across the 26 alphabet characters
vector hasLower(26, false);
vector hasUpper(26, false);

```
    // Log the existence of each character based on its casing
    for (char c : word) {
        if (islower(c)) {
            hasLower[c - 'a'] = true;
        } else if (isupper(c)) {
            hasUpper[c - 'A'] = true;
        }
    }
    
    int specialCount = 0;
    
    // Count characters that succeeded in presenting both lowercase and uppercase variants
    for (int i = 0; i < 26; i++) {
        if (hasLower[i] && hasUpper[i]) {
            specialCount++;
        }
    }
    
    return specialCount;
}

```

};