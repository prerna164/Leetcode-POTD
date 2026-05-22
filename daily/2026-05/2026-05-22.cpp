/*
Problem: Search in Rotated Sorted Array
Link: LeetCode 33

Date: 2026-05-22
Difficulty: Medium
Tags: Array, Binary Search

🧠 Intuition:
The problem demands an O(log n) solution, which immediately points to Binary Search. However, the array is rotated at an unknown pivot point. 

The core realization for a rotated sorted array is that whenever you divide it in half using a midpoint (`mid`), at least one of the two halves (left or right) is guaranteed to remain strictly sorted. 
For example, if the array is [4, 5, 6, 7, 0, 1, 2] and `mid` points to 7:
- The left half [4, 5, 6, 7] is perfectly sorted.
- The right half [7, 0, 1, 2] is not sorted.

We can exploit this property. By checking which half is sorted, we can determine whether our `target` lies within the boundaries of that sorted half. If it does, we narrow our search space to that half. If it doesn't, we can safely discard that entire sorted half and look into the other, un-pivoted portion of the array.

--------------------------------------------------------

⚙️ Approach:
1. Initialize two pointers: `low = 0` and `high = nums.size() - 1`.
2. Enter a `while` loop that continues as long as `low <= high`.
3. Calculate the middle index: `mid = low + (high - low) / 2` (to prevent integer overflow).
4. If `nums[mid] == target`, we found the target, so return `mid`.
5. Identify which half of the array is normally sorted:
   - **Case A: Left half is sorted** (`nums[low] <= nums[mid]`)
     - Check if the target falls within the sorted left boundaries: `target >= nums[low] && target < nums[mid]`.
     - If true, the target must be on the left; update `high = mid - 1`.
     - If false, eliminate the left half; update `low = mid + 1`.
   - **Case B: Right half is sorted** (`nums[low] > nums[mid]`)
     - Check if the target falls within the sorted right boundaries: `target > nums[mid] && target <= nums[high]`.
     - If true, the target must be on the right; update `low = mid + 1`.
     - If false, eliminate the right half; update `high = mid - 1`.
6. If the loop terminates without finding the target, return `-1`.

--------------------------------------------------------

⏱ Time Complexity:
O(log n)
- Just like classical binary search, we cut the search space exactly in half during every iteration. 
- Even though there is conditional checking to identify the sorted half, it takes O(1) constant operations per step.

📦 Space Complexity:
O(1)
- The algorithm modifies pointers in place and uses an iterative approach.
- Only a fixed number of auxiliary integer variables (`low`, `high`, `mid`) are declared, consuming constant extra memory.

*/

#include <vector>

using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            // Target found
            if (nums[mid] == target) {
                return mid;
            }

            // Step 1: Check if the left portion is sorted
            if (nums[low] <= nums[mid]) {
                // Step 2: Determine if target lies inside the sorted left boundary
                if (target >= nums[low] && target < nums[mid]) {
                    high = mid - 1; // Discard right side, search left
                } else {
                    low = mid + 1;  // Discard left side, search right
                }
            } 
            // Step 3: Otherwise, the right portion must be sorted
            else {
                // Step 4: Determine if target lies inside the sorted right boundary
                if (target > nums[mid] && target <= nums[high]) {
                    low = mid + 1;  // Discard left side, search right
                } else {
                    high = mid - 1; // Discard right side, search left
                }
            }
        }

        // Target does not exist in the array
        return -1;
    }
};