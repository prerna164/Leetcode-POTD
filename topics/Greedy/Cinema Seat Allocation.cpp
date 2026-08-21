/*
Problem: Cinema Seat Allocation
Link: LeetCode 1386 - Cinema Seat Allocation

Difficulty: Medium
Tags: Array, Hash Table, Bit Manipulation, Greedy

Intuition:
Each row of 10 seats can hold at most 2 four-person groups:
- Left block: seats 2, 3, 4, 5
- Middle block: seats 4, 5, 6, 7
- Right block: seats 6, 7, 8, 9

Note that seats 1 and 10 do not belong to any valid 4-person group block.
By default, an unreserved row can accommodate 2 groups (Left + Right).
For rows with reservations, we can represent seat reservations using bitmasks:
- Set bit 0 if left block (seats 2, 3, 4, 5) has any reserved seat.
- Set bit 1 if middle block (seats 4, 5, 6, 7) has any reserved seat.
- Set bit 2 if right block (seats 6, 7, 8, 9) has any reserved seat.

---

Approach:

1. Group Reservations by Row:
   * Use an `unordered_map<int, int>` to store a bitmask of unavailable blocks for each row with reservations.
   * If a seat is reserved:
     - Seats 2, 3, 4, 5 block the Left group -> set `bit 0`.
     - Seats 4, 5, 6, 7 block the Middle group -> set `bit 1`.
     - Seats 6, 7, 8, 9 block the Right group -> set `bit 2`.

2. Calculate Max Groups per Reserved Row:
   * Iterate over rows stored in the hash map:
     - If both Left and Right blocks are clear (`!(mask & 1) && !(mask & 4)`), fit 2 groups.
     - Else if Left block is clear (`!(mask & 1)`), Middle block is clear (`!(mask & 2)`), or Right block is clear (`!(mask & 4)`), fit 1 group.

3. Calculate Total for Unreserved Rows:
   * Any completely unreserved row supports 2 groups.
   * Unreserved rows = `n - map.size()`.
   * Add `(n - map.size()) * 2` to the final count.

---

⏱ Time Complexity:
O(M)

* Where $M$ is the size of `reservedSeats`.
* Grouping reservations into the hash map takes $O(M)$ time.
* Traversing the map takes $O(U)$ time, where $U \le M$ is the number of rows with at least one reservation.
* Total Runtime: O(M) linear time.

Space Complexity:
O(M) Auxiliary Space

* Hash map stores at most $M$ unique row entries.
*/

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        // Map row number -> bitmask representing blocked blocks
        // bit 0: Left block (2,3,4,5) blocked
        // bit 1: Middle block (4,5,6,7) blocked
        // bit 2: Right block (6,7,8,9) blocked
        unordered_map<int, int> row_masks;

        for (const auto& seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];

            if (col >= 2 && col <= 5) row_masks[row] |= 1; // Left blocked
            if (col >= 4 && col <= 7) row_masks[row] |= 2; // Middle blocked
            if (col >= 6 && col <= 9) row_masks[row] |= 4; // Right blocked
        }

        int total_groups = 0;

        // Process rows that have at least one reserved seat
        for (auto& [row, mask] : row_masks) {
            // Check if both Left and Right blocks are unblocked
            if ((mask & 1) == 0 && (mask & 4) == 0) {
                total_groups += 2;
            } 
            // Check if at least one block (Left, Middle, or Right) is unblocked
            else if ((mask & 1) == 0 || (mask & 2) == 0 || (mask & 4) == 0) {
                total_groups += 1;
            }
        }

        // Unreserved rows can each seat 2 groups
        long long unreserved_rows = n - row_masks.size();
        total_groups += unreserved_rows * 2;

        return total_groups;
    }
};