/*
Problem: Largest Almost Missing Integer
Link: LeetCode 3471 - Largest Almost Missing Integer

Difficulty: Easy
Tags: Array, Hash Table, Counting

Intuition:
An integer `x` is "almost missing" if it appears in EXACTLY one subarray of size `k` within `nums`.
We need to find the largest such integer, or return `-1` if none exists.

Key Observations Based on Subarray Size `k`:
1. Case 1: `k == 1`
   - Subarrays of size 1 are just individual elements.
   - An element `x` appears in exactly 1 subarray of size 1 if and only if `x` appears exactly once in the whole array `nums`.
   - Solution: Find the maximum element with frequency 1 in `nums`.

2. Case 2: `k == N` (where N = nums.size())
   - There is only 1 subarray of size `k` (the whole array `nums`).
   - Every unique element present in `nums` appears in this single subarray.
   - Solution: Return the maximum overall element present in `nums`.

3. Case 3: `1 < k < N`
   - Only the first element `nums[0]` and the last element `nums[N - 1]` can appear in exactly 1 subarray of size `k`.
   - Any element in the interior `nums[1 ... N - 2]` will be covered by at least 2 distinct sliding windows of size `k`.
   - Therefore, the candidates can only be `nums[0]` (if it occurs nowhere else) and `nums[N - 1]` (if it occurs nowhere else).

Alternatively, since constraints are very small ($N \le 50$), we can directly count how many subarrays of size $k$ contain each distinct element by generating all $N - k + 1$ subarrays of size $k$.

---

Approach:

1. Maintain Subarray Presence Counts:
   * Use a hash map `subarray_count` to keep track of how many size-`k` subarrays contain each number `x`.

2. Slide Window of Size `k`:
   * For every starting index `i` from `0` to `N - k`:
     - Collect unique elements within subarray `nums[i ... i + k - 1]`.
     - Increment `subarray_count[x]` by 1 for each unique element `x` in that subarray.

3. Find Maximum Almost Missing Integer:
   * Iterate over `subarray_count`.
   * Find the maximum `x` such that `subarray_count[x] == 1`.
   * Return the max `x`, or `-1` if no element has count equal to 1.

---

⏱ Time Complexity:
O(N * k)

* There are $N - k + 1$ subarrays of size $k$.
* Processing each subarray takes $O(k)$ time.
* Total operations $\le 50 \times 50 = 2500$, executing nearly instantaneously.

Space Complexity:
O(N) Auxiliary Space

* Hash map stores counts for at most $N$ distinct numbers.
*/

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = nums.size();
        unordered_map<int, int> subarray_count;

        // Iterate through all possible subarrays of size k
        for (int i = 0; i <= n - k; ++i) {
            unordered_set<int> unique_in_subarray(nums.begin() + i, nums.begin() + i + k);
            for (int x : unique_in_subarray) {
                subarray_count[x]++;
            }
        }

        int ans = -1;
        // Find the maximum element that appears in exactly 1 subarray of size k
        for (auto& [val, count] : subarray_count) {
            if (count == 1) {
                ans = max(ans, val);
            }
        }

        return ans;
    }
};