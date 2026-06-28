/*
Problem: Maximum Element After Decrementing and Rearranging
Link: Constrained Slope Maximum Value Optimization

Date: 2026-06-28
Difficulty: Medium
Tags: Array, Greedy, Sorting

Intuition:
The problem allows us to rearrange the elements of an array in any order and decrease any element to a smaller positive integer. Our goals are:
1. The first element must be 1.
2. The absolute difference between adjacent elements must be at most 1 ($arr[i] - arr[i-1] \le 1$).
We want to maximize the largest element in the final array.

To maximize the elements as they grow from left to right, we should sort the array in ascending order first. Sorting is optimal because it arranges smaller values earlier, allowing larger values to follow them while maintaining the smallest possible jumps.

After sorting, we enforce the boundary rules greedily:
- Set the first element `arr[0] = 1`.
- For each subsequent element at index `i`, its maximum possible value is limited by the previous element: `arr[i]` can be at most `arr[i-1] + 1`. 
- If the current value `arr[i]` is already smaller than or equal to `arr[i-1] + 1`, we keep it as it is (since we can only *decrease* elements, never increase them). 
- If it is strictly larger, we cap it by decreasing it to exactly `arr[i-1] + 1` to maximize its value under the constraint.

The maximum element in the valid array will naturally be the last element after this greedy modification.

---

Approach:

1. Sorting:
   * Sort the input array `arr` in non-decreasing order.

2. Greedy Correction:
   * Explicitly set `arr[0] = 1`.
   * Loop through the array from `i = 1` to `n - 1`.
   * Enforce the adjacency bound: `arr[i] = min(arr[i], arr[i - 1] + 1)`.

3. Result Extraction:
   * The maximum value achievable will be stored at the last index `arr[n - 1]`.

---

⏱ Time Complexity:
O(N log N)

* Sorting the array dominates the time complexity, requiring $O(N \log N)$ operations.
* The subsequent greedy traversal through the array takes $O(N)$ linear time.
* For $N \le 10^5$, this solution executes within 15–20 milliseconds.

Space Complexity:
O(1) Auxiliary Space

* The adjustments are done in-place within the input vector, requiring no additional storage arrays.
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        // Optimize standard I/O streams for competitive programming speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = arr.size();
        
        // Step 1: Sort the array to process values in a non-decreasing order
        sort(arr.begin(), arr.end());

        // Step 2: Enforce the boundary rule for the first element
        arr[0] = 1;

        // Step 3: Greedily cap elements to satisfy the adjacency slope constraints
        for (int i = 1; i < n; ++i) {
            arr[i] = min(arr[i], arr[i - 1] + 1);
        }

        // The maximum possible value will naturally cascade to the end of the array
        return arr[n - 1];
    }
};