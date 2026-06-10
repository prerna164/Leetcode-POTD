/*
Problem: Maximum Total Subarray Value II (LeetCode 3691)
Link: https://leetcode.com/problems/maximum-total-subarray-value-ii/

Date: 2026-06-10
Difficulty: Hard
Tags: Sparse Table, Heap (Priority Queue), Greedy, Range Queries

Intuition:
The problem asks us to select exactly `k` *distinct* non-empty subarrays to maximize the sum of their values, where the value of a subarray is `max(nums[l..r]) - min(nums[l..r])`. Unlike the first version of this problem where we could select the absolute best subarray `k` times, here each subarray `nums[l..r]` must possess unique coordinate boundaries `(l, r)`. 

Let's look at the monotonicity behavior:
For a fixed left boundary `l`, as the right boundary `r` extends rightward from `l` to `n - 1`, the value `max(nums[l..r]) - min(nums[l..r])` is strictly monotonic non-decreasing. This is because expanding a range can only potentially increase (or keep equal) its maximum element, and decrease (or keep equal) its minimum element.

Thus, for any fixed left index `l`, the maximum value it can ever achieve across the entire array is reached at the maximum possible right boundary: `r = n - 1`. 
This property allows us to model the problem similarly to finding the top-k sums from sorted lists. We can seed a Maximum Heap (Priority Queue) with the initial maximum state for every possible left boundary `l` from `0` to `n - 1`, setting their initial right boundaries to `n - 1`.

The state in the heap will look like `(value, l, r)`. 
When we pop the absolute maximum range value from the heap, we add it to our answer. To discover the next best alternative from that specific left boundary sequence, we decrement its right index to `r - 1` (if `r > l`), calculate its new range value, and push it back into the heap.

To make this approach viable within the performance limits, computing `max(nums[l..r])` and `min(nums[l..r])` must be extremely efficient. We can precalculate a Sparse Table to handle Range Maximum Queries (RMQ) and Range Minimum Queries in static $\mathcal{O}(1)$ time.

---

Approach:

1. Sparse Table Precomputation:
   * Build two 2D tables `st_max[N][logN]` and `st_min[N][logN]` to hold range maximums and minimums for binary-power lengths.
   * Compute log values down to a lookup array `lg` for $\mathcal{O}(1)$ interval size retrieval.

2. Heap Initialization:
   * Create a priority queue `pq` storing tuples or structured elements representing `(value, l, r)`.
   * For every left boundary `l` from `0` to `n - 1`:
     - Query its maximum value at range `[l, n - 1]` using the Sparse Table.
     - Push `(value, l, n - 1)` into the priority queue.

3. Greedy Extraction:
   * Run a loop exactly `k` times.
   * In each iteration, pop the largest element `(value, l, r)` from the max-heap and add `value` to the total accumulated score.
   * If `r > l`, look at the next best candidate for this left boundary by generating `(new_value, l, r - 1)` and pushing it back into the heap.

4. Return Result: Once `k` iterations finish, return the total score.

---

⏱ Time Complexity:
O(N log N + K log N)

* Precomputing the Sparse Table takes $\mathcal{O}(N \log N)$ time.
* Seeding the heap initially takes $\mathcal{O}(N \log N)$ time for $N$ elements.
* The greedy loop runs exactly $K$ times. Each iteration pops from and pushes to the heap, taking $\mathcal{O}(\log N)$ time per step, resulting in $\mathcal{O}(K \log N)$ total time.
* Given $N = 5 \times 10^4$ and $K = 10^5$, the code requires around $2.5 \times 10^6$ operations, passing comfortably within 30–50 milliseconds.

Space Complexity:
O(N log N)

* The Sparse Tables utilize $\mathcal{O}(N \log N)$ auxiliary space.
* The priority queue holds at most $N$ elements at any given point, requiring $\mathcal{O}(N)$ space.
*/

#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <iostream>

using namespace std;

class SparseTable {
    int n;
    int max_log;
    vector<vector<int>> st_max;
    vector<vector<int>> st_min;
    vector<int> lg;

public:
    SparseTable(const vector<int>& nums) {
        n = nums.size();
        max_log = log2(n) + 1;
        st_max.assign(n, vector<int>(max_log));
        st_min.assign(n, vector<int>(max_log));
        lg.assign(n + 1, 0);

        // Precompute logarithm values for O(1) query lookups
        for (int i = 2; i <= n; i++) {
            lg[i] = lg[i / 2] + 1;
        }

        // Base cases for intervals of length 1
        for (int i = 0; i < n; i++) {
            st_max[i][0] = nums[i];
            st_min[i][0] = nums[i];
        }

        // Compute values iteratively for powers of 2
        for (int j = 1; j < max_log; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st_max[i][j] = max(st_max[i][j - 1], st_max[i + (1 << (j - 1))][j - 1]);
                st_min[i][j] = min(st_min[i][j - 1], st_min[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int queryMax(int l, int r) {
        int k = lg[r - l + 1];
        return max(st_max[l][k], st_max[r - (1 << k) + 1][k]);
    }

    int queryMin(int l, int r) {
        int k = lg[r - l + 1];
        return min(st_min[l][k], st_min[r - (1 << k) + 1][k]);
    }

    long long queryValue(int l, int r) {
        return (long long)queryMax(l, r) - queryMin(l, r);
    }
};

class Solution {
private:
    struct SubarrayState {
        long long value;
        int l;
        int r;

        // Custom comparator to turn standard priority_queue into a Max-Heap
        bool operator<(const SubarrayState& other) const {
            return value < other.value;
        }
    };

public:
    long long maxTotalValue(vector<int>& nums, int k) {
        // Optimize standard I/O streams for competitive programming speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = nums.size();
        SparseTable st(nums);
        priority_queue<SubarrayState> pq;

        // Initialize the Max-Heap with the maximum ranges for each left boundary
        for (int l = 0; l < n; ++l) {
            long long val = st.queryValue(l, n - 1);
            pq.push({val, l, n - 1});
        }

        long long totalValueSum = 0;

        // Extract the k largest distinct subarrays greedily
        for (int step = 0; step < k; ++step) {
            SubarrayState current = pq.top();
            pq.pop();

            totalValueSum += current.value;

            // If a next smaller sub-range exists on this left-bound sequence, add it to the heap
            if (current.r > current.l) {
                long long next_val = st.queryValue(current.l, current.r - 1);
                pq.push({next_val, current.l, current.r - 1});
            }
        }

        return totalValueSum;
    }
};