/*
Problem: Process String with  Special Operations II
Link: Scalable String Operations Tracking

Date: 2026-06-17
Difficulty: Hard
Tags: String, Simulation, Vector Optimization, Math

Intuition:
With constraints where `k` and the final string length can reach up to 10^15, explicit generation or simulation of the string is completely impossible due to time and memory limits. Instead, we must track the length of the string at every step and then reconstruct the source character by tracing index `k` backwards from the final step to the beginning.

Let `lengths[i]` represent the length of the string after processing the prefix of `s` up to index `i-1`. We can easily compute all lengths in a forward pass:
1. Alphabet character: `lengths[i] = lengths[i-1] + 1`
2. '*': `lengths[i] = max(0, lengths[i-1] - 1)`
3. '#': `lengths[i] = lengths[i-1] * 2`
4. '%': `lengths[i] = lengths[i-1]`

After the forward pass, if `k` is out of bounds (`k >= lengths[n]`), we immediately return '.'. 

Otherwise, we work backward from the last character operation down to the first. For each operation at step `i` (associated with character `s[i-1]`), we map the index `k` to what it was at step `i-1`:
- If `s[i-1]` is a lowercase letter: If `k` points to the last character (`lengths[i] - 1`), then this is the character that was just appended. We can return `s[i-1]` directly! Otherwise, it remains unchanged.
- If `s[i-1] == '*'`: The character at index `k` is unaffected by a backspace at the end, so `k` remains unchanged.
- If `s[i-1] == '#'`: The string was duplicated. If `k` is in the second half (`k >= lengths[i-1]`), it wraps back to the first half: `k -= lengths[i-1]`.
- If `s[i-1] == '%'`: The string was reversed. The new index maps back to: `k = lengths[i-1] - 1 - k`.

---

Approach:

1. Forward DP Pass (Length Calculation):
   * Create a `lengths` array of size `n + 1` where `lengths[0] = 0`.
   * Loop through `s` and calculate the length at each step according to the rules.

2. Bounds Validation:
   * Check if `k >= lengths[n]` or `k < 0`. If true, return '.'.

3. Backward Reverse Tracking:
   * Loop from `i = n` down to 1.
   * Check the current operation symbol `s[i-1]` and modify `k` to its corresponding previous state position using the reverse formulas.
   * If an appended character is matched, return it immediately.

---

⏱ Time Complexity:
O(N)

* The forward pass to compute lengths takes O(N) time.
* The backward tracking pass takes at most O(N) steps.
* Total Time Complexity is linear O(N), which runs flawlessly well under 5 milliseconds for N = 10^5.

Space Complexity:
O(N)

* We store the length values at each step in a `lengths` vector of size N + 1, taking O(N) space.
*/

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    char processStr(string s, long long k) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = s.length();
        // lengths[i] stores the length of the string after processing s[0...i-1]
        vector<long long> lengths(n + 1, 0);

        // Step 1: Forward pass to compute lengths at each step
        for (int i = 1; i <= n; ++i) {
            char c = s[i - 1];
            if (c >= 'a' && c <= 'z') {
                lengths[i] = lengths[i - 1] + 1;
            } else if (c == '*') {
                lengths[i] = max(0LL, lengths[i - 1] - 1);
            } else if (c == '#') {
                lengths[i] = lengths[i - 1] * 2;
            } else if (c == '%') {
                lengths[i] = lengths[i - 1];
            }
        }

        // Step 2: Out of bounds check
        if (k < 0 || k >= lengths[n]) {
            return '.';
        }

        // Step 3: Backward pass to track the index k to its origin source character
        for (int i = n; i >= 1; --i) {
            char c = s[i - 1];

            if (c >= 'a' && c <= 'z') {
                // If k is the newly appended character, we found our answer
                if (k == lengths[i] - 1) {
                    return c;
                }
                // Otherwise, k stays the same relative to lengths[i-1]
            } else if (c == '*') {
                // Deleting the last character doesn't shift indices before it
                // k stays the same
            } else if (c == '#') {
                // If k falls into the duplicated second half, map it back to the first half
                if (k >= lengths[i - 1]) {
                    k -= lengths[i - 1];
                }
            } else if (c == '%') {
                // If reversed, invert the index location relative to the previous length boundary
                k = lengths[i - 1] - 1 - k;
            }
        }

        return '.';
    }
};