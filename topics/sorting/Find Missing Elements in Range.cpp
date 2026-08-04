/*
Problem: Find Missing Elements in Range
Link: LeetCode - Find Missing Elements in Range

Difficulty: Easy
Tags: Array, Hash Table, Sorting

Intuition:
We are given an array `nums` of unique integers that originally formed a continuous range of numbers from a minimum value (`min_val`) to a maximum value (`max_val`).
Some numbers inside this range may be missing, but the minimum and maximum elements of the range are guaranteed to still be present in `nums`.

To find the missing elements:
1. Identify the minimum element (`min_val`) and maximum element (`max_val`) in `nums`.
2. Store all elements present in `nums` in a boolean lookup array/hash set for $O(1)$ presence check.
3. Iterate through every integer `x` from `min_val` to `max_val`. If `x` is not present in `nums`, collect `x` into our result vector.

---

Approach:

1. Identify Extremes & Presence Lookup:
   * Find `min_val = *min_element(nums.begin(), nums.end())`.
   * Find `max_val = *max_element(nums.begin(), nums.end())`.
   * Use a boolean vector/array `present` of size 101 (given constraints $1 \le nums[i] \le 100$) to mark numbers existing in `nums`.

2. Collect Missing Numbers:
   * Loop through numbers `x` from `min_val` to `max_val`.
   * If `!present[x]`, push `x` to the `result` vector.
   * Since we iterate sequentially from `min_val` to `max_val`, the resulting list is naturally sorted.

---

⏱ Time Complexity:
O(N + (MAX - MIN))

* Finding the min/max and building the lookup set takes $O(N)$ time where $N = \text{nums.length}$.
* Iterating from `min_val` to `max_val` takes $O(\text{MAX} - \text{MIN})$ time.
* Since $N \le 100$ and $nums[i] \le 100$, total operations are at most ~200, making execution practically $O(1)$.

Space Complexity:
O(1) Auxiliary Space (excluding output vector)

* A boolean array of fixed size 101 uses $O(1)$ extra space.
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int minVal = nums[0];
        int maxVal = nums[0];
        vector<bool> present(101, false);

        for (int x : nums) {
            minVal = min(minVal, x);
            maxVal = max(maxVal, x);
            present[x] = true;
        }

        vector<int> missing;
        for (int x = minVal; x <= maxVal; ++x) {
            if (!present[x]) {
                missing.push_back(x);
            }
        }

        return missing;
    }
};