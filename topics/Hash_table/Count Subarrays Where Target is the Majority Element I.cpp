/*
Problem: Count Subarrays Where Target is the Majority Element I
Link: Prefix Sum Range Tree Constraints

Date: 2026-06-25
Difficulty: Medium
Tags: Array, Prefix Sum, Hash Table, Binary Indexed Tree / Fenwick Tree

Intuition:
The problem asks us to find the number of subarrays where the `target` element appears strictly more than half the time. Let's transform this condition mathematically. 
For a subarray from index $i$ to $j$:
  $$\text{Count of target} > \frac{\text{Total elements}}{2}$$
  $$\text{Count of target} > \frac{(j - i + 1)}{2}$$
  $$2 \times \text{Count of target} > j - i + 1$$
  $$2 \times \text{Count of target} - (j - i + 1) > 0$$

If we replace each element in the original array with:
  - $+1$ if $nums[k] == target$
  - $-1$ if $nums[k] \neq target$
Then the condition simply becomes: the sum of the transformed subarray must be strictly greater than 0!

Let $P[x]$ be the prefix sum of this transformed array up to index $x$. The sum of a subarray from $i$ to $j$ is given by $P[j] - P[i-1]$. We want:
  $$P[j] - P[i-1] > 0 \implies P[j] > P[i-1]$$

This reduces the problem to counting the number of pairs $(i-1, j)$ such that $i-1 < j$ and $P[i-1] < P[j]$. This is a classic inversion-count-like problem that can be solved efficiently using a Fenwick Tree (Binary Indexed Tree) or a simple frequency coordinate shift hash map since $N \le 1000$. Given the constraints ($N \le 1000$), an $O(N^2)$ brute-force check or an optimized $O(N \log N)$ Fenwick Tree approach can be implemented. Let's provide the highly efficient $O(N \log N)$ approach using a offset frequency strategy to keep it cleanly optimized.

---

Approach:

1. Element Transformation:
   * Maintain a running prefix sum `current_sum = 0`.
   * The minimum possible prefix sum value is $-N$ and the maximum is $+N$. We can use a frequency tracking array or hash table shifted by an offset of $N$ to avoid negative indexing.

2. Fenwick Tree / Frequency Scan:
   * Since $N \le 1000$, we can map values safely. For maximum scalability, we use a Fenwick tree or an ordered array coordinate compression. Here, we can simply map values into a Fenwick tree of size $2N + 2$.
   * Add the initial prefix state $P[-1] = 0$ (which shifts to index $N$ in our tracking structure).
   * For each element in `nums`, add $+1$ or $-1$ to `current_sum`. Query how many previous prefix sums are strictly smaller than `current_sum`, add this to our answer, and then insert the new `current_sum` into the tree.

---

⏱ Time Complexity:
O(N log N)

* Iterating through the array takes $O(N)$ steps.
* Each Fenwick tree query and update operation takes $O(\log N)$ time.
* Total Time Complexity is $O(N \log N)$, which runs in less than 1 millisecond for $N = 1000$.

Space Complexity:
O(N) Auxiliary Space

* The Fenwick tree array requires $O(2N)$ space to offset negative prefix sums safely, maintaining an extremely low and flat memory footprint.
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
    int countMajoritySubarrays(vector<int>& nums, int target) {
        // Optimize standard I/O streams for competitive programming speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = nums.size();
        size = 2 * n + 2;
        bit.assign(size, 0);

        int offset = n + 1; // Shift to completely avoid negative indices
        int current_sum = 0;
        int answer = 0;

        // Base case: prefix sum before processing any element is 0
        update(0 + offset, 1);

        for (int num : nums) {
            // Transform element to +1 or -1
            if (num == target) {
                current_sum += 1;
            } else {
                current_sum -= 1;
            }

            // Count how many previous prefix sums are strictly less than current_sum
            // query(idx) gets count of values <= idx. We want values <= current_sum - 1
            answer += query(current_sum - 1 + offset);

            // Add the new prefix sum to our tracker structure
            update(current_sum + offset, 1);
        }

        return answer;
    }
};