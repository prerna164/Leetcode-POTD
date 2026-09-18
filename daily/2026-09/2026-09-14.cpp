/*
Problem: Rectangle Overlap
Link: LeetCode 836 - Rectangle Overlap

Difficulty: Easy
Tags: Math, Geometry

Intuition:
Two axis-aligned rectangles overlap if and only if their projections onto both the X-axis and Y-axis overlap with a positive length.

For 1D intervals [A, B] and [C, D], they overlap with positive length if:
min(B, D) > max(A, C)

For rectangles:
1. X-axis overlap: min(rec1[2], rec2[2]) > max(rec1[0], rec2[0])
2. Y-axis overlap: min(rec1[3], rec2[3]) > max(rec1[1], rec2[1])

Alternatively, we can check for non-overlapping conditions:
Rectangles DO NOT overlap if one is completely to the left, right, top, or bottom of the other:
- Left: rec1[2] <= rec2[0]
- Right: rec1[0] >= rec2[2]
- Top: rec1[1] >= rec2[3]
- Bottom: rec1[3] <= rec2[1]

If none of these non-overlapping conditions are true, the rectangles overlap.

---

Approach:

1. Check if the intersection along the X-axis has positive length:
   `max(rec1[0], rec2[0]) < min(rec1[2], rec2[2])`

2. Check if the intersection along the Y-axis has positive length:
   `max(rec1[1], rec2[1]) < min(rec1[3], rec2[3])`

3. Return `true` if both conditions are satisfied, otherwise `false`.

---

⏱ Time Complexity:
O(1)

* Performs a constant number of basic comparison operations.

Space Complexity:
O(1) Auxiliary Space

* Uses no extra memory.
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        // Check if overlap exists along both X and Y axes
        bool x_overlap = max(rec1[0], rec2[0]) < min(rec1[2], rec2[2]);
        bool y_overlap = max(rec1[1], rec2[1]) < min(rec1[3], rec2[3]);

        return x_overlap && y_overlap;
    }
};