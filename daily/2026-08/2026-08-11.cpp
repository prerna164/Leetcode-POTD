/*
Problem: Smallest Missing Integer Greater Than Sequential Prefix Sum
Link: LeetCode 2996 - Smallest Missing Integer Greater Than Sequential Prefix Sum

Difficulty: Easy
Tags: Array, Hash Table, Sorting

Intuition:
We are given an array `nums`. A sequential prefix is a subarray starting at index 0 where each subsequent element is strictly 1 greater than its predecessor (`nums[j] == nums[j - 1] + 1`).

1. Find the Longest Sequential Prefix Sum:
   - Start at index 0 and compute the prefix sum as long as `nums[j] == nums[j - 1] + 1`.
   - The loop stops at the first index where this sequential condition breaks.

2. Find the Smallest Missing Integer >= Prefix Sum:
   - Store all elements of `nums` in an unordered hash set (or lookup table) for O(1) existence checks.
   - Starting from `x = sum`, increment `x` by 1 until we find a value `x` that is NOT present in `nums`.
   - Return `x`.

---

Approach:

1. Sum the Longest Sequential Prefix:
   * Initialize `sum = nums[0]`.
   * Iterate `i` from `1` to `nums.size() - 1`.
   * If `nums[i] == nums[i - 1] + 1`, add `nums[i]` to `sum`.
   * Otherwise, break out of the loop.

2. Unordered Set Lookup:
   * Populate an `unordered_set<int>` with elements from `nums`.

3. Find Missing Value:
   * Starting with `x = sum`, check if `x` exists in the set.
   * While `x` exists in the set, increment `x++`.
   * Return `x`.

---

⏱ Time Complexity:
O(N)

* Finding the sequential prefix takes O(N) where N = nums.length.
* Building the unordered set takes O(N) time.
* Checking and incrementing `x` takes at most O(N) steps because at most N unique integers exist in `nums`.
* Overall Runtime: O(N) linear time.

Space Complexity:
O(N) Auxiliary Space

* Hash set requires storage for at most N elements.
*/

#include <vector>
#include <unordered_set>
#include <iostream>

using namespace std;

class Solution {
public:
    int missingInteger(vector<int>& nums) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int sum = nums[0];

        // Step 1: Calculate sum of the longest sequential prefix
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] == nums[i - 1] + 1) {
                sum += nums[i];
            } else {
                break;
            }
        }

        // Step 2: Store elements in a hash set for O(1) lookup
        unordered_set<int> present(nums.begin(), nums.end());

        // Step 3: Find smallest integer >= sum missing from nums
        while (present.count(sum)) {
            sum++;
        }

        return sum;
    }
};