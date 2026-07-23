/*
Problem: Maximize Active Section with Trade I
Link: LeetCode - Max Active Sections After Trade

Date: 2026-07-21
Difficulty: Medium
Tags: String, Two Pointers, Greedy, Array

Intuition:
Augmenting s with '1's at both ends ensures that every block of '0's is surrounded by '1's.
When we execute a trade on a block of '1's surrounded by two '0' blocks:
1. The middle '1' block is converted to '0's, merging the two adjacent '0' blocks.
2. The merged '0' block is then completely converted into '1's.

Net active sections gain = (length of first '0' block) + (length of second '0' block).

To maximize total active sections:
- Count all existing '1's in string s.
- Find the maximum sum of lengths of any two adjacent '0' blocks in the string.
- The total answer will be: (Total '1's in s) + max(Length of two adjacent '0' blocks).

---

Approach:

1. Block Segmentation:
   * Traverse string s using a two-pointer approach to identify contiguous segments of identical characters ('0's or '1's).

2. Frequency & Gain Tracking:
   * Keep a running sum `ans` for all existing '1's.
   * Maintain `pre` as the length of the previous '0' block (initialized to negative infinity so isolated single '0' blocks don't trigger invalid gains).
   * Maintain `mx` to record the maximum value of `pre + cur` across adjacent '0' blocks.

3. Final Result:
   * Return `ans + mx`.

---

⏱ Time Complexity:
O(N)

* A single pass using two pointers processes each character in string s of length N at most twice.
* Time complexity is strictly linear, O(N).

Space Complexity:
O(1) Auxiliary Space

* Runs fully in-place with a few primitive variables, requiring O(1) constant extra memory.
*/

#include <string>
#include <algorithm>
#include <climits>
#include <iostream>

using namespace std;

class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = s.length();
        int ans = 0;       // Total count of existing '1's
        int mx = 0;        // Maximum net gain from converting two adjacent '0' blocks
        int pre = INT_MIN; // Length of previous '0' block
        
        int i = 0;
        while (i < n) {
            int j = i + 1;
            while (j < n && s[j] == s[i]) {
                j++;
            }
            
            int cur = j - i; // Length of current contiguous block
            
            if (s[i] == '1') {
                ans += cur;
            } else {
                // If we have a valid previous '0' block, consider merging it with the current '0' block
                if (pre != INT_MIN) {
                    mx = max(mx, pre + cur);
                }
                pre = cur;
            }
            
            i = j;
        }

        return ans + mx;
    }
};