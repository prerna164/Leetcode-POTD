/*
Problem: 3740. Minimum Distance Between Three Equal Elements I
Link: https://leetcode.com/problems/minimum-distance-between-three-equal-elements-i/

Date: 2026-04-10
Difficulty: Easy
Tags: Array, Hash Table, Sliding Window

-----------------------------------------------------

🧠 Intuition:
- We need to find three identical numbers with indices (i, j, k). 
- If we assume i < j < k, the distance formula simplifies:
  Distance = (j - i) + (k - j) + (k - i) 
           = (k - i) + (k - i) 
           = 2 * (k - i)
- To minimize this distance, we need to minimize the gap between the 
  first and the third occurrence of the same number.
- The minimum gap for any three identical numbers will always be found 
  between three consecutive occurrences of that number in the array.

-----------------------------------------------------

⚙️ Approach:
1. Use a Hash Map (`unordered_map`) to store all indices for each unique 
   number in the array.
2. For each number that appears at least 3 times:
   - Iterate through its list of indices using a sliding window of size 3.
   - For every triplet of consecutive indices (v[i], v[i+1], v[i+2]), 
     calculate the distance: 2 * (v[i+2] - v[i]).
   - Track the overall minimum distance found.
3. If no triplet is found, return -1.

-----------------------------------------------------

⏱ Time Complexity:
O(N) - We traverse the input array once to build the map, and then 
iterate through the indices stored in the map. Each index is visited exactly twice.

📦 Space Complexity:
O(N) - In the worst case (all numbers are distinct), we store N entries 
in the hash map.

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
        unordered_map<int, vector<int>> mp;
        int n = nums.size();
        
        // Step 1: Group indices by their values
        for (int i = 0; i < n; i++) {
            mp[nums[i]].push_back(i);
        }
        
        int ans = INT_MAX;

        // Step 2: Iterate through each group of indices
        for (auto &it : mp) {
            vector<int> &v = it.second;

            // Triplet only possible if a number appears at least 3 times
            if (v.size() < 3) continue;
            
            // Step 3: Check consecutive triplets to find minimum 2 * (k - i)
            for (int i = 0; i <= (int)v.size() - 3; i++) {
                int dist = 2 * (v[i + 2] - v[i]);
                ans = min(ans, dist);
            }
        }
        
        return (ans == INT_MAX) ? -1 : ans;
    }
};