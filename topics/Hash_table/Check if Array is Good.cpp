/*
Problem: Check if Array is Good
Link: LeetCode 2784

Date: 2026-05-14
Difficulty: Easy
Tags: Array, Hash Table, Sorting, Counting

🧠 Intuition:

An array is considered "good" if it is a valid permutation of a predefined base array:
`base[n] = [1, 2, ..., n - 1, n, n]`

If we look closely at the properties of `base[n]`:
1. The total number of elements in the array is exactly `n + 1`.
2. The maximum value present in the array is `n`.
3. Every integer from `1` to `n - 1` appears exactly once.
4. The integer `n` appears exactly twice.

From this, a straightforward pattern emerges:
- If the given array `nums` has a length of `len`, then for it to be a valid `base[n]`, the value of `n` MUST be exactly `len - 1`.
- If the maximum value in `nums` doesn't match `len - 1`, it cannot be a valid permutation.
- Sorting the array organizes the numbers in an increasing order. After sorting, the array must look exactly like `[1, 2, 3, ..., n-1, n, n]`. 

Therefore, by simply sorting the array, we can walk through it line-by-line and check if every element perfectly matches its expected index value: `nums[i] == i + 1` for all elements except the very last one, which must also equal `n`.

--------------------------------------------------------

⚙️ Approach:

1. Let `len` be the size of the input array `nums`.
2. Calculate the expected maximum element `n = len - 1`.
3. Handle the base edge case: Since `base[1] = [1, 1]`, any valid good array must have a length of at least 2. If `len < 2`, return `false` immediately.
4. Sort the `nums` array in non-decreasing order using `std::sort`.
5. Iterate through the array using a loop from index `i = 0` to `n - 1`:
   - At each index `i`, check if `nums[i]` is equal to `i + 1`.
   - If any element deviates from this rule (e.g., a missing number, a premature duplicate, or a value out of bounds), return `false`.
6. Finally, check the last element at index `n`:
   - It must be exactly equal to `n`.
   - If `nums[n] == n`, return `true`; otherwise, return `false`.

--------------------------------------------------------

⏱ Time Complexity:

O(L * log L)

- Where `L` is the length of the `nums` array.
- Sorting the array dominates the runtime and takes O(L * log L) time.
- The single subsequent linear scan takes O(L) time.
- Since the problem constraints specify L <= 100, this approach is extremely fast and executes in negligible time.

📦 Space Complexity:

O(1) or O(log L)

- The algorithm modifies the input array `nums` in place, requiring no extra data structures like hash tables or frequency arrays.
- O(log L) space is implicitly used by `std::sort` for the call stack during the execution of its underlying introsort algorithm.

*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool isGood(vector<int>& nums) {
        int len = nums.size();
        int n = len - 1; // For base[n], the length is always n + 1, so n = len - 1
        
        // base[1] = [1, 1] is the smallest possible good array
        if (len < 2) return false;
        
        // Sort the array to align it with the sequential definition of base[n]
        sort(nums.begin(), nums.end());
        
        // Verify numbers from 1 to n - 1
        for (int i = 0; i < n; i++) {
            if (nums[i] != i + 1) {
                return false;
            }
        }
        
        // Verify the final element is also equal to n
        if (nums[n] != n) {
            return false;
        }
        
        return true;
    }
};