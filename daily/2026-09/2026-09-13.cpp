/*
Problem: Image Overlap
Link: LeetCode 835 - Image Overlap

Difficulty: Medium
Tags: Array, Matrix, Hash Table

Intuition:
Instead of iterating through every possible 2D shift (dx, dy) and evaluating the overlap between the two images for each shift, we can focus only on the positions where `1`s exist.

If a `1` in `img1` is located at coordinates `(r1, c1)` and a `1` in `img2` is located at coordinates `(r2, c2)`, then translating `img1` by shift vector `(r2 - r1, c2 - c1)` will align these two `1`s directly on top of each other.

By computing the displacement vector `(r2 - r1, c2 - c1)` for EVERY pair of `1`s between `img1` and `img2`, the shift vector that appears most frequently will yield the maximum number of overlapping `1`s.

---

Approach:

1. Collect Coordinates:
   * Record all `(r, c)` coordinates where `img1[r][c] == 1` into a vector `ones1`.
   * Record all `(r, c)` coordinates where `img2[r][c] == 1` into a vector `ones2`.

2. Calculate Displacements:
   * For every point `p1` in `ones1` and `p2` in `ones2`:
     - Compute row shift: `dr = p2.r - p1.r`
     - Compute column shift: `dc = p2.c - p1.c`
     - Map the 2D shift `(dr, dc)` to a unique 1D key to track counts easily (e.g., using a 2D frequency array or hash map with offset `N` since `-N < dr, dc < N`).

3. Find Maximum Frequency:
   * Keep track of the highest frequency recorded for any shift vector.

---

⏱ Time Complexity:
O(V1 * V2 + N^2)

* $V_1$ and $V_2$ are the number of `1`s in `img1` and `img2` respectively ($V_1, V_2 \le N^2$).
* In the worst case (all ones), it takes $O(N^4)$ steps.
* Given $N \le 30$, $N^4 = 810,000$ operations, which runs well within < 5ms.

Space Complexity:
O(V1 + V2 + N^2) Auxiliary Space

* Storing coordinates of `1`s takes $O(N^2)$ space.
* The frequency count array for all possible shift vectors takes $(2N + 1) \times (2N + 1) = O(N^2)$ space.
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = img1.size();
        vector<pair<int, int>> ones1;
        vector<pair<int, int>> ones2;

        // Store coordinates of all 1s in both images
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (img1[r][c] == 1) {
                    ones1.push_back({r, c});
                }
                if (img2[r][c] == 1) {
                    ones2.push_back({r, c});
                }
            }
        }

        // If either image has no 1s, maximum overlap is 0
        if (ones1.empty() || ones2.empty()) {
            return 0;
        }

        // Frequency array for shifts: range of dr and dc is [-(n-1), (n-1)]
        // Shift values by +n to map into valid non-negative array indices [0, 2n]
        vector<vector<int>> shift_counts(2 * n + 1, vector<int>(2 * n + 1, 0));
        int max_overlap = 0;

        // Compute relative translation vectors between every pair of 1s
        for (const auto& p1 : ones1) {
            for (const auto& p2 : ones2) {
                int dr = p2.first - p1.first + n;
                int dc = p2.second - p1.second + n;
                
                shift_counts[dr][dc]++;
                max_overlap = max(max_overlap, shift_counts[dr][dc]);
            }
        }

        return max_overlap;
    }
};