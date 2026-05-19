/*
Problem: Minimum Common Value
Link: LeetCode 2540

Date: 2026-05-19
Difficulty: Easy
Tags: Array, Two Pointers, Binary Search

🧠 Intuition:
We are given two integer arrays, `nums1` and `nums2`, both sorted in non-decreasing order. 
Our objective is to find the smallest integer common to both arrays. If no such element exists, 
we should return -1.

Since both arrays are already sorted, we can exploit this order. Think of how a merge operation 
works in Merge Sort: we compare elements from both arrays sequentially. If we find an equal value, 
it is guaranteed to be the smallest common integer because we are scanning both sorted collections 
from left to right (smallest to largest).

If the elements at our current positions are not equal, we can safely skip the smaller one. 
The smaller element cannot possibly match any subsequent elements in the other array because all 
remaining elements are larger or equal.

--------------------------------------------------------

⚙️ Approach:
1. Two Pointers Initialization: Initialize two pointers, `i = 0` for `nums1` and `j = 0` for `nums2`.
2. Linear Traversal: Run a loop while both pointers are within their respective array boundaries 
   (`i < nums1.size()` and `j < nums2.size()`).
3. Three-way Comparison inside the loop:
   - If `nums1[i] == nums2[j]`: We have found our smallest common element. Return `nums1[i]` immediately.
   - If `nums1[i] < nums2[j]`: The value at `nums1[i]` is too small to find a match in `nums2` moving forward. 
     Advance pointer `i` by 1 (`i++`).
   - If `nums1[i] > nums2[j]`: The value at `nums2[j]` is too small to find a match in `nums1` moving forward. 
     Advance pointer `j` by 1 (`j++`).
4. Fallback: If the loop terminates without finding a match, it implies there is no common element. 
   Return `-1`.

--------------------------------------------------------

⏱ Time Complexity:
O(N + M)
- Where `N` is the length of `nums1` and `M` is the length of `nums2`.
- In the worst-case scenario (e.g., no common element or the common element is at the very end), 
  each pointer traverses its array at most once. Each step increments at least one pointer, 
  leading to a linear time constraint.

📦 Space Complexity:
O(1)
- The algorithm processes the input arrays in-place using only two integer pointers (`i` and `j`).
- No auxiliary data structures (like Hash Sets or Maps) are allocated, ensuring constant space usage.

*/

#include <vector>

using namespace std;

class Solution {
public:
    int getCommon(vector<int>& nums1, vector<int>& nums2) {
        int i = 0; // Pointer for nums1
        int j = 0; // Pointer for nums2
        
        // Loop until one of the pointers runs out of bounds
        while (i < nums1.size() && j < nums2.size()) {
            // Case 1: Found the smallest common element
            if (nums1[i] == nums2[j]) {
                return nums1[i];
            }
            // Case 2: Element in nums1 is smaller; advance nums1 pointer
            else if (nums1[i] < nums2[j]) {
                i++;
            }
            // Case 3: Element in nums2 is smaller; advance nums2 pointer
            else {
                j++;
            }
        }
        
        // Return -1 if no common element exists
        return -1;
    }
};