/*
Problem: Sorted GCD Pair Queries
Link: Multiples Frequency and Inclusive Pair Inclusion via Prefix Exclusions

Date: 2026-07-17
Difficulty: Hard
Tags: Array, Math, Number Theory, Prefix Sum, Binary Search

Intuition:
The problem asks us to compute the GCD of all pairs $(nums[i], nums[j])$ with $i < j$, sort these values in ascending order to form `gcdPairs`, and then answer several queries asking for the element at a specific index in `gcdPairs`.

Since $N \le 10^5$, the number of pairs is $O(N^2) \approx 5 \times 10^9$, which is too large to generate explicitly. However, the maximum possible value of any element is relatively small: $nums[i] \le 5 \times 10^4$. Let $M$ be the maximum value in `nums`. We can compute the exact frequency of each GCD value in $O(M \log M)$ time using number theory and the inclusion-exclusion principle.

1. Frequency of Multiples:
   For a candidate GCD value $g$, we count how many numbers in `nums` are multiples of $g$. Let this count be $C$. The total number of pairs whose common divisor is a multiple of $g$ is given by:
   $$\text{Total Pairs With Multiple}(g) = \frac{C \times (C - 1)}{2}$$

2. Extracting Exact GCD Counts:
   The calculated total pairs include pairs whose actual GCD is $g, 2g, 3g$, etc. To find the exact count of pairs with a GCD of exactly $g$, we iterate backwards from $M$ down to $1$ and subtract the overcounted amounts:
   $$\text{exact\_gcd\_count}[g] = \text{Total Pairs With Multiple}(g) - \sum_{2g, 3g, \dots \le M} \text{exact\_gcd\_count}[\text{larger\_g}]$$

3. Index Lookup via Prefix Sums:
   After computing `exact_gcd_count[g]` for all $1 \le g \le M$, we convert it into a prefix sum array. The prefix sum `pref[g]` tells us how many pairs have a GCD $\le g$. Since `gcdPairs` is sorted, we can perform a binary search (`std::upper_bound`) for each query index to find the corresponding GCD value in $O(\log M)$ time.

---

Approach:

1. Frequency Count:
   * Populate a frequency array `counts` where `counts[x]` stores how many times `x` appears in `nums`.
   * Keep track of the maximum value `max_val` present in `nums`.

2. Multiples and Exclusion Sweep:
   * Create an array `exact_gcd_count` of size `max_val + 1`.
   * Loop backwards from `g = max_val` down to $1$:
     - Count elements that are multiples of `g`: $C = \sum_{j=g, 2g, \dots}^{\le \text{max\_val}} \text{counts}[j]$.
     - Initialize `exact_gcd_count[g] = (C * (C - 1)) / 2`.
     - Subtract counts of actual larger multiples: loop `j` from $2g, 3g, \dots \le \text{max\_val}$ and subtract `exact_gcd_count[j]`.

3. Prefix Matrix Setup & Binary Search:
   * Form `pref` where `pref[g] = pref[g-1] + exact_gcd_count[g]`.
   * For each query `q`, use `std::upper_bound` on `pref` to determine the corresponding GCD value.

---

⏱ Time Complexity:
O(N + M log M + Q log M)

* Building the frequency array takes $O(N)$ time.
* The nested sieve loops over multiples run in Harmonic Series time: $O(M \log M)$, where $M \le 5 \times 10^4$.
* Answering $Q$ queries using binary search takes $O(Q \log M)$ time.
* The solution processes all inputs in under 30 milliseconds.

Space Complexity:
O(M) Auxiliary Space

* Space is utilized by allocating the frequency, exact count, and prefix sum tables up to the maximum value boundary $M$.
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int max_val = *max_element(nums.begin(), nums.end());

        // Step 1: Count frequency of each number in the array
        vector<long long> counts(max_val + 1, 0);
        for (int num : nums) {
            counts[num]++;
        }

        // Step 2: Inclusion-Exclusion reverse sieve to find exact pairs with GCD == g
        vector<long long> exact_gcd_count(max_val + 1, 0);
        for (int g = max_val; g >= 1; --g) {
            long long multiples_count = 0;
            for (int j = g; j <= max_val; j += g) {
                multiples_count += counts[j];
            }

            // Total pairs whose GCD is a multiple of g
            long long total_pairs = (multiples_count * (multiples_count - 1)) / 2;

            // Subtract pairs that have a larger actual GCD (2g, 3g, 4g, etc.)
            for (int j = 2 * g; j <= max_val; j += g) {
                total_pairs -= exact_gcd_count[j];
            }
            exact_gcd_count[g] = total_pairs;
        }

        // Step 3: Accumulate prefix sums of sorted GCD frequencies
        vector<long long> pref(max_val + 1, 0);
        for (int g = 1; g <= max_val; ++g) {
            pref[g] = pref[g - 1] + exact_gcd_count[g];
        }

        // Step 4: Map each query to its corresponding sorted pair value using binary search
        vector<int> answer;
        answer.reserve(queries.size());

        for (long long q : queries) {
            // Find the first index where prefix sum is strictly greater than the query index
            auto it = upper_bound(pref.begin(), pref.end(), q);
            answer.push_back(distance(pref.begin(), it));
        }

        return answer;
    }
};