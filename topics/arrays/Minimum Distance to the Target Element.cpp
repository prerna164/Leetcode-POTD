/*
Problem: 1848. Minimum Distance to the Target Element
Link: https://leetcode.com/problems/minimum-distance-to-the-target-element/

Difficulty: Easy
Tags: Array, Iteration

-----------------------------------------------------

🧠 Intuition:
- We need to find the index 'i' where nums[i] matches the target.
- Among all matching indices, we want the one that minimizes the absolute gap from the given 'start' index.
- Since the array size is small (up to 1000), a single linear scan is the most efficient way to check all possibilities.

-----------------------------------------------------

⚙️ Approach:
1. Initialize a variable `minDist` with a very large value (INT_MAX).
2. Loop through the array from i = 0 to nums.size() - 1.
3. If nums[i] is equal to target:
   - Calculate the distance: abs(i - start).
   - If this distance is smaller than our current `minDist`, update `minDist`.
4. Optimization: If we find a distance of 0, we can return it immediately as it is the smallest possible distance.
5. Return the final `minDist`.

-----------------------------------------------------

⏱ Time Complexity:
O(N) - We traverse the array exactly once, where N is the number of elements in nums.

📦 Space Complexity:
O(1) - We only use a constant amount of extra space for variables (minDist, i, etc.).

-----------------------------------------------------
*/

#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int getMinDistance(vector<int>& nums, int target, int start) {
        int minDist = INT_MAX;
        int n = nums.size();
        
        for (int i = 0; i < n; ++i) {
            // Check if the current element matches our target
            if (nums[i] == target) {
                // Calculate the absolute distance
                int currentDist = abs(i - start);
                
                // Update min_dist if the current one is smaller
                if (currentDist < minDist) {
                    minDist = currentDist;
                }
                
                // Optimization: If distance is 0, we can't get any smaller
                if (minDist == 0) return 0;
            }
        }
        
        return minDist;
    }
};