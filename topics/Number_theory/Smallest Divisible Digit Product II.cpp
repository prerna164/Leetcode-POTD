/*
Problem: Smallest Divisible Digit Product II
Link: LeetCode 3348 - Smallest Divisible Digit Product II

Difficulty: Hard
Tags: String, Greedy, Math, Number Theory, Digit DP

Intuition:
We need to find the smallest zero-free number (contains no '0' digits) that is >= `num` and whose digit product is divisible by `t`.

Key Observations:
1. Prime Factorization of `t`:
   - Non-zero digits (1 to 9) can only contribute prime factors 2, 3, 5, and 7.
   - If `t` has any prime factor other than 2, 3, 5, or 7, no digit product can ever be divisible by `t`, so we immediately return `"-1"`.
   - Otherwise, we factorize `t` into count of primes: {c2, c3, c5, c7}.

2. Greedy Matching Strategy:
   - To make a suffix as small as possible while meeting required prime factors, we greedily combine prime factors into single digits:
     * 7s become '7'
     * 5s become '5'
     * Pairs of 3s become '9' (and remaining 3 becomes '3')
     * Triplets of 2s become '8', pairs become '4', etc.
     * Combinations like 2 * 3 = 6 are also considered to minimize total required digits.
   - We check if `num` itself is valid. If not, we find the longest prefix of `num` that we can keep such that the remaining length can be filled with digits satisfying the missing prime factors.
   - If no prefix of `num` of length `N` works, we construct a number of length `N + 1` or the minimum required length.

---

Approach:

1. Factorize `t`:
   * Count required powers of 2, 3, 5, 7. If `t` has other prime factors, return `"-1"`.

2. Helper Functions:
   * `get_min_digits(c2, c3, c5, c7)`: Calculates the minimum number of digits needed to supply the required prime factor counts.
   * `build_suffix(c2, c3, c5, c7, target_len)`: Constructs the lexicographically smallest string of length `target_len` that satisfies the required prime factor counts (padding with '1's as needed).

3. Try matching `num` prefix:
   * Iterate backwards from position `i = N - 1` to `0`.
   * Try incrementing `num[i]` to digit `d` (from `num[i] + 1` up to '9').
   * Check if the required remaining prime factor counts (after prefix `num[0...i-1]` and `d`) can fit within the available `N - 1 - i` suffix length.
   * On the first valid candidate, construct the answer: `num[0...i-1] + d + build_suffix(...)` and return.

4. Handle length expansion:
   * If no valid suffix fits in length `N`, construct the smallest number of length `max(N + 1, min_digits_needed)` using `build_suffix(...)`.

---

⏱ Time Complexity:
O(N)

* Factoring `t` takes O(log t) time.
* Checking prefixes of `num` takes O(N) iterations. In each iteration, digit factor updates and suffix availability checks take O(1) time.
* Overall Runtime: O(N) linear time, where N = num.length <= 2 * 10^5.

Space Complexity:
O(N) Auxiliary Space

* Required to store the result string of length N or N + 1.
*/

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

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

        void remove_digit(int d) {
            if (d == 2) c2--;
            else if (d == 3) c3--;
            else if (d == 4) c2 -= 2;
            else if (d == 5) c5--;
            else if (d == 6) { c2--; c3--; }
            else if (d == 7) c7--;
            else if (d == 8) c2 -= 3;
            else if (d == 9) c3 -= 2;
        }
    };

    // Computes minimum digits needed to satisfy remaining prime factors
    int get_min_digits(int c2, int c3, int c5, int c7) {
        c2 = max(0, c2);
        c3 = max(0, c3);
        c5 = max(0, c5);
        c7 = max(0, c7);
        return (c2 + 2) / 3 + (c3 + 1) / 2 + c5 + c7;
    }

    // Constructs the lexicographically smallest string of length 'len' matching requirements
    string build_suffix(int c2, int c3, int c5, int c7, int len) {
        c2 = max(0, c2);
        c3 = max(0, c3);
        c5 = max(0, c5);
        c7 = max(0, c7);

        string digits = "";
        while (c7 > 0) { digits += '7'; c7--; }
        while (c5 > 0) { digits += '5'; c5--; }
        while (c3 >= 2) { digits += '9'; c3 -= 2; }
        while (c2 >= 3) { digits += '8'; c2 -= 3; }
        if (c3 == 1 && c2 == 1) { digits += '6'; c3--; c2--; }
        if (c3 == 1) { digits += '3'; c3--; }
        if (c2 == 2) { digits += '4'; c2 -= 2; }
        if (c2 == 1) { digits += '2'; c2--; }

        sort(digits.begin(), digits.end());
        int ones = len - (int)digits.length();
        return string(max(0, ones), '1') + digits;
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

        // Check if num itself contains '0'
        int first_zero = -1;
        for (int i = 0; i < n; ++i) {
            if (num[i] == '0') {
                first_zero = i;
                break;
            }
        }

        // Track factors present in num
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
                cur.remove_digit(num[i] - '0');
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