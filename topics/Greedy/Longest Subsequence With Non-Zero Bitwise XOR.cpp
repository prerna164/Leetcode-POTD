/*
Problem: Longest Subsequence With Non-Zero Bitwise XOR

Difficulty: Medium
Tags: Array, Bit Manipulation, Greedy

Intuition:
We need to find the length of the longest subsequence whose cumulative bitwise XOR is non-zero.

Let's compute the bitwise XOR sum of ALL elements in `nums` (i.e., the entire array):
1. Case 1: Total XOR sum of all elements != 0
   - If the total XOR sum is already non-zero, the entire array itself is the longest valid subsequence!
   - Therefore, the answer is `n` (where `n = nums.length`).

2. Case 2: Total XOR sum of all elements == 0
   - If the total XOR sum is 0, we can remove a single element `x` from the array to get a remaining XOR sum of `total_XOR ^ x = 0 ^ x = x`.
   - If there exists any element `x != 0` in `nums`, removing `x` leaves `n - 1` elements with a non-zero XOR sum equal to `x`.
   - Since removing 1 element gives length `n - 1` (the maximum possible length less than `n`), the answer is `n - 1`.
   - If ALL elements in `nums` are 0, then every non-empty subsequence has a XOR sum of 0, so no valid non-zero subsequence exists. In this case, return `0`.

---

Approach:

1. Calculate Total XOR Sum:
   * Iterate through `nums` and compute the XOR sum of all elements, while checking if any non-zero element exists.

2. Check Conditions:
   * If `totalXOR != 0`, return `n`.
   * Else if `totalXOR == 0` and there exists at least one non-zero element, return `n - 1`.
   * Else (all elements are 0), return `0`.

---

⏱ Time Complexity:
O(N)

* A single pass through the array `nums` of length `N` to compute the total XOR sum.
* Total Runtime: O(N) linear time.

Space Complexity:
O(1) Auxiliary Space

* Requires only a few variables (`totalXOR`, `hasNonZero`).
*/

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int totalXOR = 0;
        bool hasNonZero = false;
        int n = nums.size();

        for (int x : nums) {
            totalXOR ^= x;
            if (x != 0) {
                hasNonZero = true;
            }
        }

        // If the XOR of the whole array is non-zero, the answer is n
        if (totalXOR != 0) {
            return n;
        }

        // If total XOR is 0, but there's at least one non-zero element, 
        // removing that element gives a valid subsequence of length n - 1
        if (hasNonZero) {
            return n - 1;
        }

        // If all elements are 0, no valid subsequence exists
        return 0;
    }
};