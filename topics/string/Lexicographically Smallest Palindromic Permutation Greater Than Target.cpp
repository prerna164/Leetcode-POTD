/*
Problem: Lexicographically Smallest Palindromic Permutation Greater Than Target
Link: LeetCode (Lexicographically Smallest Palindromic Permutation Greater Than Target)

Difficulty: Medium / Hard
Tags: String, Greedy, Palindrome, Backtracking, Counting

Intuition:
A palindrome of length N is completely determined by its first half of length M = (N + 1) / 2.
- The second half is simply the reverse of the first half (excluding the middle character if N is odd).
- Therefore, finding the lexicographically smallest palindromic permutation strictly greater than `target` boils down to constructing a valid first half string `H` of length M such that:
  1. `H` is constructed using half of the characters available in `s` (plus the single odd character in the middle if N is odd).
  2. The full palindrome formed by `H` is lexicographically strictly greater than `target`.

Valid Palindrome Check:
- At most one character in `s` can have an odd frequency count. If more than one character has an odd frequency, no palindromic permutation exists, so we immediately return `""`.

First Half Construction:
Let `half_len = (N + 1) / 2`.
We can use a backtrack/greedy approach by maximizing the length `i` of the matched prefix with `target[0...i-1]`.
For a fixed match length `i` (from `half_len` down to `0`):
1. Check if the prefix `target[0...i-1]` can be formed using available half counts of `s`.
2. Try placing a character `c > target[i]` at index `i`.
3. Fill remaining positions `i + 1 ... half_len - 1` with the smallest remaining characters in ascending order.
4. Construct the full palindrome from this candidate half.
5. Verify if the full palindrome is strictly greater than `target`. (If `c > target[i]`, it is guaranteed to be greater. If `i == half_len`, we check if the reversed second half makes the full palindrome strictly greater than `target`).

---

Approach:

1. Validate Palindrome Feasibility:
   * Count character frequencies of `s`.
   * Count how many characters have odd counts. If `oddCount > 1`, return `""`.
   * Form the available `halfCounts` array: `halfCounts[c] = totalCounts[c] / 2`.
   * If `N` is odd, record `midChar` as the character with odd frequency.

2. Iterate Prefix Match Length `i` from `half_len` Down to `0`:
   * For index `i`:
     - Test placing candidate characters `c` at `first_half[i]`:
       * If `i == half_len`: Try `c = target[i - 1]` (to match target's half exactly and rely on second half to exceed target).
       * If `i < half_len`: Try `c` from `target[i] + 1` to `'z'`.
     - For a valid character `c`, greedily fill positions `i + 1` to `half_len - 1` with smallest available characters.
     - Build the complete palindrome string and check if `palindrome > target`.
     - The first valid candidate found with the largest prefix `i` and smallest `c` will be our answer.

3. Return result string or `""`.

---

⏱ Time Complexity:
O(N^2 + N * 26)

* `N` is up to 300, `half_len <= 150`.
* We check prefixes of length up to `N/2`.
* For each prefix, filling the remaining characters and expanding the palindrome takes O(N) time.
* Total Runtime: O(N^2) worst case, executing in under 2 milliseconds.

Space Complexity:
O(N + 26) Auxiliary Space

* Space for frequency arrays of size 26 and temporary half/full string buffers.
*/

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
private:
    string buildPalindrome(const string& first_half, int n, char midChar) {
        string res = first_half;
        int m = first_half.length();
        
        // If length is odd, the last char of first_half is the middle character
        int right_start = (n % 2 == 1) ? m - 2 : m - 1;
        for (int i = right_start; i >= 0; --i) {
            res += first_half[i];
        }
        return res;
    }

public:
    string lexPalindromicPermutation(string s, string target) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = s.length();
        vector<int> count(26, 0);
        for (char ch : s) {
            count[ch - 'a']++;
        }

        int odd_count = 0;
        char midChar = 0;
        for (int c = 0; c < 26; ++c) {
            if (count[c] % 2 != 0) {
                odd_count++;
                midChar = 'a' + c;
            }
        }

        // A valid palindrome can have at most one character with odd frequency
        if (odd_count > 1) {
            return "";
        }

        vector<int> halfCount(26, 0);
        for (int c = 0; c < 26; ++c) {
            halfCount[c] = count[c] / 2;
        }

        int half_len = (n + 1) / 2;

        // We try matching prefix of length i from half_len down to 0
        for (int i = half_len; i >= 0; --i) {
            // Count characters used in target[0...i-1]
            vector<int> used(26, 0);
            bool possible = true;
            for (int j = 0; j < i; ++j) {
                int c = target[j] - 'a';
                used[c]++;
                // If it's the middle char of an odd palindrome at index half_len - 1
                if (n % 2 == 1 && j == half_len - 1) {
                    if (target[j] != midChar) {
                        possible = false;
                        break;
                    }
                } else {
                    if (used[c] > halfCount[c]) {
                        possible = false;
                        break;
                    }
                }
            }

            if (!possible) continue;

            // Remaining available half counts
            vector<int> remHalf = halfCount;
            for (int c = 0; c < 26; ++c) {
                remHalf[c] -= used[c];
            }

            // Determine starting character candidate at index i
            int start_char = 0;
            if (i < half_len) {
                start_char = (target[i] - 'a') + 1;
            } else { // i == half_len, test exact match if valid
                start_char = (i > 0) ? (target[i - 1] - 'a') : 0; 
            }

            // Try candidate characters at position i
            for (int c = (i == half_len ? start_char : start_char); c < (i == half_len ? start_char + 1 : 26); ++c) {
                if (i == half_len) {
                    // Exact match prefix up to half_len
                    string first_half = target.substr(0, half_len);
                    string pal = buildPalindrome(first_half, n, midChar);
                    if (pal > target) {
                        return pal;
                    }
                } else {
                    // Check if char c can be placed at index i
                    bool valid_choice = false;
                    if (n % 2 == 1 && i == half_len - 1) {
                        if (c == midChar - 'a') valid_choice = true;
                    } else {
                        if (remHalf[c] > 0) valid_choice = true;
                    }

                    if (!valid_choice) continue;

                    // Place candidate c at index i
                    string first_half = target.substr(0, i);
                    first_half += (char)('a' + c);

                    vector<int> curRem = remHalf;
                    if (!(n % 2 == 1 && i == half_len - 1)) {
                        curRem[c]--;
                    }

                    // Fill remaining half positions (i + 1 to half_len - 1) greedily
                    for (int pos = i + 1; pos < half_len; ++pos) {
                        if (n % 2 == 1 && pos == half_len - 1) {
                            first_half += midChar;
                        } else {
                            for (int r = 0; r < 26; ++r) {
                                if (curRem[r] > 0) {
                                    first_half += (char)('a' + r);
                                    curRem[r]--;
                                    break;
                                }
                            }
                        }
                    }

                    string pal = buildPalindrome(first_half, n, midChar);
                    if (pal > target) {
                        return pal;
                    }
                }
            }
        }

        return "";
    }
};