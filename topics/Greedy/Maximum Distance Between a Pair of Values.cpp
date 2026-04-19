/*
Problem: 1855. Maximum Distance Between a Pair of Values
Link: https://leetcode.com/problems/maximum-distance-between-a-pair-of-values/

Difficulty: Medium
Tags: Array, Two Pointers, Binary Search, Greedy

-----------------------------------------------------

🧠 Intuition:
- We have two non-increasing arrays (sorted in descending order).
- We need to find indices (i, j) such that i <= j and nums1[i] <= nums2[j], maximizing (j - i).
- Because both arrays are non-increasing:
    - If nums1[i] is too large for nums2[j], moving j further right won't help (nums2[j] will only get smaller). We must move i forward to find a smaller value in nums1.
    - If nums1[i] <= nums2[j], we have a valid pair. We should try to increase j to see if we can find a larger distance, as nums1[i] might still be <= subsequent elements in nums2.

-----------------------------------------------------

⚙️ Approach:
1. Initialize two pointers: i = 0 (for nums1) and j = 0 (for nums2).
2. Initialize maxDist = 0.
3. Use a while loop that runs as long as i < nums1.size() and j < nums2.size().
4. Check the condition: nums1[i] <= nums2[j].
   - If TRUE:
     - The pair (i, j) is valid.
     - Calculate the distance j - i and update maxDist.
     - Increment j to explore potentially larger distances.
   - If FALSE:
     - nums1[i] is too large. Increment i to point to a smaller (or equal) value in nums1.
5. Note: Since we only care about i <= j, even if i surpasses j during the i++ step, the logic holds because j - i would be negative and not affect maxDist.

-----------------------------------------------------

⏱ Time Complexity:
O(N + M) - We traverse through both arrays using pointers i and j. Each pointer is incremented at most once for each element.

📦 Space Complexity:
O(1) - Only a few integer variables are used, regardless of the input size.

-----------------------------------------------------
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        int i = 0; // Pointer for nums1
        int j = 0; // Pointer for nums2
        int maxDist = 0;
        int n1 = nums1.size();
        int n2 = nums2.size();

        // Standard two-pointer approach for non-increasing arrays
        while (i < n1 && j < n2) {
            // Condition for a valid pair: i <= j and nums1[i] <= nums2[j]
            if (nums1[i] <= nums2[j]) {
                // Valid pair found, update max distance
                maxDist = max(maxDist, j - i);
                // Try to increase j to find an even larger distance
                j++;
            } else {
                // nums1[i] is too large for the current nums2[j].
                // Since nums1 is non-increasing, we must move to a 
                // larger index in nums1 to find a smaller value.
                i++;
            }
        }

        return maxDist;
    }
};