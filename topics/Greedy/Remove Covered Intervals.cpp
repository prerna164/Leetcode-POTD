/*
Problem: Remove Covered Intervals
Link: Interval Enclosure Greedy Removal Strategy

Date: 2026-07-06
Difficulty: Medium
Tags: Array, Sorting, Greedy

Intuition:
An interval $[a, b)$ is covered by another interval $[c, d)$ if $c \le a$ and $b \le d$. This means the covering interval must start earlier (or at the same time) and end later (or at the same time).

To find these overlaps easily, we can sort the intervals using a specific greedy custom comparator:
1. Sort by the **start point in ascending order**. This ensures that for any subsequent interval, its start point will always be $\ge$ the start point of previous intervals ($c \le a$ is naturally satisfied).
2. If two intervals share the exact same start point, sort them by their **end point in descending order**. This places the larger, more inclusive interval first, meaning any identical start-point intervals that follow will immediately be recognized as completely covered.

After sorting, we perform a linear scan while maintaining the maximum end point (`max_end`) seen so far among non-covered intervals. For each interval:
- If its end point is $\le$ `max_end`, it is completely enclosed by a previous interval, so we increment our removed intervals counter.
- If its end point is strictly $>$ `max_end`, it extends past previous boundaries. It cannot be covered, so we update `max_end` to this new end point.

---

Approach:

1. Custom Sort:
   * Sort the `intervals` vector using a lambda comparator:
     ```cpp
     sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
         if (a[0] == b[0]) return a[1] > b[1];
         return a[0] < b[0];
     });
     ```

2. Linear Sweep:
   * Initialize `removed_count = 0` and `max_end = 0`.
   * Loop through each interval:
     - If `curr[1] <= max_end`, increment `removed_count`.
     - Else, update `max_end = curr[1]`.

3. Result Payload:
   * The number of remaining intervals is simply `intervals.size() - removed_count`.

---

⏱ Time Complexity:
O(N log N)

* Sorting the array dominates the time complexity, requiring $O(N \log N)$ comparison operations.
* The subsequent linear filtering pass takes $O(N)$ time.
* With $N \le 1000$, total steps are well under $10^4$, executing in less than 1 millisecond.

Space Complexity:
O(1) Auxiliary Space

* Sorting can be completed in-place inside the passed vector, using no additional memory structures.
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        // Step 1: Sort by start point ascending, and by end point descending if starts match
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] == b[0]) {
                return a[1] > b[1];
            }
            return a[0] < b[0];
        });

        int removed_count = 0;
        int max_end = 0;

        // Step 2: Linear scan to detect and drop covered intervals
        for (const auto& interval : intervals) {
            int current_end = interval[1];

            // If the current interval's right boundary is swallowed by max_end, it's covered
            if (current_end <= max_end) {
                removed_count++;
            } else {
                // Otherwise, this interval expands further, becoming the new tracking ceiling
                max_end = current_end;
            }
        }

        // Return the number of remaining valid intervals
        return intervals.size() - removed_count;
    }
};