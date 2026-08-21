/*
Problem: Distribute Elements Into Two Arrays I
Link: LeetCode 3069 - Distribute Elements Into Two Arrays I

Difficulty: Easy
Tags: Array, Simulation

Intuition:
We need to simulate the distribution of elements from `nums` into two arrays `arr1` and `arr2` according to the given rules:
1. First element `nums[0]` goes to `arr1`.
2. Second element `nums[1]` goes to `arr2`.
3. For each subsequent element `nums[i]` (from index 2 to n - 1):
   - Compare the last element of `arr1` (`arr1.back()`) with the last element of `arr2` (`arr2.back()`).
   - If `arr1.back() > arr2.back()`, append `nums[i]` to `arr1`.
   - Otherwise, append `nums[i]` to `arr2`.
4. Concatenate `arr1` and `arr2` to form the final result.

---

Approach:

1. Initialize `arr1` with `nums[0]` and `arr2` with `nums[1]`.
2. Loop `i` from `2` to `nums.size() - 1`:
   * Check if `arr1.back() > arr2.back()`.
   * Push `nums[i]` to `arr1` if true; otherwise, push to `arr2`.
3. Concatenate `arr2` into `arr1` using `insert()`.
4. Return `arr1`.

---

⏱ Time Complexity:
O(N)

* A single linear scan through `nums` of length `N` takes O(N) operations.
* Concatenating the two vectors takes O(N) time.
* Overall Runtime: O(N) linear time.

Space Complexity:
O(N) Auxiliary Space

* Space allocated for `arr1` and `arr2` to store elements of `nums`.
*/

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> resultArray(vector<int>& nums) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        vector<int> arr1 = {nums[0]};
        vector<int> arr2 = {nums[1]};

        for (int i = 2; i < nums.size(); ++i) {
            if (arr1.back() > arr2.back()) {
                arr1.push_back(nums[i]);
            } else {
                arr2.push_back(nums[i]);
            }
        }

        // Concatenate arr2 into arr1
        arr1.insert(arr1.end(), arr2.begin(), arr2.end());

        return arr1;
    }
};