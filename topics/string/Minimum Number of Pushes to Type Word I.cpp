/*
Problem: Minimum Number of Pushes to Type Word I
Link: LeetCode 3014 - Minimum Number of Pushes to Type Word I

Date: 2026-07-30
Difficulty: Easy
Tags: Math, String, Greedy

Intuition:
We are given a string `word` containing distinct lowercase English letters.
We want to assign letters to the 8 telephone keypad keys (numbered 2 through 9) to minimize the total key pushes required to type `word`.

Key Observations:
1. Available Key Slots:
   - There are 8 keys available: {2, 3, 4, 5, 6, 7, 8, 9}.
   - The first letter assigned to a key requires 1 push.
   - The second letter assigned to a key requires 2 pushes.
   - The third letter requires 3 pushes, and the fourth requires 4 pushes.

2. Greedy Allocation for Distinct Letters:
   - Since all letters in `word` are distinct, each letter appears exactly once.
   - To minimize total pushes, we should fill the 1st position (1 push) on all 8 keys first.
   - If there are more than 8 letters, we fill the 2nd position (2 pushes) on all 8 keys next.
   - If there are more than 16 letters, we fill the 3rd position (3 pushes) on all 8 keys next.
   - If there are more than 24 letters, the remaining letters go to the 4th position (4 pushes).

3. Mathematical Formulation:
   - For `N` letters (where N = word.length):
     * The first 8 letters take 1 push each: `min(N, 8) * 1`
     * The next 8 letters (9 to 16) take 2 pushes each: `min(max(0, N - 8), 8) * 2`
     * The next 8 letters (17 to 24) take 3 pushes each: `min(max(0, N - 16), 8) * 3`
     * The remaining letters (25 to 26) take 4 pushes each: `max(0, N - 24) * 4`

---

Approach:

1. Calculate length `N = word.length()`.
2. Compute the total pushes required using integer division:
   - `pushes = 0`
   - For each index `i` from `0` to `N - 1`:
     - The push cost for the `i`-th letter is `(i / 8) + 1`.
     - Accumulate `pushes += (i / 8) + 1`.
3. Return `pushes`.

---

⏱ Time Complexity:
O(1)

* The string length `N` is bounded by 26 (`1 <= word.length <= 26`).
* The loop runs at most 26 times, executing constant time arithmetic operations.

Space Complexity:
O(1) Auxiliary Space

* Uses a constant amount of memory for local variables.
*/

#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
    int minimumPushes(string word) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = word.length();
        int pushes = 0;

        for (int i = 0; i < n; ++i) {
            pushes += (i / 8) + 1;
        }

        return pushes;
    }
};