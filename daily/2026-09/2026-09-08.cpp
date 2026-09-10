/*
Problem: Count Commas in Range
Link: https://leetcode.com/problems/count-commas-in-range/description/?envType=daily-question&envId=2026-09-08
Difficulty: Easy
Tags: Math, Number Theory

Intuition:
In standard number formatting, commas are placed every 3 digits from right to left:
- Numbers from 1 to 999 (1 to 3 digits) have 0 commas.
- Numbers from 1,000 to 999,999 (4 to 6 digits) have 1 comma each.
- Numbers from 1,000,000 to 999,999,999 (7 to 9 digits) have 2 commas each.

Given the constraint `1 <= n <= 10^5`:
- Every number `x <= 999` contributes 0 commas.
- Every number `x >= 1000` up to `n` contributes exactly 1 comma.

Therefore, for $n \le 10^5$, the total number of commas used across all numbers from 1 to `n` is simply the number of integers in the range `[1000, n]`.
- If `n < 1000`, the answer is `0`.
- If `n >= 1000`, the answer is `n - 999` (or `n - 1000 + 1`).

---

Approach:

1. Check Range:
   * If `n < 1000`, return `0`.
   * Otherwise, return `n - 999`.

---

⏱ Time Complexity:
O(1)

* Constant $O(1)$ arithmetic check.

Space Complexity:
O(1) Auxiliary Space

* Uses no extra memory.
*/

#include <iostream>

using namespace std;

class Solution {
public:
    int countCommas(int n) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        if (n < 1000) {
            return 0;
        }
        
        return n - 999;
    }
};