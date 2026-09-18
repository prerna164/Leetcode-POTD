/*
Problem: Maximum Number of Non-Overlapping Substrings
Link: LeetCode 1520 - Maximum Number of Non-Overlapping Substrings

Difficulty: Hard
Tags: String, Greedy, Two Pointers, Prefix Sum / Interval Scheduling

Intuition:
We need to find non-overlapping valid substrings such that:
1. Every character inside a chosen substring must have ALL of its occurrences within that substring.
2. We maximize the NUMBER of chosen substrings.
3. If there is a tie in the count of substrings, we minimize the TOTAL LENGTH.

Step 1: Finding Valid Substrings
- First, record the first and last occurrence index for every unique character in `s`.
- A character `c` forces its valid substring to span at least from `first[c]` to `last[c]`.
- As we expand the boundary from `first[c]` to `last[c]`, any other character `ch` enclosed within this range might have occurrences outside current boundaries, forcing us to extend `right = max(right, last[ch])` and check `left = min(left, first[ch])`.
- If expanding the boundary pulls in a character whose `first` occurrence is BEFORE our starting character's `first` occurrence, then starting a valid substring at `first[c]` is impossible (it would have to start earlier, which will be handled when considering that earlier character).

Step 2: Maximizing Count & Minimizing Total Length (Interval Scheduling)
- Once all valid intervals `[L, R]` are generated, this reduces to the classic Activity Selection / Interval Scheduling problem.
- To maximize the number of non-overlapping intervals and minimize length:
  - Sort all valid intervals by their END points (`R`) in ascending order.
  - Iterate through the sorted intervals. If an interval starts strictly after the last selected interval's end point (`L > prev_R`), select it greedily!

---

Approach:

1. Identify Character Ranges:
   * Maintain `first_occ[26]` and `last_occ[26]` arrays initialized to `-1`.
   * Fill occurrences in a single pass over `s`.

2. Expand and Validate Intervals:
   * For each character `ch` present in `s`, start with range `[L, R] = [first_occ[ch], last_occ[ch]]`.
   * Expand `R` dynamically by checking all characters `s[i]` for `i` between `L` and `R`.
   * If `first_occ[s[i]] < L`, invalidate this start point (since a valid interval containing `ch` would need to start at or before `first_occ[s[i]]`).
   * If valid, record `[L, R]` as a valid interval candidate.

3. Greedy Interval Selection:
   * Sort valid intervals by `R` ascending.
   * Iterate and greedily select non-overlapping intervals (`L > prev_R`).

4. Extract and return `s.substr(L, R - L + 1)` for each selected interval.

---

⏱ Time Complexity:
O(N + 26 * N) = O(N)

* Finding character bounds takes $O(N)$ time.
* Extending ranges for at most 26 unique characters takes $O(26 \cdot N) = O(N)$ time.
* Sorting at most 26 valid intervals takes $O(26 \log 26) = O(1)$ time.
* Total Runtime: $O(N)$ linear time.

Space Complexity:
O(1) Auxiliary Space (excluding output space)

* Storing character bounds and valid intervals requires arrays of max size 26.
*/

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
private:
    struct Interval {
        int l, r;
    };

public:
    vector<string> maxNumOfSubstrings(string s) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = s.length();
        vector<int> first_occ(26, -1);
        vector<int> last_occ(26, -1);

        for (int i = 0; i < n; ++i) {
            int ch = s[i] - 'a';
            if (first_occ[ch] == -1) {
                first_occ[ch] = i;
            }
            last_occ[ch] = i;
        }

        vector<Interval> valid_intervals;

        // Try forming a valid substring starting at the first occurrence of each character
        for (int i = 0; i < 26; ++i) {
            if (first_occ[i] == -1) continue;

            int l = first_occ[i];
            int r = last_occ[i];
            bool valid = true;

            for (int j = l; j <= r; ++j) {
                int ch = s[j] - 'a';
                // If a character inside [l, r] started before l, this start point l cannot form a valid minimal interval
                if (first_occ[ch] < l) {
                    valid = false;
                    break;
                }
                r = max(r, last_occ[ch]);
            }

            if (valid) {
                valid_intervals.push_back({l, r});
            }
        }

        // Sort valid intervals by right endpoint (greedy interval scheduling)
        sort(valid_intervals.begin(), valid_intervals.end(), [](const Interval& a, const Interval& b) {
            return a.r < b.r;
        });

        vector<string> result;
        int prev_r = -1;

        for (const auto& interval : valid_intervals) {
            if (interval.l > prev_r) {
                result.push_back(s.substr(interval.l, interval.r - interval.l + 1));
                prev_r = interval.r;
            }
        }

        return result;
    }
};