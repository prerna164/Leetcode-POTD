/*
Problem: Number of ZigZag Arrays I
Link: Dynamic Programming State-Transition Matrix

Date: 2026-06-23
Difficulty: Hard
Tags: Dynamic Programming, Prefix Sum, Math

Intuition:
The problem asks us to count valid arrays of length `n` where each element belongs to the range `[l, r]`. The sequence must change its direction at every step—meaning it can neither contain two consecutive equal elements, nor can three consecutive elements continue in a strictly increasing or decreasing trajectory.

This implies the relative heights of the array must bounce up and down alternately:
  - If $A[i-1] < A[i]$, then the next element must drop: $A[i] > A[i+1]$.
  - If $A[i-1] > A[i]$, then the next element must rise: $A[i] < A[i+1]$.

This structure perfectly lends itself to Dynamic Programming (DP). Let the total number of values we can choose from be $M = r - l + 1$. We can map the range $[l, r]$ to a zero-indexed interval $[0, M-1]$.

Let's maintain two DP tables for the transitions at position `i` ending with a value `v`:
  - `up[v]`: Number of valid prefixes of length `i` where the last step was an increase ($A[i-1] < A[i] = v$).
  - `down[v]`: Number of valid prefixes of length `i` where the last step was a decrease ($A[i-1] > A[i] = v$).

Transitions:
  - To transition to an `up` state at value $v$, the previous element $prev$ must be strictly smaller than $v$ ($prev < v$), and the previous step must have been a decrease (`down[prev]`).
    $$up_{new}[v] = \sum_{prev=0}^{v-1} down[prev]$$
  - To transition to a `down` state at value $v$, the previous element $prev$ must be strictly larger than $v$ ($prev > v$), and the previous step must have been an increase (`up[prev]`).
    $$down_{new}[v] = \sum_{prev=v+1}^{M-1} up[prev]$$

Naively calculating these transitions for every step would take $O(N \cdot M^2)$ which is too slow. However, since the transitions are simple contiguous prefix/suffix sums, we can maintain running accumulation tracking sums to optimize the transition time down to $O(N \cdot M)$.

---

Approach:

1. Range Normalization:
   * Calculate $M = r - l + 1$. If $n = 1$, the answer is $M$ (handled implicitly since $n \ge 3$).

2. Base Cases Initialization:
   * For an array of length 2, any pair of distinct elements is valid. 
   * If $prev < v$, it initializes an `up` state. For a fixed $v$, there are exactly $v$ elements smaller than it. Thus, `up[v] = v`.
   * If $prev > v$, it initializes a `down` state. For a fixed $v$, there are exactly $M - 1 - v$ elements larger than it. Thus, `down[v] = M - 1 - v`.

3. Optimized DP Transitions with Prefix Sums:
   * Loop `i` from 3 up to `n`.
   * Create prefix sums of the previous `down` array to optimize `up_new` computations.
   * Create suffix sums of the previous `up` array to optimize `down_new` computations.
   * Update the active state configurations and repeat.

4. Summation:
   * The total configurations will be the sum of all elements in both `up` and `down` tables at step `n`.

---

⏱ Time Complexity:
O(N * (r - l))

* Let $M = r - l + 1$.
* For each length step from 3 to $N$, we do a prefix sum sweep and a state update loop of size $M$.
* This takes $O(M)$ time per row transition. Across $N$ steps, total time complexity is $O(N \cdot M)$.
* Given $N \le 2000$ and $M \le 2000$, total operations are around $4 \cdot 10^6$, which executes in under 10 milliseconds.

Space Complexity:
O(r - l) Auxiliary Space

* Instead of storing a full 2D grid matrix tracking all layers, we only need the arrays of the previous state iteration.
* This keeps space restricted down to $O(M)$, well under a few kilobytes.
*/

#include <vector>
#include <numeric>
#include <iostream>

using namespace std;

class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        long long MOD = 1000000007;
        int M = r - l + 1;

        // DP tables representing states at the current length position
        // up[v] means last move went up to value v (0-indexed relative to l)
        // down[v] means last move went down to value v
        vector<long long> up(M, 0);
        vector<long long> down(M, 0);

        // Base case initialization for length = 2
        for (int v = 0; v < M; ++v) {
            up[v] = v;             // count of elements < v
            down[v] = M - 1 - v;   // count of elements > v
        }

        // DP transition iterations for length from 3 up to n
        for (int i = 3; i <= n; ++i) {
            vector<long long> next_up(M, 0);
            vector<long long> next_down(M, 0);

            // Compute prefix sums of 'down' to optimize next_up transitions
            long long running_down_sum = 0;
            for (int v = 0; v < M; ++v) {
                next_up[v] = running_down_sum;
                running_down_sum = (running_down_sum + down[v]) % MOD;
            }

            // Compute suffix sums of 'up' to optimize next_down transitions
            long long running_up_sum = 0;
            for (int v = M - 1; v >= 0; --v) {
                next_down[v] = running_up_sum;
                running_up_sum = (running_up_sum + up[v]) % MOD;
            }

            up = move(next_up);
            down = move(next_down);
        }

        // Aggregate total configurations across all ending variations
        long long total_valid_arrays = 0;
        for (int v = 0; v < M; ++v) {
            total_valid_arrays = (total_valid_arrays + up[v] + down[v]) % MOD;
        }

        return total_valid_arrays;
    }
};