/*
Problem: Number of Unique XOR Triplet I
Link: LeetCode - Unique XOR Triplet Values

Date: 2026-07-24
Difficulty: Medium
Tags: Array, Bit Manipulation, Math

Intuition:
A XOR triplet is defined as nums[i] ^ nums[j] ^ nums[k] for indices i <= j <= k.
We are given an array `nums` of length `n`, which is a permutation of integers from 1 to n.

Key Observations:
1. Small Array Sizes (n < 3):
   - When n = 1: nums = [1]. The only valid triplet is (0,0,0) -> 1 ^ 1 ^ 1 = 1.
     Total unique XOR values = 1.
   - When n = 2: nums = [1, 2].
     Possible values:
     (0,0,0) -> 1 ^ 1 ^ 1 = 1
     (0,0,1) -> 1 ^ 1 ^ 2 = 2
     (0,1,1) -> 1 ^ 2 ^ 2 = 1
     (1,1,1) -> 2 ^ 2 ^ 2 = 2
     Unique XOR values are {1, 2}, total = 2.

2. General Case (n >= 3):
   - Since `nums` contains all integers from 1 to n, we have complete freedom to choose elements.
   - By picking two identical elements and one distinct element (e.g., x ^ x ^ y = y), we can obtain every single number in {1, 2, ..., n}.
   - Furthermore, using three distinct elements x ^ y ^ z, XOR properties allow us to construct every integer from 0 up to (2^b - 1), where b is the number of bits required to represent `n` (i.e., b = bit_length(n)).
   - Specifically, bitwise operations on all permutations of 1..n spanned over 3 elements span the entire sub-space of [0, 2^b - 1].
   - Therefore, for n >= 3, the number of unique XOR triplet values is exactly 2^b, where 2^b is the smallest power of 2 strictly greater than n.

---

Approach:

1. Base Cases:
   - If `n < 3`, directly return `n`.

2. Bit Length Computation:
   - Compute the bit length `b` of `n`, which is the position of the most significant set bit of `n`.
   - In C++, this can be efficiently computed using the compiler builtin `__builtin_clz(n)` as `32 - __builtin_clz(n)`.

3. Result Calculation:
   - Return `1 << b` (which equals 2^b).

---

⏱ Time Complexity:
O(1)
* Computing the bit length takes O(1) time using CPU leading-zero instruction `__builtin_clz`.

Space Complexity:
O(1) Auxiliary Space
* Uses constant additional memory.
*/

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = nums.size();
        if (n < 3) {
            return n;
        }

        // Calculate bit_length of n (number of bits needed to represent n)
        // __builtin_clz gives leading zeros; 32 - __builtin_clz(n) gives the bit length.
        int bit_length = 32 - __builtin_clz(n);

        // Result is 2^(bit_length)
        return 1 << bit_length;
    }
};