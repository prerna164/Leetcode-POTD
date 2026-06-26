/*
Problem: Count Subarrays with Majority Element II
Link: Prefix Sum Inversion Counting with Fenwick Tree

Date: 2026-06-26
Difficulty: Hard
Tags: Array, Prefix Sum, Binary Indexed Tree / Fenwick Tree

Intuition:
The condition requires the target element to appear strictly more than half the time in a subarray from index i to j. 
Mathematically, this translates to:
  2 * (Count of target) - (Length of subarray) > 0

We can map the input array elements into a transformed array:
  - +1 if nums[k] == target
  - -1 if nums[k] != target

If P[x] represents the prefix sum of this transformed array up to index x, the sum of a subarray from i to j is P[j] - P[i-1]. We need:
  P[j] - P[i-1] > 0  =>  P[j] > P[i-1]

We want to find the total pairs (i-1, j) such that i-1 < j and P[i-1] < P[j]. This is an inversion-counting variation that can be handled optimally using a Binary Indexed Tree (Fenwick Tree) in O(N log N) time. Because N <= 10^5, the total number of valid subarrays can be up to N*(N+1)/2, which exceeds 32-bit integer limits. Thus, we use a `long long` data type to store the count.

---

Approach:

1. Transform & Offset Base:
   * The prefix sum can range from -N to +N. To avoid working with negative array bounds, we use an index shift `offset = n + 1`.
   * Create a Fenwick Tree of size `2 * N + 2` initialized to zero.
   * Seed the tree with the initial prefix sum of 0 at `0 + offset`.

2. Range Checking & Accumulation:
   * Walk sequentially through `nums`. Update the running prefix sum.
   * Query the Fenwick tree to see how many previous prefix sums are strictly less than `current_sum`. 
   * Add the query result to our `long long answer`.
   * Update the Fenwick tree by inserting the `current_sum`.

---

⏱ Time Complexity:
O(N log N)

* Iterating through the array takes O(N) operations.
* Each element triggers one query and one update on the Fenwick Tree, taking O(log N) time.
* Total execution time easily fits within 15 milliseconds for N = 10^5.

Space Complexity:
O(N) Auxiliary Space

* The Fenwick tree vector utilizes a memory space proportional to 2 * N + 2, maintaining a very lightweight memory footprint.
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
private:
    vector<int> bit;
    int size;

    void update(int idx, int val) {
        for (; idx < size; idx += idx & -idx) {
            bit[idx] += val;
        }
    }

    int query(int idx) {
        int sum = 0;
        for (; idx > 0; idx -= idx & -idx) {
            sum += bit[idx];
        }
        return sum;
    }

public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        // Optimize standard I/O streams for competitive programming speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = nums.size();
        size = 2 * n + 2;
        bit.assign(size, 0);

        int offset = n + 1; // Coordinate shift to map negative values safely
        int current_sum = 0;
        long long answer = 0;

        // Base case: prefix sum before any elements are evaluated is 0
        update(0 + offset, 1);

        for (int num : nums) {
            // Map target values to +1 and non-target values to -1
            if (num == target) {
                current_sum += 1;
            } else {
                current_sum -= 1;
            }

            // Accumulate counts of all valid past indices where P[i-1] < P[j]
            answer += query(current_sum - 1 + offset);

            // Add the current prefix sum state into our Fenwick Tree index
            update(current_sum + offset, 1);
        }

        return answer;
    }
};