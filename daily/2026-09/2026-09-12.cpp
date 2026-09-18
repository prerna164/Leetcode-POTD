/*
Problem: Maximum Score Non-Overlapping Intervals (At Most 4 Intervals)
Link: LeetCode (Maximum Weight Non-Overlapping Intervals)

Difficulty: Hard
Tags: Array, Dynamic Programming, Binary Search, Sorting

Intuition:
We want to select up to 4 mutually non-overlapping intervals such that the total sum of their weights is maximized. 
If multiple selections yield the same maximum total weight, we must return the selection whose array of original indices is lexicographically smallest.

Key Definitions & Constraints:
1. Intervals overlap if they share ANY point (i.e., `l_j <= r_i` means overlapping). Thus, two intervals `i` and `j` are non-overlapping if `l_j > r_i`.
2. We can select $k \in \{1, 2, 3, 4\}$ intervals.

Strategy:
1. Sort Intervals by Right Endpoints:
   - To build a DP state efficiently, sort the intervals by `r` (and tie-break by `l` or original index).
   - Precompute for each interval `i` the largest index `prev_idx` of an interval that ends strictly before `intervals[i].l` (i.e., `intervals[prev_idx].r < intervals[i].l`). We can find `prev_idx` using `std::upper_bound` or `std::lower_bound` on right endpoints.

2. Dynamic Programming State & Lexicographical Ordering:
   - Let `dp[i][k]` be the optimal choice using a subset of the first `i` sorted intervals, picking at most `k` intervals.
   - Each state `dp[i][k]` stores:
     - `weight`: Maximum weight attainable.
     - `indices`: Vector of original 0-based indices corresponding to this optimal weight choice, sorted in ascending order.
   - When comparing two choices `A` and `B` for state `dp[i][k]`:
     - Primary criterion: `weight_A > weight_B`.
     - Secondary criterion: If weights are equal (`weight_A == weight_B`), choose the one whose sorted list of indices is lexicographically smaller.

3. Transitions for `dp[i][k]`:
   For the `i`-th sorted interval (1-based index `i`):
   - Option 1 (Skip interval `i`): Take `dp[i - 1][k]`.
   - Option 2 (Take interval `i`): Take `dp[prev_idx][k - 1]` and append `intervals[i - 1].original_idx`, then sort the index array.
   - Compare Option 1 and Option 2 using our custom comparator (maximize weight, then minimize lexicographical index array).

4. Overall Optimal Result:
   - The answer is the best choice among `dp[N][k]` for $k \in \{1, 2, 3, 4\}$.

---

Approach:

1. Data Preparation:
   * Create a structure/tuple `(l, r, weight, original_index)` for each interval.
   * Sort the intervals array based on `r` (right boundary).
   * Extract right boundaries into a separate array to enable binary search (`std::lower_bound`).

2. Binary Search Precomputation:
   * For each sorted interval `i`, find the largest index `p` (1-based) such that `sorted_intervals[p-1].r < sorted_intervals[i-1].l`.

3. DP Computation:
   * Initialize `dp[N + 1][5]` table with zero weights and empty index vectors.
   * Populate `dp[i][k]` row by row for $i = 1 \dots N$ and $k = 1 \dots 4$.

4. Return Best Result:
   * Find the best `dp[N][k]` across $k \in \{1, 2, 3, 4\}$ and return its index list.

---

⏱ Time Complexity:
O(N log N + N * K * K log K)

* Sorting $N$ intervals takes $O(N \log N)$ time.
* Binary search for each interval takes $O(\log N)$.
* DP transitions run $N \times 4$ times. Each index array has at most 4 elements, so lexicographical comparison and sorting take $O(K \log K)$ where $K = 4$.
* Total Runtime: $O(N \log N)$ time, completing well within the 500ms limit for $N = 5 \times 10^4$.

Space Complexity:
O(N * K) Auxiliary Space

* DP table of size $N \times 5$, where each cell holds a small vector of up to 4 integers.
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct Interval {
    int l, r, weight, id;
};

class Solution {
private:
    struct DPValue {
        long long weight = 0;
        vector<int> indices;

        // Custom comparison operator:
        // 1. Higher total weight is preferred.
        // 2. Lexicographically smaller indices array is preferred.
        bool isBetterThan(const DPValue& other) const {
            if (weight != other.weight) {
                return weight > other.weight;
            }
            return indices < other.indices;
        }
    };

public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = intervals.size();
        vector<Interval> sorted_intervals(n);

        for (int i = 0; i < n; ++i) {
            sorted_intervals[i] = {intervals[i][0], intervals[i][1], intervals[i][2], i};
        }

        // Sort intervals by right endpoint
        sort(sorted_intervals.begin(), sorted_intervals.end(), [](const Interval& a, const Interval& b) {
            if (a.r != b.r) return a.r < b.r;
            if (a.l != b.l) return a.l < b.l;
            return a.id < b.id;
        });

        // Store right endpoints for binary search
        vector<int> right_ends(n);
        for (int i = 0; i < n; ++i) {
            right_ends[i] = sorted_intervals[i].r;
        }

        // Precompute previous non-overlapping interval index (1-based)
        vector<int> prev_idx(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            // Find first interval with right end >= sorted_intervals[i].l
            auto it = lower_bound(right_ends.begin(), right_ends.end(), sorted_intervals[i].l);
            int idx = distance(right_ends.begin(), it);
            prev_idx[i + 1] = idx; // 1-based index
        }

        // dp[i][k] stores optimal choice using a subset of first i sorted intervals, picking at most k intervals
        vector<vector<DPValue>> dp(n + 1, vector<DPValue>(5));

        for (int i = 1; i <= n; ++i) {
            int p = prev_idx[i];
            const auto& current_item = sorted_intervals[i - 1];

            for (int k = 1; k <= 4; ++k) {
                // Option 1: Skip current interval
                DPValue best_val = dp[i - 1][k];

                // Option 2: Include current interval
                DPValue take_val;
                take_val.weight = dp[p][k - 1].weight + current_item.weight;
                take_val.indices = dp[p][k - 1].indices;
                take_val.indices.push_back(current_item.id);
                sort(take_val.indices.begin(), take_val.indices.end());

                if (take_val.isBetterThan(best_val)) {
                    best_val = take_val;
                }

                dp[i][k] = best_val;
            }
        }

        // Find best choice among 1, 2, 3, or 4 intervals taken from all N intervals
        DPValue final_ans = dp[n][1];
        for (int k = 2; k <= 4; ++k) {
            if (dp[n][k].isBetterThan(final_ans)) {
                final_ans = dp[n][k];
            }
        }

        return final_ans.indices;
    }
};