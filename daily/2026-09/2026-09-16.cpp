/*
Problem: Number of Sets of K Non-Overlapping Line Segments
Link: LeetCode 1621 - Number of Sets of K Non-Overlapping Line Segments

Difficulty: Medium
Tags: Math, Combinatorics, Dynamic Programming

Intuition:
We have $N$ points along a 1D line (from $x = 0$ to $x = N - 1$), forming $N - 1$ unit intervals.
We want to choose $K$ non-overlapping line segments (where sharing an endpoint is allowed).

Combinatorial Transformation:
- A line segment is defined by a start point and an end point.
- Since segments are allowed to share endpoints (e.g., segment 1 ends at $x=2$ and segment 2 starts at $x=2$), we have $K$ segments requiring $2K$ endpoints in total.
- However, when two adjacent segments share an endpoint, those 2 endpoints coincide into 1 point.
- If we instead enforce that NO segments share endpoints, we would need to insert a gap of length $\ge 0$ between adjacent segments.
- More elegantly: standard stars-and-bars / combinations approach allows us to transform sharing endpoints into choosing points from an expanded pool.

Alternatively, consider choosing $2K$ points out of $N$ points with replacement for shared endpoints.
Each shared endpoint reduces the number of distinct points used by 1.
If we add $K - 1$ "virtual" points to the $N$ points (giving $N + K - 1$ total available points), every choice of $2K$ distinct points from these $N + K - 1$ points corresponds uniquely to a valid selection of $K$ segments (allowing shared endpoints)!

Formula:
Total ways = $\binom{N + K - 1}{2K}$

---

Approach:

1. Compute Combination $\binom{N + K - 1}{2K} \pmod{10^9 + 7}$:
   * Total pool size $M = N + K - 1$.
   * Total points to pick $R = 2K$.
   * Compute $\binom{M}{R} = \frac{M!}{R! \times (M - R)!} \pmod{10^9 + 7}$ using Pascal's triangle or dynamic programming / modular inverse.
   * Since $N, K \le 1000$, $M \le 2000$ and $R \le 2000$, we can compute $\binom{M}{R}$ directly using DP in $O((N+K) \times K)$ time or $O(K)$ with modular inverse.

---

⏱ Time Complexity:
O(K) or O((N + K) * K)

* Using Pascal's Triangle DP: $O((N + K) \cdot K)$ time.
* Total Runtime: $O(N \cdot K)$ time, completing in $< 1$ ms for $N, K \le 1000$.

Space Complexity:
O(K) Auxiliary Space

* Optimizing DP table to 1D array of size $2K + 1$.
*/

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int numberOfSets(int n, int k) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        const int MOD = 1e9 + 7;
        
        // We need to compute C(n + k - 1, 2 * k)
        int M = n + k - 1;
        int R = 2 * k;

        if (R > M) return 0;

        // DP table for Combinations C(n, r) using Pascal's Identity:
        // C(n, r) = C(n - 1, r - 1) + C(n - 1, r)
        vector<long long> C(R + 1, 0);
        C[0] = 1; // C(0, 0) = 1

        for (int i = 1; i <= M; ++i) {
            for (int j = min(i, R); j > 0; --j) {
                C[j] = (C[j] + C[j - 1]) % MOD;
            }
        }

        return C[R];
    }
};