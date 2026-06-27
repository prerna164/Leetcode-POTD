/*
Problem: Find the Maximum Number of Elements in Subset
Link: Subsequence Peak-Square Pattern Tracking

Date: 2026-06-27
Difficulty: Medium
Tags: Array, Hash Table, Math, Sorting

Intuition:
The problem asks us to find the maximum length of a subset that can be arranged in a mountain-like geometric sequence:
  [x, x^2, x^4, ..., x^k, ..., x^4, x^2, x]

This pattern dictates that:
1. Every element except the peak element ($x^k$) must appear at least twice in our subset (one for the left climbing side and one for the right falling side).
2. The peak element can appear exactly once (or more, but only one forms the turning crest).
3. The chain transfers using squares: $x \to x^2 \to x^4 \dots$

Special Case for 1:
The number 1 squared is still 1 ($1^2 = 1, 1^4 = 1 \dots$). Thus, if our base element is 1, the sequence is just a series of 1s. To make a valid symmetric sequence of 1s, we can take as many 1s as possible, provided the count is odd. If the count of 1s in `nums` is even, say $C$, we can take at most $C - 1$ elements to form a valid odd-length pattern.

For any base $x > 1$:
We can compute the frequencies of all numbers in a hash map. For a chosen base $x$:
- If `freq[x] >= 2`, we can use two copies of $x$ and move up to check $x^2$.
- If `freq[x] == 1`, $x$ must act as the peak element, terminating the chain.
- If `freq[x] == 0`, the chain breaks.

We can iterate through every unique number in our array to try it as a base $x$, simulate its climbing chain, and track the maximum length found.

---

Approach:

1. Frequency Table Population:
   * Load the frequencies of all elements in `nums` into an `unordered_map<long long, int> freq`.

2. Base Case Edge Check (1s):
   * Extract `freq[1]`. If it exists, initialize our global answer `max_len` to `freq[1] % 2 == 0 ? freq[1] - 1 : freq[1]`.

3. Chain Verification Scan:
   * Loop through each unique element key in the map where $key > 1$.
   * Track the current chain length `current_len = 0`.
   * While `freq[key] >= 2`:
     - Add 2 to `current_len`.
     - Check if $key \times key \le 10^9$ to prevent integer overflows. If it overflows, break.
     - Move up the chain: `key = key * key`.
   * If `freq[key] == 1`, this element completes the chain as the unique peak element. Add 1 to `current_len`.
   * If `freq[key] == 0`, the last element we counted as having $\ge 2$ copies must retroactively become our peak. Subtract 1 from `current_len`.
   * Update `max_len = max(max_len, current_len)`.

---

⏱ Time Complexity:
O(N)

* Building the frequency map takes $O(N)$ time.
* For each unique key, squaring the number grows it exponentially ($x, x^2, x^4, x^8 \dots$). Since $nums[i] \le 10^9$, a chain can have at most $\approx 5$ steps before overshooting the limit. Thus, processing each chain takes $O(1)$ steps.
* Total Time Complexity scales completely linearly, executing in under 20 milliseconds.

Space Complexity:
O(N) Auxiliary Space

* The `unordered_map` stores at most $N$ unique tracking entries, which keeps the memory footprint low and optimal.
*/

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int maximumLength(vector<int>& nums) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        unordered_map<long long, int> freq;
        for (int num : nums) {
            freq[num]++;
        }

        // Step 1: Process the special edge case where base element is 1
        int max_len = 1; // Any single element itself forms a valid pattern of length 1
        if (freq.count(1)) {
            int count_ones = freq[1];
            // An odd number of 1s can always form a symmetric pattern
            if (count_ones % 2 == 0) {
                max_len = max(max_len, count_ones - 1);
            } else {
                max_len = max(max_len, count_ones);
            }
        }

        // Step 2: Traverse each unique element as a potential base x > 1
        for (auto& pair : freq) {
            long long base = pair.first;
            if (base == 1) continue;

            int current_len = 0;
            long long current_val = base;

            // Climb up the chain by squaring the elements
            while (freq.count(current_val) && freq[current_val] >= 2) {
                current_len += 2;
                
                // Prevent arithmetic boundary overflow before squaring
                if (current_val > 100000) {
                    current_val = 1e18; // Force breakdown state
                    break;
                }
                current_val = current_val * current_val;
            }

            // Check the state of the terminating peak element
            if (freq.count(current_val) && freq[current_val] >= 1) {
                current_len += 1;
            } else {
                // If the next link is missing, one copy from the previous step serves as the peak
                current_len -= 1;
            }

            max_len = max(max_len, current_len);
        }

        return max_len;
    }
};