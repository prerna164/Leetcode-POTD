/*
Problem: Maximum Number of Non-overlapping Palindrome Substrings
Link: LeetCode 2472 - Maximum Number of Non-overlapping Palindrome Substrings

Difficulty: Hard
Tags: String, Dynamic Programming, Greedy, Two Pointers

Intuition:
We want to select the maximum number of non-overlapping palindromic substrings, each having length >= k.

Key Optimization Insight:
Any palindrome of length strictly greater than k + 1 contains a smaller palindrome inside it of length k or k + 1!
- If a palindrome has odd length >= k, its center sub-palindrome of length k (or k+1) is also a palindrome.
- If a palindrome has even length >= k, its center sub-palindrome of length k (or k+1) is also a palindrome.

Therefore, we ONLY ever need to look for palindromes of exact length `k` and length `k + 1`.
Finding smaller palindromes first is always greedy-optimal because a shorter palindrome finishes earlier (smaller right index), leaving more space for future non-overlapping palindromes.

We can use Dynamic Programming or a Greedy Expand-Around-Center approach:
`dp[i]` = Maximum non-overlapping palindromes in `s[0...i-1]`.
For each index `i` from `1` to `N`:
1. `dp[i] = dp[i - 1]` (option to skip `s[i - 1]`).
2. Check if there is a palindrome of length `k` ending at `i - 1`. If yes, `dp[i] = max(dp[i], dp[i - k] + 1)`.
3. Check if there is a palindrome of length `k + 1` ending at `i - 1`. If yes, `dp[i] = max(dp[i], dp[i - (k + 1)] + 1)`.

---

Approach:

1. Dynamic Programming State:
   * `dp[i]` represents max valid palindromes using prefix `s[0...i-1]`.

2. Helper Function `isPalindrome(s, l, r)`:
   * Checks if substring `s[l...r]` is a palindrome in $O(len)$ time.

3. Transitions for `i` from `k` to `N`:
   * Set `dp[i] = dp[i - 1]`.
   * Test substring of length `k` ending at `i - 1`: `s[i - k ... i - 1]`.
     If valid palindrome, `dp[i] = max(dp[i], dp[i - k] + 1)`.
   * Test substring of length `k + 1` ending at `i - 1`: `s[i - k - 1 ... i - 1]` (if `i >= k + 1`).
     If valid palindrome, `dp[i] = max(dp[i], dp[i - k - 1] + 1)`.

4. Return `dp[N]`.

---

⏱ Time Complexity:
O(N * K)

* `N = s.length()`.
* At each index `i`, we check at most two substrings of lengths `k` and `k + 1` for palindromicity.
* Each check takes $O(k)$ time.
* Total Runtime: $O(N \cdot K)$ time, well within execution limits for $N \le 2000$.

Space Complexity:
O(N) Auxiliary Space

* `dp` array of size `N + 1`.
*/

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
private:
    bool isPalindrome(const string& s, int left, int right) {
        while (left < right) {
            if (s[left] != s[right]) return false;
            left++;
            right--;
        }
        return true;
    }

public:
    int maxPalindromes(string s, int k) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = s.length();
        if (k > n) return 0;

        // dp[i] = max non-overlapping palindromes in s[0...i-1]
        vector<int> dp(n + 1, 0);

        for (int i = 1; i <= n; ++i) {
            // Option 1: Do not include s[i-1] in any new palindrome
            dp[i] = dp[i - 1];

            // Option 2: Check for a palindrome of length k ending at index i - 1
            if (i >= k && isPalindrome(s, i - k, i - 1)) {
                dp[i] = max(dp[i], dp[i - k] + 1);
            }

            // Option 3: Check for a palindrome of length k + 1 ending at index i - 1
            if (i >= k + 1 && isPalindrome(s, i - k - 1, i - 1)) {
                dp[i] = max(dp[i], dp[i - k - 1] + 1);
            }
        }

        return dp[n];
    }
};