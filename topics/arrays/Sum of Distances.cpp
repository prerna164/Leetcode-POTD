/*
Problem: 2615. Sum of Distances
Link: https://leetcode.com/problems/sum-of-distances/

Difficulty: Medium
Tags: Array, Hash Table, Prefix Sum

-----------------------------------------------------

🧠 Intuition:
- We need the sum of |i - j| for all indices j where nums[i] == nums[j].
- For a specific value at indices [p0, p1, ..., pk], at index pi:
  Distance = (pi - p0) + (pi - p1) + ... + (pj - pi) + (pk - pi)
- This simplifies to: 
  (i * pi - sum_left) + (sum_right - (k - i) * pi)
- This allows O(N) total time instead of O(N^2).

-----------------------------------------------------

⚙️ Approach:
1. Group Indices: Use an unordered_map to store a list of indices for each unique number.
2. Standard Iteration: Use `it->first` (value) and `it->second` (indices) to ensure compatibility with older C++ standards.
3. Prefix Sum: For each group, calculate total index sum, then iterate while tracking `leftSum` to solve the distance equation in O(1).

-----------------------------------------------------

⏱ Time Complexity:
O(N) - Two linear passes: one to group and one to calculate.

📦 Space Complexity:
O(N) - To store the map of indices and the result vector.

-----------------------------------------------------
*/

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        int n = nums.size();
        vector<long long> arr(n, 0);
        unordered_map<int, vector<int>> indicesMap;

        // Step 1: Group all indices by their value
        for (int i = 0; i < n; ++i) {
            indicesMap[nums[i]].push_back(i);
        }

        // Step 2: Calculate distances using prefix sums
        // Using iterator to avoid C++17 structured binding errors
        for (auto it = indicesMap.begin(); it != indicesMap.end(); ++it) {
            const vector<int>& pos = it->second;
            int k = pos.size();
            if (k <= 1) continue; 

            long long totalSum = 0;
            for (int p : pos) totalSum += p;

            long long leftSum = 0;
            for (int i = 0; i < k; ++i) {
                long long p_i = pos[i];
                long long rightSum = totalSum - leftSum - p_i;
                
                long long leftCount = i;
                long long rightCount = k - 1 - i;

                // formula: (leftCount * p_i - leftSum) + (rightSum - rightCount * p_i)
                arr[p_i] = (leftCount * p_i - leftSum) + (rightSum - rightCount * p_i);
                
                leftSum += p_i;
            }
        }

        return arr;
    }
};