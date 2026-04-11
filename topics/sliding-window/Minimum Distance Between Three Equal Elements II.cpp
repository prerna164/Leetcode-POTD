/*
Problem: 3740. Minimum Distance Between Three Equal Elements II
Link: https://leetcode.com/problems/minimum-distance-between-three-equal-elements-i/

Date: 2026-04-11
Difficulty: Easy
Tags: Array, Hash Table, Sliding Window

-----------------------------------------------------

🧠 Intuition:
- We are looking for three indices (i, j, k) where nums[i] == nums[j] == nums[k].
- For any three indices sorted as i < j < k, the distance formula simplifies:
  Distance = abs(i - j) + abs(j - k) + abs(k - i)
           = (j - i) + (k - j) + (k - i)
           = j - i + k - j + k - i
           = 2 * (k - i)
- The middle index 'j' does not affect the total distance! The result only depends 
  on the gap between the first and third occurrence.
- To minimize 2 * (k - i), we need to find the smallest window that contains 
  exactly three occurrences of the same value. This smallest window will always 
  be formed by three *consecutive* occurrences of that value.

-----------------------------------------------------

⚙️ Approach:
1. Use an `unordered_map<int, pair<int, int>>` to track the last two seen 
   indices of every number encountered so far. 
   - `pair.first`: stores the most recent index (index of the 2nd occurrence).
   - `pair.second`: stores the index before that (index of the 1st occurrence).
2. Traverse the array once. For each element `val` at index `i`:
   - Check if `val` exists in the map.
   - If it exists and has a valid `second` index (meaning we've seen it at least 
     twice before), we now have a triplet.
   - Calculate distance: `2 * (current_index - second_last_index)`.
   - Update the global minimum distance.
   - Update the map: current `first` becomes the new `second`, and current 
     index `i` becomes the new `first`.
3. If no triplet is ever found, return -1.

-----------------------------------------------------

⏱ Time Complexity:
O(N) - We iterate through the array exactly once. Each hash map operation 
(insertion and lookup) takes O(1) on average.

📦 Space Complexity:
O(N) - In the worst case, we store two indices for every unique element 
in the array within the hash map.

-----------------------------------------------------
*/

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int minimumDistance(vector<int>& nums) {
        int n = nums.size();
        // Map: value -> {last_seen_index, second_last_seen_index}
        unordered_map<int, pair<int, int>> lastIndices;
        int min_dist = INT_MAX;
        bool found = false;

        for (int i = 0; i < n; ++i) {
            int val = nums[i];

            if (lastIndices.count(val)) {
                int prev1 = lastIndices[val].first;  // Most recent index
                int prev2 = lastIndices[val].second; // Index before the most recent

                // If prev2 is not -1, it means we have at least 3 occurrences now
                if (prev2 != -1) {
                    // Distance is 2 * (k - i) where k is current i and i is prev2
                    int current_dist = 2 * (i - prev2);
                    if (current_dist < min_dist) {
                        min_dist = current_dist;
                    }
                    found = true;
                }
                
                // Shift the indices: 
                // The previous 'first' is now the 'second' oldest, 
                // and the current 'i' is the 'first' oldest.
                lastIndices[val] = {i, prev1};
            } else {
                // First time encountering this number
                lastIndices[val] = {i, -1};
            }
        }

        return found ? min_dist : -1;
    }
};