/*
Problem: Number of Unique XOR Triplet II
Link: LeetCode - Unique XOR Triplet Values

Date: 2026-07-24
Difficulty: Medium
Tags: Array, Bit Manipulation, Hash Table

Intuition:
We are given an arbitrary array `nums` of size N (where N <= 1500 and nums[i] <= 1500).
We want to find the number of unique values produced by `nums[i] ^ nums[j] ^ nums[k]` for all `0 <= i <= j <= k < N`.

Notice the constraints:
- `nums.length` <= 1500
- `nums[i]` <= 1500

A naive evaluation of all triplets takes O(N^3) time, which is ~3.37 * 10^9 operations—too slow.
However, we can reduce this by breaking down the triplet XOR into two steps:
1. First, compute all possible pairwise XOR values: `pairXOR = nums[i] ^ nums[j]` for all `i <= j`.
2. Second, combine each unique pairwise XOR value with every element in `nums`: `tripletXOR = pairXOR ^ nums[k]`.

Since `nums[i] <= 1500`, the maximum possible XOR value is bounded by the smallest power of 2 greater than 1500, which is 2048.
Thus, the total number of distinct pairwise XOR values is at most 2048!

Instead of iterating over all `N * N * N` triplets, we can:
1. Find all unique values in `nums` (removing duplicates to optimize). Let this set of unique numbers be `U`.
2. Generate all unique pairwise XOR values `P = { x ^ y | x, y in U }`.
3. Generate all unique triplet XOR values `T = { p ^ z | p in P, z in U }`.
4. Return the size of `T`.

Because `|U| <= 1500` and `|P| <= 2048`, computing `P` takes O(|U|^2) time and computing `T` takes O(|P| * |U|) time.
In the worst case, this requires at most ~2048 * 1500 ≈ 3 * 10^6 operations, which easily runs well within execution limits!

---

Approach:

1. Deduplicate Input:
   * Sort and remove duplicates from `nums` to obtain a unique list of elements `unique_nums`.

2. Generate Pairwise XORs:
   * Use a boolean array / std::vector<bool> `has_pair_xor` of size 2048 to mark all possible values formed by `unique_nums[i] ^ unique_nums[j]` for `0 <= i <= j < unique_nums.size()`.

3. Generate Triplet XORs:
   * Use another boolean array `has_triplet_xor` of size 2048.
   * Iterate over all possible pairwise XOR values `p` present in `has_pair_xor` and all elements `z` in `unique_nums`.
   * Mark `p ^ z` as true in `has_triplet_xor`.

4. Count & Return:
   * Count the total number of `true` flags in `has_triplet_xor` and return the result.

---

⏱ Time Complexity:
O(U^2 + P * U)

* Where U is the number of unique elements in `nums` (U <= min(N, 1500)) and P is the number of unique pairwise XOR values (P <= 2048).
* In the worst case, U <= 1500 and P <= 2048:
  - Deduplication: O(N log N)
  - Pairwise XOR generation: O(U^2) ≈ 1.12 * 10^6 operations.
  - Triplet XOR generation: O(P * U) ≈ 2048 * 1500 ≈ 3.07 * 10^6 operations.
* Overall Runtime: Well within execution limits (< 10 ms).

Space Complexity:
O(U + MAX_VAL) Auxiliary Space

* Vector for unique elements: O(U) space.
* Boolean arrays of fixed size 2048 (or 4096 to be safe): O(1) space.
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        // Step 1: Extract unique values from nums
        vector<int> unique_nums = nums;
        sort(unique_nums.begin(), unique_nums.end());
        unique_nums.erase(unique(unique_nums.begin(), unique_nums.end()), unique_nums.end());

        int u_size = unique_nums.size();

        // Step 2: Compute all unique pairwise XOR values
        // Maximum value of nums[i] <= 1500 < 2048, so XOR will never exceed 2047.
        const int MAX_XOR = 2048;
        vector<bool> pair_xor(MAX_XOR, false);

        for (int i = 0; i < u_size; ++i) {
            for (int j = i; j < u_size; ++j) {
                pair_xor[unique_nums[i] ^ unique_nums[j]] = true;
            }
        }

        // Collect all valid pairwise XOR values
        vector<int> valid_pairs;
        valid_pairs.reserve(MAX_XOR);
        for (int x = 0; x < MAX_XOR; ++x) {
            if (pair_xor[x]) {
                valid_pairs.push_back(x);
            }
        }

        // Step 3: Compute all unique triplet XOR values
        vector<bool> triplet_xor(MAX_XOR, false);
        for (int p : valid_pairs) {
            for (int z : unique_nums) {
                triplet_xor[p ^ z] = true;
            }
        }

        // Step 4: Count distinct triplet XOR values
        int count = 0;
        for (int x = 0; x < MAX_XOR; ++x) {
            if (triplet_xor[x]) {
                count++;
            }
        }

        return count;
    }
};