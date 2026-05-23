/*
Problem: Check if Array Is Sorted and Rotated
Link: LeetCode 1752

Date: 2026-05-23
Difficulty: Easy
Tags: Array

🧠 Intuition:
If an array is sorted in non-decreasing order, it will always be completely non-decreasing from start to finish. However, if we rotate it, there will be exactly one "drop point" where an element is strictly greater than the next element (the pivot point where the original array wrapped around). 

Think of it as looking at the array circularly:
1. If the array is perfectly sorted and not rotated (or all elements are equal), there are 0 drops.
2. If the array is sorted and rotated exactly once, there will be exactly 1 drop.
3. If there is more than 1 drop, it means the array was never originally sorted.

Crucially, because it is a rotation, we also need to check the transition from the very last element back to the very first element (`nums[n-1] > nums[0]`). If that transition also drops, it counts toward our total drop limit. If the total number of drops across the entire circular array is 1 or 0, then the array is a valid sorted and rotated array.

--------------------------------------------------------

⚙️ Approach:
1. Initialize a counter `countDrops = 0` to track the number of times an element is greater than its subsequent element.
2. Store the size of the array in `n`.
3. Iterate through the array from `i = 0` to `n - 1`:
   - Use the modulo operator `(i + 1) % n` to cleanly check the next element. This automatically handles comparing the last element (`nums[n-1]`) with the first element (`nums[0]`) without needing a separate condition outside the loop.
   - If `nums[i] > nums[(i + 1) % n]`, increment `countDrops`.
4. After completing the loop, check if `countDrops <= 1`. 
   - If true, return `true`.
   - Otherwise, return `false`.

--------------------------------------------------------

⏱ Time Complexity:
O(n)
- We iterate through the array of size n exactly once.
- Inside the loop, all operations (modulo, indexing, comparison) run in O(1) constant time.

📦 Space Complexity:
O(1)
- The algorithm uses a fixed amount of auxiliary space (`countDrops` and `n`), regardless of the input array size.

*/

#include <vector>

using namespace std;

class Solution {
public:
    bool check(vector<int>& nums) {
        int countDrops = 0;
        int n = nums.size();
        
        for (int i = 0; i < n; i++) {
            // Compare current element with the next element circularly
            if (nums[i] > nums[(i + 1) % n]) {
                countDrops++;
            }
        }
        
        // A valid sorted and rotated array can have at most 1 drop point
        return countDrops <= 1;
    }
};