/*
Problem: Smallest Stable Index II
Link: LeetCode (Smallest Stable Index)

Difficulty: Medium
Tags: Array, Prefix / Suffix Processing

Intuition:
For each index `i` from `0` to `n - 1`:
- `prefix_max[i]` represents the maximum value in `nums[0...i]`.
- `suffix_min[i]` represents the minimum value in `nums[i...n-1]`.
- Instability score at `i` is defined as `prefix_max[i] - suffix_min[i]`.

We need to return the smallest index `i` where `prefix_max[i] - suffix_min[i] <= k`.

To compute this efficiently:
1. Compute a `suffix_min` array where `suffix_min[i]` stores the minimum element from index `i` to `n - 1`.
2. Iterate from left to right while updating `prefix_max`. At each step `i`, calculate `prefix_max - suffix_min[i]`.
3. Return the first index `i` where the instability score is `<= k`. If no such index exists, return `-1`.

---

Approach:

1. Precompute Suffix Minimums:
   * Build an array `suffix_min` of size `n`.
   * Set `suffix_min[n - 1] = nums[n - 1]`.
   * Traverse backwards from `n - 2` down to `0` filling `suffix_min[i] = min(nums[i], suffix_min[i + 1])`.

2. Iterate and Check Instability Score:
   * Maintain `running_max = nums[0]`.
   * For each index `i` from `0` to `n - 1`:
     - Update `running_max = max(running_max, nums[i])`.
     - Calculate `instability = running_max - suffix_min[i]`.
     - If `instability <= k`, return `i`.

3. Return `-1` if no stable index is found.

---

⏱ Time Complexity:
O(N)

* One backward pass to compute `suffix_min` and one forward pass to check instability scores.
* Total Runtime: O(N) linear time.

Space Complexity:
O(N) Auxiliary Space

* Space used for the `suffix_min` array of size N.
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = nums.size();
        vector<int> suffix_min(n);

        suffix_min[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            suffix_min[i] = min(nums[i], suffix_min[i + 1]);
        }

        int running_max = 0;
        for (int i = 0; i < n; ++i) {
            running_max = max(running_max, nums[i]);
            long long instability = (long long)running_max - suffix_min[i];

            if (instability <= k) {
                return i;
            }
        }

        return -1;
    }
};