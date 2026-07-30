/*
Problem: Smallest Palindromic Rearrangement II (k-th Lexicographically Smallest Palindromic Permutation)
Link: LeetCode 3518 - Smallest Palindromic Rearrangement II

Date: 2026-07-29
Difficulty: Hard
Tags: Hash Table, Math, String, Combinatorics, Counting, Greedy

Intuition:
We are given a palindromic string `s` and a positive integer `k`.
Our goal is to find the k-th lexicographically smallest palindromic permutation of `s`.
If fewer than `k` distinct palindromic permutations exist, we must return `""`.

Key Observations:
1. Palindrome Symmetry:
   - A palindrome of length N is completely determined by its first half of size `len = N / 2`.
   - If N is odd, the middle character is fixed and placed in the center (`s[len]`).
   - Thus, the problem reduces to generating the k-th lexicographically smallest permutation of the left half.

2. Combinatorial Digit-by-Digit Placement (Greedy Selection):
   - Rather than generating all permutations (which is computationally impossible for large strings), we can place characters from position `0` to `len - 1` one by one.
   - At each position, we try candidate characters in alphabetical order ('a' to 'z').
   - For candidate `c`, we tentatively place it and count how many valid arrangements can be formed by the remaining characters.
   - If the count of arrangements is `>= k`, then the k-th permutation starts with this prefix, so we keep `c` and move to the next position.
   - If the count is `< k`, we skip all those arrangements by subtracting the count from `k` (`k -= count`) and try the next candidate character.

3. Counting Multiset Permutations with Saturation:
   - The number of distinct permutations of a multiset with remaining length `L` and character counts `cnt[0..25]` is given by:
     $$ \frac{L!}{\prod (cnt[i]!)} = \binom{L}{cnt[0]} \times \binom{L - cnt[0]}{cnt[1]} \times \dots $$
   - Since $k \le 10^6$, any intermediate permutation count larger than $10^6 + 1$ can be capped/saturated to $10^6 + 1$ to prevent integer overflow.

---

Approach:

1. Extract Half-Frequencies & Middle Character:
   - Count the frequencies of each character in `s`.
   - Calculate `half[i] = freq[i] / 2` for each character `i` from 0 to 25.
   - Total length of the left half: `halfLen = N / 2`.
   - Middle character `mid`: if `N` is odd, `mid` is the character with odd frequency.

2. Check Possibility:
   - Compute total possible permutations of the left half.
   - If `total < k`, return `""`.

3. Construct Left Half Greedily:
   - For each index `i` from `0` to `halfLen - 1`:
     - Loop candidate `c` from `0` to `25`:
       - If `half[c] > 0`:
         - Temporarily decrement `half[c]--`.
         - Compute `ways = countPermutations(half, halfLen - 1 - i)`.
         - If `ways >= k`: character `c` is selected; `break`.
         - Else: `k -= ways`, increment `half[c]++` back, and try next character.

4. Assemble Output:
   - Result string = `left` + (`mid` if odd) + `reverse(left)`.

---

⏱ Time Complexity:
O(N + 26 * 26 * N) = O(N)

* Calculating total permutations of a 26-element array takes O(26) arithmetic operations.
* Constructing the left half takes `(N / 2)` steps. At each step, we iterate over 26 possible character choices and evaluate `countPermutations`, taking O(26) steps.
* Total operations per string position: O(26 * 26) = constant O(1).
* Overall runtime is strictly linear O(N).

Space Complexity:
O(N) Auxiliary Space

* Space required to store the constructed string of length N.
* Fixed-size frequency arrays of size 26 use O(1) space.
*/

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
private:
    static const long long LIMIT = 1000001; // Max k is 10^6, cap saturation limit

    // Helper function to calculate combinations nCr with saturation limit
    long long nCr(int n, int r) {
        if (r < 0 || r > n) return 0;
        if (r == 0 || r == n) return 1;
        r = min(r, n - r);
        long long res = 1;
        for (int i = 1; i <= r; ++i) {
            res = res * (n - i + 1) / i;
            if (res > LIMIT) return LIMIT;
        }
        return res;
    }

    // Helper function to calculate total distinct permutations of character multiset
    long long countPermutations(const vector<int>& cnt, int total) {
        long long ways = 1;
        int remaining = total;
        for (int i = 0; i < 26; ++i) {
            if (cnt[i] > 0) {
                ways *= nCr(remaining, cnt[i]);
                if (ways > LIMIT) return LIMIT;
                remaining -= cnt[i];
            }
        }
        return ways;
    }

public:
    string smallestPalindrome(string s, int k) {
        // Optimize I/O for competitive programming
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = s.length();
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c - 'a']++;
        }

        vector<int> half(26, 0);
        int halfLen = n / 2;
        char mid = '\0';

        for (int i = 0; i < 26; ++i) {
            half[i] = freq[i] / 2;
            if (freq[i] % 2 != 0) {
                mid = 'a' + i;
            }
        }

        // Total permutations possible for the left half
        long long totalWays = countPermutations(half, halfLen);
        if (totalWays < k) {
            return "";
        }

        string left = "";
        long long currentK = k;

        // Construct the left half of the palindrome character by character
        for (int pos = 0; pos < halfLen; ++pos) {
            for (int ch = 0; ch < 26; ++ch) {
                if (half[ch] == 0) continue;

                // Try placing character 'ch'
                half[ch]--;
                long long ways = countPermutations(half, halfLen - pos - 1);

                if (ways >= currentK) {
                    left += (char)('a' + ch);
                    break; // Picked this character, move to next position
                } else {
                    currentK -= ways;
                    half[ch]++; // Backtrack and try next character
                }
            }
        }

        string right = left;
        reverse(right.begin(), right.end());

        if (mid != '\0') {
            return left + mid + right;
        }
        return left + right;
    }
};