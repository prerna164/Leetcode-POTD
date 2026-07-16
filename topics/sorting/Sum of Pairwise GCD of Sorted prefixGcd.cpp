/*
Problem: Sum of Pairwise GCD of Sorted prefixGcd
Link: Prefix Max GCD Array Matching Simulation

Date: 2026-07-16
Difficulty: Medium
Tags: Array, Math, Number Theory, Two Pointers, Sorting

Intuition:
The problem is divided into a few straightforward procedural stages:

1. Prefix Maximum & GCD Array Construction:
   * We need to build a `prefixGcd` array where each element at index `i` is defined by `gcd(nums[i], max(nums[0]...nums[i]))`.
   * We can compute this efficiently by keeping a running tracker of the maximum value seen so far as we iterate through the `nums` array.

2. Sorting & Two-Pointer Pairing Simulation:
   * Sort the newly constructed `prefixGcd` array in non-decreasing order.
   * Pair elements by picking the smallest available and largest available elements simultaneously. This matches the standard outer bounds symmetric reduction using a two-pointer scheme: one pointer starting at index `0` moving rightwards (`left`), and the other pointer at index `n - 1` moving leftwards (`right`).
   * We repeat this while `left < right`. If `n` is odd, the middle single element where `left == right` is automatically bypassed and ignored as requested.

3. Summing Results:
   * For each pair `(prefixGcd[left], prefixGcd[right])`, compute their standard GCD and accumulate it into a `long long` tally variable to avoid integer overflows.

---

Approach:

1. Dynamic Array Verification Scan:
   * Traverse the `nums` array to generate the prefix maximum. For each position, compute `std::gcd(nums[i], current_max)` and write it directly into the `prefixGcd` vector slot.

2. Sorting Strategy:
   * Run `std::sort` over the constructed array.

3. Balanced Symmetric Reduction:
   * Initialize a `left = 0` pointer and a `right = n - 1` pointer. Loop while `left < right`, compute `std::gcd(prefixGcd[left], prefixGcd[right])`, add to a tracking variable `total_gcd_sum`, then increment `left` and decrement `right`.

---

⏱ Time Complexity:
O(N log N + N log(MAX_VAL))

* Constructing the `prefixGcd` array requires $O(N)$ iterations, where each step performs a GCD lookup taking logarithmic time proportional to the value size ($O(\log(\text{MAX\_VAL}))$.
* Sorting the computed sequence takes $O(N \log N)$ time.
* The symmetric pairing loops over $O(N)$ bounds with a constant number of $O(\log(\text{MAX\_VAL}))$ operations.
* For $N = 10^5$, total operations complete cleanly under 35 milliseconds.

Space Complexity:
O(N) Auxiliary Space

* Space is strictly utilized by allocating the `prefixGcd` storage array of size $N$.
*/

#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

using namespace std;

class Solution {
public:
    long long gcdSum(vector<int>& nums) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = nums.size();
        vector<long long> prefixGcd(n);
        
        int current_max = 0;

        // Step 1: Construct the prefixGcd array using a running max tracker
        for (int i = 0; i < n; ++i) {
            current_max = max(current_max, nums[i]);
            prefixGcd[i] = std::gcd((long long)nums[i], (long long)current_max);
        }

        // Step 2: Sort the array in non-decreasing order
        sort(prefixGcd.begin(), prefixGcd.end());

        long long total_gcd_sum = 0;
        int left = 0;
        int right = n - 1;

        // Step 3: Pair elements symmetrically from both endpoints using two pointers
        while (left < right) {
            total_gcd_sum += std::gcd(prefixGcd[left], prefixGcd[right]);
            left++;
            right--;
        }

        return total_gcd_sum;
    }
};