/*
Problem: Find Minimum in Rotated Sorted Array
Link: LeetCode 153

Date: 2026-05-15
Difficulty: Medium
Tags: Array, Binary Search

🧠 Intuition:

A sorted array that has been rotated will have two sorted sub-parts. For example:
[4, 5, 6, 7, 0, 1, 2]
Part 1: [4, 5, 6, 7] | Part 2: [0, 1, 2]

The minimum element is the "pivot" point where the ascending order breaks. 

Since the problem requires an O(log n) time complexity, binary search is the 
standard tool. The key logic is to compare the middle element with the rightmost 
element to decide which half contains the minimum:

1. If nums[mid] > nums[right]: The minimum must be in the right half (because the 
   rotation caused a drop somewhere after mid).
2. If nums[mid] < nums[right]: The minimum is either at mid or to its left (because 
   the right side is currently in sorted order relative to mid).

--------------------------------------------------------

⚙️ Approach:

1. Initialize two pointers: `left = 0` and `right = n - 1`.
2. While `left < right`:
   - Calculate `mid = left + (right - left) / 2`.
   - Compare `nums[mid]` with `nums[right]`.
   - Case A: `nums[mid] > nums[right]`
     - This means the "inflection point" (minimum) is to the right of mid.
     - Move `left = mid + 1`.
   - Case B: `nums[mid] <= nums[right]`
     - This means the right part is sorted. The minimum could be `mid` itself 
       or something further left.
     - Move `right = mid`.
3. When the loop terminates, `left` and `right` will converge on the index of 
   the minimum element.
4. Return `nums[left]`.

--------------------------------------------------------

⏱ Time Complexity:

O(log n)

- We use binary search, which halves the search space in every iteration.
- For an array of size n, this takes logarithmic time.

📦 Space Complexity:

O(1)

- We only use a few integer variables (`left`, `right`, `mid`).
- No extra space proportional to the input size is required.

*/

#include <vector>

using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;

            // If mid element is greater than the rightmost element, 
            // the minimum must be in the right half.
            if (nums[mid] > nums[right]) {
                left = mid + 1;
            } 
            // Otherwise, the minimum is in the left half including mid.
            else {
                right = mid;
            }
        }

        // Both left and right point to the minimum element.
        return nums[left];
    }
};