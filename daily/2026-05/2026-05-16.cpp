/*
Problem: Find Minimum in Rotated Sorted Array II
Link: LeetCode 154

Date: 2026-05-16
Difficulty: Hard
Tags: Array, Binary Search

🧠 Intuition:

This problem expands on finding the minimum in a rotated sorted array by introducing
duplicates. The array can still be visualized as two sorted sub-parts:
[2, 2, 2, 0, 1, 2, 2]
Part 1: [2, 2, 2] | Part 2: [0, 1, 2, 2]

Like the basic version, we compare `nums[mid]` with `nums[right]` to identify which
half contains the minimum. However, duplicates introduce a tricky third case:

1. If nums[mid] > nums[right]: The minimum is strictly to the right of mid.
2. If nums[mid] < nums[right]: The minimum is at mid or to its left.
3. If nums[mid] == nums[right]: We cannot determine whether the minimum lies in the
left half or the right half. For instance:
* [2, 2, 0, 2, 2] -> mid is 0, right is 2 (min is to the left)
* [2, 2, 2, 0, 2] -> mid is 2, right is 2 (min is to the right)



To handle this ambiguity safely without skipping the minimum element, we simply
decrement the right pointer (`right--`). Since `nums[mid] == nums[right]`, removing
`nums[right]` from the search space doesn't lose the minimum because `nums[mid]` is
still tracking that value.

---

⚙️ Approach:

1. Initialize two pointers: `left = 0` and `right = n - 1`.
2. While `left < right`:
* Calculate `mid = left + (right - left) / 2`.
* Case A: `nums[mid] > nums[right]`
* The inflection point is strictly in the right subarray.
* Move `left = mid + 1`.


* Case B: `nums[mid] < nums[right]`
* The right side is cleanly sorted. The minimum is either `mid` or to its left.
* Move `right = mid`.


* Case C: `nums[mid] == nums[right]`
* Trapped in an ambiguous duplicate sequence.
* Safely shrink the window from the right by executing `right--`.




3. When `left == right`, the pointers have converged onto the minimum element.
4. Return `nums[left]`.

---

⏱ Time Complexity:

* Average Case: O(log n)
When elements are distinct or duplicates are rare, the search space is halved
at each step.
* Worst Case: O(n)
If the array contains entirely identical elements (e.g., [2, 2, 2, 2, 2]), Case C
triggers continuously, shifting the right pointer by only 1 element per iteration
and degrading the binary search into a linear scan.

📦 Space Complexity:

O(1)

* The algorithm operates entirely in-place, tracking only a few index pointer variables
(`left`, `right`, `mid`).

*/

#include 

using namespace std;

class Solution {
public:
int findMin(vector& nums) {
int left = 0;
int right = nums.size() - 1;

```
    while (left < right) {
        int mid = left + (right - left) / 2;

        // Case A: The pivot/minimum must be in the right half
        if (nums[mid] > nums[right]) {
            left = mid + 1;
        } 
        // Case B: The right side is sorted, minimum is mid or to its left
        else if (nums[mid] < nums[right]) {
            right = mid;
        } 
        // Case C: Ambiguity due to duplicates. Shrink search space linearly.
        else {
            right--;
        }
    }

    // Converged position holds the minimum value
    return nums[left];
}

```

};