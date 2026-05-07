/*
Problem: Jump Game IX or Maximum Reachable Value (Jump Game Variant)
Link: (Contextual Interview Question)

Date: 2026-05-07
Difficulty: Medium
Tags: Array, Dynamic Programming, Greedy, Prefix Max, Suffix Min

🧠 Intuition:

The core of this problem lies in understanding the "Connected Components" 
created by the jump rules:
1. Forward Jump (i -> j, j > i): Allowed if nums[j] < nums[i] (Downhill).
2. Backward Jump (j -> i, j < i): Allowed if nums[i] > nums[j] (Uphill).

Notice that if i < j and nums[j] < nums[i], then i can jump forward to j, 
and j can jump backward to i. This makes the relationship effectively 
bi-directional between a larger left element and a smaller right element.

As long as we have a "dip" in the values (a smaller value appearing after 
a larger one), those indices can reach each other. The maximum value 
attainable in such a component is the maximum value of the "Peak" in 
that specific range.

A "cut" in the reachability happens only when all values to the left 
are less than or equal to all values to the right. If a prefix maximum 
cannot "see" any smaller value to its right to jump into, it cannot 
propagate its value further.

--------------------------------------------------------

⚙️ Approach:

1. Prefix Maximum Pass:
   Initialize an array `prefixMax` where `prefixMax[i]` stores the 
   maximum value encountered from index 0 to i. Initially, these are 
   the best candidates for the maximum reachable value.

2. Suffix Minimum Tracking:
   Traverse the array from right to left. Maintain the index of the 
   smallest element encountered so far from the right (`suffixMinIdx`).

3. Reachability Propagation:
   - For each index `i` from right to left:
   - Check if the current `prefixMax[i]` can "jump" into a smaller 
     value further to the right. 
   - If `prefixMax[i] > nums[suffixMinIdx]`, it means the peak at the 
     left can jump into the valley at the right.
   - Once they are connected, the index `i` inherits the reachability 
     of that suffix minimum. We update `prefixMax[i]` to be the maximum 
     value reachable from that rightward component.

4. Result:
   The modified `prefixMax` array now contains the maximum value 
   reachable for every index.

--------------------------------------------------------

⏱ Time Complexity:

O(N)

- One pass to compute the initial prefix maximums: O(N).
- One pass to process suffix minimums and propagate reachability: O(N).
- Total time is linear relative to the number of elements.

📦 Space Complexity:

O(N)

- We store the prefix maximums in an array of size N.
- No other significant auxiliary space is used.

*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> maxValue(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return {};

        // Step 1: Compute Prefix Maximums
        // Initially, each index's best hope is the largest value to its left
        vector<int> prefixMax(n);
        prefixMax[0] = nums[0];
        for (int i = 1; i < n; i++) {
            prefixMax[i] = max(prefixMax[i - 1], nums[i]);
        }

        // Step 2: Track Suffix Minimum and Propagate
        // suffixMinIdx tracks the smallest value to the right of current index
        int suffixMinIdx = n - 1;

        for (int i = n - 2; i >= 0; i--) {
            // If the max value available to index i is greater than a value 
            // to its right, a forward jump is possible.
            if (prefixMax[i] > nums[suffixMinIdx]) {
                // By jumping to the right, index i can reach whatever 
                // the right-side component can reach.
                prefixMax[i] = prefixMax[suffixMinIdx];
            }
            
            // Update the suffix minimum index if a smaller value is found
            if (nums[i] < nums[suffixMinIdx]) {
                suffixMinIdx = i;
            }
        }

        return prefixMax;
    }
};