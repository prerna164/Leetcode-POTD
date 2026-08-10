/*
Problem: Smallest Divisible Digit Product II
Link: LeetCode 3348 - Smallest Divisible Digit Product II

Difficulty: Hard
Tags: String, Greedy, Math, Number Theory, Digit DP

Intuition:
We want to find the smallest zero-free number >= `num` whose digit product is divisible by `t`.

1. Prime Factorization:
   - Non-zero digits (1..9) only contain prime factors 2, 3, 5, and 7.
   - If `t` has any prime factor > 7, no solution exists -> return "-1".

2. Exact Digit Counting:
   - $5$s and $7$s always map to single digits '5' and '7'.
   - For $2$s and $3$s, we can try taking $k$ instances of digit '6' (where $0 \le k \le \min(c_2, c_3)$).
   - Remaining $2$s are packed into '8's (and leftover '4' or '2'), remaining $3$s into '9's (and leftover '3').
   - Minimizing over $k$ gives the exact minimum number of digits required.

3. Suffix Construction:
   - At each position of the suffix, pick the smallest digit $d \in [1, 9]$ such that the remaining prime factor requirements can fit into the remaining length.

---

⏱ Time Complexity:
O(N)

* Factoring `t` takes O(log t) time.
* Testing prefixes of `num` takes O(N) iterations.
* `get_min_digits` runs in O(min(c2, c3)) = O(log t) = O(1) time.
* Constructing the suffix takes O(N * 9 * O(1)) = O(N) time.
* Overall Runtime: O(N) linear time.

Space Complexity:
O(N) Auxiliary Space

* Space required for the output string of length N or N + 1.
*/

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>

using namespace std;

class Solution {
private:
    struct PrimeCount {
        int c2 = 0, c3 = 0, c5 = 0, c7 = 0;

        void add_digit(int d) {
            if (d == 2) c2++;
            else if (d == 3) c3++;
            else if (d == 4) c2 += 2;
            else if (d == 5) c5++;
            else if (d == 6) { c2++; c3++; }
            else if (d == 7) c7++;
            else if (d == 8) c2 += 3;
            else if (d == 9) c3 += 2;
        }
    };

    // Computes the EXACT minimum number of digits needed to fulfill the required prime factors
    int get_min_digits(int c2, int c3, int c5, int c7) {
        c2 = max(0, c2);
        c3 = max(0, c3);
        c5 = max(0, c5);
        c7 = max(0, c7);

        int min_d = INT_MAX;
        int max_sixes = min(c2, c3);

        for (int k = 0; k <= max_sixes; ++k) {
            int rem2 = c2 - k;
            int rem3 = c3 - k;
            int digits2 = (rem2 + 2) / 3;
            int digits3 = (rem3 + 1) / 2;
            min_d = min(min_d, k + digits2 + digits3);
        }

        return c5 + c7 + min_d;
    }

    // Constructs the lexicographically smallest string of length `len` matching requirements
    string build_suffix(int c2, int c3, int c5, int c7, int len) {
        string suffix = "";
        for (int pos = 0; pos < len; ++pos) {
            int rem_len = len - 1 - pos;
            for (int d = 1; d <= 9; ++d) {
                PrimeCount temp;
                temp.add_digit(d);
                if (get_min_digits(c2 - temp.c2, c3 - temp.c3, c5 - temp.c5, c7 - temp.c7) <= rem_len) {
                    suffix += (char)('0' + d);
                    c2 -= temp.c2;
                    c3 -= temp.c3;
                    c5 -= temp.c5;
                    c7 -= temp.c7;
                    break;
                }
            }
        }
        return suffix;
    }

public:
    string smallestNumber(string num, long long t) {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        // Step 1: Factorize t into prime factors 2, 3, 5, 7
        PrimeCount req;
        long long temp_t = t;
        while (temp_t % 2 == 0) { req.c2++; temp_t /= 2; }
        while (temp_t % 3 == 0) { req.c3++; temp_t /= 3; }
        while (temp_t % 5 == 0) { req.c5++; temp_t /= 5; }
        while (temp_t % 7 == 0) { req.c7++; temp_t /= 7; }

        if (temp_t > 1) return "-1"; // Invalid prime factor (> 7)

        int n = num.length();

        // Check for '0' in num
        int first_zero = -1;
        for (int i = 0; i < n; ++i) {
            if (num[i] == '0') {
                first_zero = i;
                break;
            }
        }

        // Compute prime factors present in num
        PrimeCount cur;
        int limit = (first_zero == -1) ? n : first_zero;
        for (int i = 0; i < limit; ++i) {
            cur.add_digit(num[i] - '0');
        }

        // If num is zero-free and already divisible by t
        if (first_zero == -1 && get_min_digits(req.c2 - cur.c2, req.c3 - cur.c3, req.c5 - cur.c5, req.c7 - cur.c7) == 0) {
            return num;
        }

        // Step 2: Try changing num from right to left
        for (int i = n - 1; i >= 0; --i) {
            if (i < limit) {
                // backtrack the digit at position i
                int d_val = num[i] - '0';
                if (d_val == 2) cur.c2--;
                else if (d_val == 3) cur.c3--;
                else if (d_val == 4) cur.c2 -= 2;
                else if (d_val == 5) cur.c5--;
                else if (d_val == 6) { cur.c2--; cur.c3--; }
                else if (d_val == 7) cur.c7--;
                else if (d_val == 8) cur.c2 -= 3;
                else if (d_val == 9) cur.c3 -= 2;
            }

            if (first_zero != -1 && i > first_zero) continue;

            int start_digit = (i < first_zero || first_zero == -1) ? (num[i] - '0' + 1) : 1;

            for (int d = start_digit; d <= 9; ++d) {
                PrimeCount temp_cur = cur;
                temp_cur.add_digit(d);

                int rem_len = n - 1 - i;
                int need_digits = get_min_digits(req.c2 - temp_cur.c2, req.c3 - temp_cur.c3, 
                                                 req.c5 - temp_cur.c5, req.c7 - temp_cur.c7);

                if (need_digits <= rem_len) {
                    string prefix = num.substr(0, i) + (char)('0' + d);
                    string suffix = build_suffix(req.c2 - temp_cur.c2, req.c3 - temp_cur.c3, 
                                                 req.c5 - temp_cur.c5, req.c7 - temp_cur.c7, rem_len);
                    return prefix + suffix;
                }
            }
        }

        // Step 3: Expand length if no same-length solution exists
        int min_len = max(n + 1, get_min_digits(req.c2, req.c3, req.c5, req.c7));
        return build_suffix(req.c2, req.c3, req.c5, req.c7, min_len);
    }
};