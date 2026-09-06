/*
Problem: Construct Uniform Parity Array Construction I
Link: LeetCode (Uniform Array Construction)

Difficulty: Easy
Tags: Array, Math, Parity, Greedy

Intuition:
We want to construct `nums2` from `nums1` such that every element in `nums2` has the same parity (all even or all odd).
For each index `i`, we can either:
1. Keep the original element: `nums2[i] = nums1[i]`
2. Subtract any other element `nums1[j]`: `nums2[i] = nums1[i] - nums1[j]`

Parity Rules for Subtraction (`A - B`):
- Even - Even = Even
- Odd - Odd = Even
- Even - Odd = Odd
- Odd - Even = Odd

Case 1: Target All Even Numbers
- If `nums1` already contains an ODD number, we can subtract that odd number from any other odd number to convert it to EVEN (since Odd - Odd = Even).
- If `nums1` contains NO odd numbers (all elements are even), keeping all original values naturally yields ALL EVEN elements.
- Conclusion: We can ALWAYS construct an ALL EVEN array for any `nums1`.

Case 2: Target All Odd Numbers
- To make an even number `nums1[i]` into an ODD number, we MUST subtract an ODD number `nums1[j]` from it (since Even - Odd = Odd).
- To keep an odd number `nums1[i]` ODD, we can either leave it as is or subtract an EVEN number (since Odd - Even = Odd).
- Crucially, to change any even numbers into odd numbers, AT LEAST ONE ODD NUMBER MUST EXIST in `nums1`.
- If there are NO odd numbers in `nums1`, we can NEVER create an ALL ODD array. However, we can still construct an ALL EVEN array (Case 1).

Therefore, since we only need to satisfy AT LEAST ONE uniform parity choice (All Even OR All Odd), and constructing an All Even array is always possible, the answer is ALWAYS `true`!

---

Approach:

1. Return `true` unconditionally because an all-even array can always be formed regardless of the initial parities in `nums1`.

---

⏱ Time Complexity:
O(1)

* Executes in constant $O(1)$ time.

Space Complexity:
O(1) Auxiliary Space

* Uses no additional memory.
*/

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        // We can always form an all-even array:
        // - If odd numbers exist, subtract an odd number from each odd element (Odd - Odd = Even).
        // - If no odd numbers exist, all elements are already even.
        return true;
    }
};