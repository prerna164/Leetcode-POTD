/*
Problem: Partition Array According to Given Pivot
Link: Stable Pivot Partitioning Simulation

Date: 2026-06-08
Difficulty: Medium
Tags: Array, Two Pointers, Simulation

Intuition:
The problem requires us to rearrange an array around a given `pivot` value such that all elements smaller than the pivot appear first, followed by all elements equal to the pivot, and finally all elements greater than the pivot. Crucially, the relative order of elements within the smaller and larger groups must be strictly preserved (a stable partition).

A naive approach using sorting would violate the stable condition or increase time complexity unnecessarily. Since we need to maintain exact relative ordering, we can use a linear simulation with a temporary tracking array. 
By calculating exactly how many elements are strictly smaller than the pivot and how many are equal to it, we can predetermine the exact starting index position for each category in our rearranged result:
1. Smaller elements start at index `0`.
2. Equal elements start at index `countSmaller`.
3. Greater elements start at index `countSmaller + countEqual`.

Scanning the array sequentially from left to right allows us to place elements directly into their designated segments, guaranteeing stability in a single optimized pass.

---

Approach:

1. Counting Frequency & Placing Boundaries:
   * Scan through `nums` to count the number of elements strictly smaller than `pivot` (`lesserCount`) and elements equal to `pivot` (`equalCount`).
   * Define three write pointers within a new result array `ans` of the same size as `nums`:
     - `left`: begins at `0` (for elements < pivot)
     - `mid`: begins at `lesserCount` (for elements == pivot)
     - `right`: begins at `lesserCount + equalCount` (for elements > pivot)

2. Direct Stable Placement:
   * Iterate through the original `nums` array from left to right.
   * If `nums[i] < pivot`, assign it to `ans[left]` and increment `left`.
   * If `nums[i] == pivot`, assign it to `ans[mid]` and increment `mid`.
   * If `nums[i] > pivot`, assign it to `ans[right]` and increment `right`.

3. Return Result: The `ans` array is now perfectly partitioned and stable. Return it.

---

⏱ Time Complexity:
O(N)

* We perform one linear pass over `nums` to compute the counts of lesser and equal elements.
* We perform a second linear pass over `nums` to distribute elements stably into the `ans` array.
* For the maximum constraint of N = 10^5, this takes around 2 * 10^5 operations, executing well under 5 milliseconds.

Space Complexity:
O(N) 

* We allocate an auxiliary `ans` array of size N to store and return the rearranged elements.
* Aside from the required output storage and a few indexing pointers, no extra memory maps or dynamic allocations are created.
*/

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> pivotArray(vector<int>& nums, int pivot) {
        // Optimize standard I/O streams for competitive programming speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = nums.size();
        int lesserCount = 0;
        int equalCount = 0;

        // Step 1: Count occurrences to set up pointer starting boundaries
        for (int num : nums) {
            if (num < pivot) {
                lesserCount++;
            } else if (num == pivot) {
                equalCount++;
            }
        }

        // Set placement pointers based on counts
        int left = 0;
        int mid = lesserCount;
        int right = lesserCount + equalCount;

        vector<int> ans(n);

        // Step 2: Fill the array stably by iterating in order
        for (int i = 0; i < n; ++i) {
            if (nums[i] < pivot) {
                ans[left++] = nums[i];
            } else if (nums[i] == pivot) {
                ans[mid++] = nums[i];
            } else {
                ans[right++] = nums[i];
            }
        }

        return ans;
    }
};