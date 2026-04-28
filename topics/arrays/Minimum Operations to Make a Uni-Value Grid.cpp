/*
Problem: Minimum Operations to Make a Uni-Value Grid
Link: https://leetcode.com/problems/minimum-operations-to-make-a-uni-value-grid/

Date: 2026-04-28
Difficulty: Medium
Tags: Array, Math, Sorting, Matrix

-----------------------------------------------------

🧠 Intuition:
- We want to make all elements in a 2D grid equal using the minimum number of 
  operations (adding or subtracting 'x').
- Two numbers 'a' and 'b' can only be made equal if they have the same 
  remainder when divided by 'x' (i.e., a % x == b % x). If any two elements 
  in the grid have different remainders, it is impossible, and we return -1.
- If all elements are compatible, the problem reduces to finding a target value 
  'K' that minimizes the sum of |grid[i][j] - K| / x.
- In mathematics, the value 'K' that minimizes the sum of absolute differences 
  from a set of points is the MEDIAN of those points.

-----------------------------------------------------

⚙️ Approach:
1. Flatten the 2D grid into a 1D list/vector 'arr'.
2. Check for compatibility: Store the remainder of the first element (arr[0] % x). 
   If any subsequent element 'num' has (num % x != remainder), return -1.
3. Sort the flattened array to easily find the median.
4. Select the median: `median = arr[size / 2]`.
5. Calculate the total operations: For each element 'num' in 'arr', the 
   operations needed to reach the median is `abs(num - median) / x`.
6. Return the total sum of operations.

-----------------------------------------------------

⏱ Time Complexity:
- O(N*M log(N*M)): Where N is rows and M is columns. Flattening takes O(N*M), 
  but sorting the resulting array of size N*M dominates the complexity.

📦 Space Complexity:
- O(N*M): We store all elements of the grid in a 1D vector to sort them.

-----------------------------------------------------
*/

#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        int m = grid.size();
        int n = grid[0].size();
        vector<int> arr;

        // 1. Flatten the grid into a 1D vector
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                arr.push_back(grid[i][j]);
            }
        }

        // 2. Check for compatibility (Modulo check)
        int mod = arr[0] % x;
        for (int num : arr) {
            if (num % x != mod) {
                return -1;
            }
        }

        // 3. Sort to find the median
        sort(arr.begin(), arr.end());
        
        // 4. Median minimizes the sum of absolute differences
        int median = arr[arr.size() / 2];
        int operations = 0;

        // 5. Calculate total operations using the median
        for (int num : arr) {
            operations += abs(num - median) / x;
        }

        return operations;
    }
};