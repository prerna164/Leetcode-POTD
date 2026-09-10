/*
Problem: Count Nodes Equal to Average of Subtree
Link: https://leetcode.com/problems/total-number-of-commas-used/description/?envType=daily-question&envId=2026-09-09
Difficulty: Medium

Tags: Math, Prefix Sums

Intuition:
In standard number formatting, commas are placed every 3 digits from right to left:
- 1 to 999 (1 to 3 digits): 0 commas
- 1,000 to 999,999 (4 to 6 digits): 1 comma
- 1,000,000 to 999,999,999 (7 to 9 digits): 2 commas
- 1,000,000,000 to 999,999,999,999 (10 to 12 digits): 3 commas
- 1,000,000,000,000 to 999,999,999,999,999 (13 to 15 digits): 4 commas

Instead of counting commas per number individually, we can count the number of integers that are at least $10^3$, at least $10^6$, at least $10^9$, at least $10^{12}$, and so on.

Every number $\ge 10^3$ gets at least 1 comma.
Every number $\ge 10^6$ gets an additional (2nd) comma.
Every number $\ge 10^9$ gets an additional (3rd) comma.
Every number $\ge 10^{12}$ gets an additional (4th) comma.
Every number $\ge 10^{15}$ gets an additional (5th) comma.

Thus, total commas = $\sum \max(0LL, n - threshold + 1)$ for thresholds $10^3, 10^6, 10^9, 10^{12}, 10^{15}, \dots$

---

Approach:

1. Initialize `totalCommas = 0` and `threshold = 1000`.
2. While `n >= threshold`:
   * Add `n - threshold + 1` to `totalCommas`.
   * Multiply `threshold` by `1000` to move to the next comma tier.
3. Return `totalCommas`.

---

⏱ Time Complexity:
O(log_1000 N)

* The loop runs at most 5-6 times since $N \le 10^{15}$.
* Total Runtime: $O(1)$ logarithmic execution time.

Space Complexity:
O(1) Auxiliary Space

* Uses constant extra memory.
*/

#include <iostream>

using namespace std;

class Solution {
public:
    long long countCommas(long long n) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        long long totalCommas = 0;
        long long threshold = 1000LL;

        while (n >= threshold) {
            totalCommas += (n - threshold + 1);
            
            // Avoid potential 64-bit signed integer overflow when multiplying by 1000
            if (threshold > LLONG_MAX / 1000LL) {
                break;
            }
            threshold *= 1000LL;
        }

        return totalCommas;
    }
};