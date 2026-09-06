/*
Problem: Construct Uniform Parity Array Construction II
Link: LeetCode (Uniform Array)

Difficulty: Medium
Tags: Array, Math, Greedy, Sorting

Intuition:
We need to form `nums2` such that all its elements are either ALL EVEN or ALL ODD.
For each element `nums1[i]`, we can either:
1. Keep `nums1[i]`.
2. Subtract `nums1[j]` such that `nums1[i] - nums1[j] >= 1` (meaning `nums1[j] < nums1[i]`).

To subtract a smaller element `nums1[j]` from `nums1[i]`, we must have a valid `nums1[j] < nums1[i]`.

Let `min_val` be the minimum element in `nums1`:
- Since `min_val` has no smaller element in `nums1`, it CANNOT be changed by subtraction.
- Therefore, `nums2[min_index]` MUST equal `min_val`.
- This fixes the required parity of ALL elements in `nums2` to match the parity of `min_val`.

Parity Rules:
- If `min_val` is EVEN:
  - Required Target Parity: ALL EVEN.
  - An even element remains EVEN by default.
  - An odd element `nums1[i]` needs to become EVEN. To do so, we must subtract an ODD element `nums1[j] < nums1[i]` (since Odd - Odd = Even).
  - So, every odd element must have a strictly smaller odd element in `nums1`.
  - The smallest odd element in `nums1` would have no smaller odd element to subtract! Thus, if any odd elements exist, it is IMPOSSIBLE to make them all even.
  - Therefore, if `min_val` is EVEN, ALL elements in `nums1` must be EVEN.

- If `min_val` is ODD:
  - Required Target Parity: ALL ODD.
  - An odd element remains ODD by default.
  - An even element `nums1[i]` needs to become ODD. To do so, we must subtract an ODD element `nums1[j] < nums1[i]` (since Even - Odd = Odd).
  - Since `min_val` is the absolute minimum AND is ODD, `min_val` is smaller than EVERY even element in `nums1`.
  - Thus, every even element `nums1[i]` can simply subtract `min_val` to become odd!
  - Therefore, if `min_val` is ODD, it is ALWAYS POSSIBLE to construct an ALL ODD array.

Summary:
- If `min_val` is ODD $\implies$ Return `true`.
- If `min_val` is EVEN $\implies$ Return `true` if ALL elements in `nums1` are EVEN; otherwise return `false`.

---

Approach:

1. Find Minimum Element:
   * Iterate through `nums1` to find `min_val`.

2. Parity Check:
   * If `min_val % 2 != 0`, return `true`.
   * If `min_val % 2 == 0`, check if any element in `nums1` is odd. If an odd element is found, return `false`. Otherwise, return `true`.

---

⏱ Time Complexity:
O(N)

* A single pass over `nums1` finds the minimum element and validates the parity condition.
* Total Runtime: O(N) linear time.

Space Complexity:
O(1) Auxiliary Space

* Uses only constant extra space.
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int min_val = *min_element(nums1.begin(), nums1.end());

        // If min_val is odd, every even element can subtract min_val to become odd (Even - Odd = Odd).
        if (min_val % 2 != 0) {
            return true;
        }

        // If min_val is even, no element can change the parity of the smallest odd element.
        // Therefore, ALL elements in nums1 must already be even.
        for (int x : nums1) {
            if (x % 2 != 0) {
                return false;
            }
        }

        return true;
    }
};