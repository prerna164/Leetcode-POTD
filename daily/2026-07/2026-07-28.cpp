/*
Problem:  Smallest Palindromic Rearrangement I
Link: Lhttps://leetcode.com/problems/smallest-palindromic-rearrangement-i/submissions/2084398340/?envType=daily-question&envId=2026-07-28

Date: 2026-07-28
Difficulty: Medium
Tags: String, Hash Table, Greedy, Sorting

Intuition:
We are given a string `s` that is guaranteed to be palindromic (or can be permuted into a palindrome).
We want to construct the lexicographically smallest palindrome formed by permuting `s`.

Key Observations:
1. Symmetry of Palindromes:
   - A palindrome reads the same forwards and backwards.
   - The first half determines the second half entirely (the second half is the reverse of the first half).
   - If `s` has an odd length, exactly one character will have an odd frequency, which must be placed in the exact center.

2. Lexicographical Minimization:
   - To make the entire palindrome as small as possible lexicographically, we must make its first half as small as possible.
   - Greedy Strategy: Collect half of the frequency of each character, sort these characters in ascending order (a-z), and place them in the left half of the string.

---

Approach:

1. Frequency Counting:
   * Count the frequency of each character in `s` using an array/vector of size 26.

2. Constructing the Left Half & Middle Character:
   * Iterate through characters from 'a' to 'z':
     - Append `freq[c] / 2` instances of character `c` to a string `half`.
     - If `freq[c]` is odd, save `c` as the `mid` character.

3. Assembling the Result:
   * Construct the final string as: `half` + (`mid` if exists) + `reverse(half)`.
   * Return the result.

---

⏱ Time Complexity:
O(N)

* Counting frequencies takes O(N) where N = |s|.
* Constructing `half` takes O(N) total character appends.
* Reversing `half` takes O(N/2) = O(N) time.
* Overall Runtime: O(N) linear time.

Space Complexity:
O(N) Auxiliary Space

* We store the string `half` and output string, requiring O(N) space.
* The frequency table takes constant O(1) space (26 elements).
*/

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    string smallestPalindrome(string s) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c - 'a']++;
        }

        string half = "";
        char mid = '\0';

        // Iterate from 'a' to 'z' to ensure lexicographically smallest order
        for (int i = 0; i < 26; ++i) {
            char c = 'a' + i;
            half.append(freq[i] / 2, c);
            if (freq[i] % 2 != 0) {
                mid = c;
            }
        }

        string rev_half = half;
        reverse(rev_half.begin(), rev_half.end());

        if (mid != '\0') {
            return half + mid + rev_half;
        }
        return half + rev_half;
    }
};