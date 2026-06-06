/*
Problem: Total Waviness in a Large Range II
Link: Custom Digit Property Range Enumeration (Optimized)

Date: 2026-06-06
Difficulty: Hard
Tags: Dynamic Programming, Digit DP, Math

Intuition:
The problem asks us to find the total 'waviness' (sum of peaks and valleys) of all integers in the given range [num1, num2]. 
With constraints reaching up to 10^15, an exhaustive loop counting waviness for each individual number will cause a Time Limit Exceeded (TLE) error. Instead, we must compute the range using a Digit Dynamic Programming (Digit DP) approach.

The fundamental tenet of Digit DP is that any range calculation can be split using prefix math:
  Total Waviness in [num1, num2] = Solve(num2) - Solve(num1 - 1)

To find the cumulative total of peaks and valleys, we build valid numbers digit-by-digit from left to right. To determine if a digit creates a wave peak or valley at any step, we need a look-ahead/look-behind context. Specifically, for a digit placed at a previous index, we need to know:
1. The position of the digit we are currently choosing (`idx`).
2. The digit chosen immediately before it (`prev`).
3. The digit chosen before that (`prev_prev`).
4. A boolean flag (`tight`) restricting our current digit choices to match the upper boundary sequence limit.
5. A boolean flag (`leading_zero`) ensuring leading zeroes aren't matched as numerical elements, as they shouldn't trigger faulty peak or valley sequences.

A digit is flagged as a peak if it satisfies: `prev > prev_prev` and `prev > current_digit`.
A digit is flagged as a valley if it satisfies: `prev < prev_prev` and `prev < current_digit`.

Because the total waviness shifts based on how many valid suffix variations can branch out from a specific configuration, our memoization table maps states to pairs: the total sum of waviness found from that state onward, and the total count of valid terminal suffix numbers generated.

---

Approach:

1. State Encoding & Structural Design:
   * Build a memoization structure `dp[idx][prev][prev_prev][tight][leading_zero]`.
   * Use an assignment value of `11` as a dummy value representing an unassigned or invalid state (e.g., when fewer than 2 valid digits have been constructed).

2. Recursion Flow & Wave Checking:
   * For a given `idx`, figure out the upper placement boundary `limit` (which is either 9 or `num_str[idx] - '0'` if `tight` is active).
   * Iterate through all digit options from `0` to `limit`.
   * If `leading_zero` is false, and both `prev` and `prev_prev` hold valid non-dummy digit values (not equal to 11), evaluate if the `prev` digit matches a peak or valley scenario against `prev_prev` and the current iteration's `digit`.
   * For every match found, that point contributes `1 * (number of valid numerical suffixes generated downstream)` to the recursive sum.

3. Complete Sum Computation:
   * Convert numbers to string representations to easily parse indices.
   * Return the result of `Solve(num2) - Solve(num1 - 1)` ensuring exact boundary resolution.

---

⏱ Time Complexity:
O(L * 10 * 12 * 12) -> O(L) where L is the maximum number of digits (L <= 16).

* The string length of any input value is bounded at 16 digits.
* The processing matrix is capped at roughly 16 * 12 * 12 * 2 * 2 = 9,216 distinct states.
* Each state transitions across at most 10 choices (digits 0-9).
* The total computation completes in a few thousand operations, taking less than 1 millisecond.

Space Complexity:
O(L) state complexity -> Memory complexity simplifies to O(1) static allocation.

* The memoization array is statically initialized using fixed small bounds (`17 x 12 x 12 x 2 x 2`).
* Recursion stack frames are bounded linearly by the maximum length string length `L`, preserving a nominal memory signature.
*/

#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
private:
    // Storing structures containing both the aggregate waviness contribution
    // and the total count of unique numerical suffix paths completed.
    struct State {
        long long waviness_sum;
        long long count;
    };
    
    string num_str;
    State dp[17][12][12][2][2];
    bool visited[17][12][12][2][2];

    State countWaviness(int idx, int prev, int prev_prev, bool tight, bool leading_zero) {
        // Base Case: A valid number has been completely generated
        if (idx == num_str.length()) {
            return {0, 1}; // Returns 0 initial waviness, 1 base configuration path
        }

        // Return memoized state result if already computed
        if (visited[idx][prev][prev_prev][tight][leading_zero]) {
            return dp[idx][prev][prev_prev][tight][leading_zero];
        }

        int limit = tight ? (num_str[idx] - '0') : 9;
        State res = {0, 0};

        for (int digit = 0; digit <= limit; ++digit) {
            bool next_tight = tight && (digit == limit);
            bool next_leading_zero = leading_zero && (digit == 0);

            int localized_waviness = 0;
            
            // Core Validation: Check if the 'prev' digit represents a peak or valley
            // Valid only if 'prev' and 'prev_prev' are real structural digits (not leading zeros / placeholders)
            if (!leading_zero && prev != 11 && prev_prev != 11) {
                if (prev > prev_prev && prev > digit) {
                    localized_waviness = 1; // Peak detected
                } else if (prev < prev_prev && prev < digit) {
                    localized_waviness = 1; // Valley detected
                }
            }

            // Define next look-behind states for recursion
            int next_prev = next_leading_zero ? 11 : digit;
            int next_prev_prev = next_leading_zero ? 11 : prev;

            State next_state = countWaviness(idx + 1, next_prev, next_prev_prev, next_tight, next_leading_zero);

            res.count += next_state.count;
            res.waviness_sum += next_state.waviness_sum + (localized_waviness * next_state.count);
        }

        visited[idx][prev][prev_prev][tight][leading_zero] = true;
        return dp[idx][prev][prev_prev][tight][leading_zero] = res;
    }

    long long solve(long long val) {
        if (val < 100) return 0; // Values lower than 3 digits contain 0 waviness by definition
        
        num_str = to_string(val);
        memset(visited, false, sizeof(visited));
        
        // Setup initial parameters: index 0, dummy digits (11), absolute tight upper bound, true leading zero state
        return countWaviness(0, 11, 11, true, true).waviness_sum;
    }

public:
    long long totalWaviness(long long num1, long long num2) {
        // Optimize standard standard I/O streams for competitive programming speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        return solve(num2) - solve(num1 - 1);
    }
};