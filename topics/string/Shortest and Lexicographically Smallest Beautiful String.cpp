/*
Problem: Shortest and Lexicographically Smallest Beautiful String
Link: LeetCode 2904 - Shortest and Lexicographically Smallest Beautiful String

Difficulty: Easy
Tags: String, Sliding Window, Two Pointers

Intuition:
A substring is defined as "beautiful" if it contains exactly `k` ones ('1').
We want to find the shortest beautiful substring. If there are multiple beautiful substrings of the same shortest length, we pick the lexicographically smallest one.

Key Observations:
1. Trimming Leading/Trailing Zeros:
   - Any shortest beautiful substring must start with a '1' and end with a '1'. If it starts or ends with '0', removing that '0' creates a shorter substring with the exact same count of `k` ones.
2. Store Indices of '1's:
   - Collect all indices where `s[i] == '1'`.
   - If total count of '1's is less than `k`, no beautiful substring exists, so return `""`.
   - For every window of `k` consecutive '1's starting at index `ones[i]` and ending at `ones[i + k - 1]`:
     - The corresponding minimal substring is `s.substr(ones[i], ones[i + k - 1] - ones[i] + 1)`.
     - Calculate its length: `len = ones[i + k - 1] - ones[i] + 1`.
3. Select Optimal Substring:
   - Track the minimum length found so far (`minLen`).
   - If a new valid substring has `length < minLen`, update `minLen` and replace the result substring.
   - If `length == minLen`, replace the result substring if the new substring is lexicographically smaller (`new_sub < ans`).

---

Approach:

1. Collect Indices:
   * Store 0-based indices of all '1's in a vector `ones`.
   * If `ones.size() < k`, return `""`.

2. Sliding Window Over Indices:
   * Loop `i` from `0` to `ones.size() - k`:
     - Calculate substring start = `ones[i]` and end = `ones[i + k - 1]`.
     - Extract `cand = s.substr(ones[i], ones[i + k - 1] - ones[i] + 1)`.
     - Update optimal candidate using string length and lexicographical comparison.

3. Return Best Result:
   * Return the best candidate string `ans`.

---

⏱ Time Complexity:
O(N^2) worst case (or O(N) since N <= 100)

* Collecting '1' indices takes O(N) time.
* There are at most N windows of size `k`.
* Substring extraction and string comparison take O(N) time per window.
* Given $N \le 100$, total operations are $\approx 100^2 = 10,000$, running instantaneously.

Space Complexity:
O(N) Auxiliary Space

* Vector `ones` stores at most N indices, and string variables store substrings of length $\le N$.
*/

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        vector<int> ones;
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == '1') {
                ones.push_back(i);
            }
        }

        // If total 1's in s is less than k, no valid beautiful substring exists
        if (ones.size() < k) {
            return "";
        }

        string ans = "";
        int minLen = s.length() + 1;

        // Examine each window containing exactly k '1's
        for (int i = 0; i + k - 1 < ones.size(); ++i) {
            int start = ones[i];
            int end = ones[i + k - 1];
            int len = end - start + 1;

            string cand = s.substr(start, len);

            if (len < minLen) {
                minLen = len;
                ans = cand;
            } else if (len == minLen) {
                if (cand < ans) {
                    ans = cand;
                }
            }
        }

        return ans;
    }
};