/*
Problem: Removing Minimum and Maximum From Array
Link: LeetCode 2091 - Removing Minimum and Maximum From Array

Difficulty: Medium
Tags: Array, Greedy, Math

Intuition:
To remove both the minimum and maximum elements, we need to find their 0-based indices `idx1` and `idx2` in `nums`.
Let `left = min(idx1, idx2)` be the smaller index and `right = max(idx1, idx2)` be the larger index.

There are 3 possible deletion strategies:
1. Delete both from the front (left side):
   - Deletions needed = `right + 1`
2. Delete both from the back (right side):
   - Deletions needed = `n - left`
3. Delete one from the front and one from the back:
   - Deletions needed = `(left + 1) + (n - right)`

The answer is simply the minimum of these 3 strategies.

---

Approach:

1. Find Indices:
   * Iterate through `nums` to find the indices of the minimum and maximum elements.
   * Assign `left = min(min_idx, max_idx)` and `right = max(min_idx, max_idx)`.

2. Calculate Deletions:
   * Strategy 1: `right + 1`
   * Strategy 2: `n - left`
   * Strategy 3: `(left + 1) + (n - right)`

3. Return `min({option1, option2, option3})`.

---

⏱ Time Complexity:
O(N)

* A single pass over `nums` finds the minimum and maximum elements.
* Total Runtime: O(N) linear time.

Space Complexity:
O(1) Auxiliary Space

* Uses only a few integer variables.
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = nums.size();
        if (n == 1) return 1;

        int min_idx = 0;
        int max_idx = 0;

        for (int i = 1; i < n; ++i) {
            if (nums[i] < nums[min_idx]) {
                min_idx = i;
            }
            if (nums[i] > nums[max_idx]) {
                max_idx = i;
            }
        }

        int left = min(min_idx, max_idx);
        int right = max(min_idx, max_idx);

        // Option 1: Delete both from the front
        int op1 = right + 1;

        // Option 2: Delete both from the back
        int op2 = n - left;

        // Option 3: Delete left from front and right from back
        int op3 = (left + 1) + (n - right);

        return min({op1, op2, op3});
    }
};