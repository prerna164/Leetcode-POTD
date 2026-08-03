/*
Problem: Stone Game
Link: LeetCode 877 - Stone Game

Difficulty: Medium
Tags: Array, Math, Dynamic Programming, Game Theory

Intuition:
We are given an array `piles` representing piles of stones. 
Two players (Alice and Bob) take turns picking piles from either the start or the end of the row. 
Alice always goes first.

Key Observations & Mathematical Guarantee:
1. `piles.length` is always EVEN.
2. The total sum of all stones across all piles is ODD (no ties possible).

Because the total number of piles is even, the piles can be split into two parity groups based on 0-indexed positions:
  - Even-indexed piles: piles[0], piles[2], piles[4], ...
  - Odd-indexed piles:  piles[1], piles[3], piles[5], ...

Alice can ALWAYS guarantee picking either ALL even-indexed piles or ALL odd-indexed piles:
- On turn 1, Alice can pick `piles[0]` (even) or `piles[n-1]` (odd, since n is even, n-1 is odd).
- If Alice picks `piles[0]`, the remaining board starts at `1` and ends at `n-1` (both odd indices). 
  Whatever Bob picks, he is forced to expose an even-indexed pile for Alice's next turn.
- Thus, Alice can calculate `sum(even_piles)` and `sum(odd_piles)`. Since the total sum is odd, one sum MUST be strictly greater than the other. 
- Alice simply chooses the strategy corresponding to the larger sum on her very first turn and remains guaranteed to win!

Therefore, Alice ALWAYS wins under optimal play.

---

Approach:

1. Return `true` directly in O(1) time and space.

(Alternatively, standard 2D/1D Dynamic Programming can be used for general cases, but for this specific problem formulation, `return true` is completely rigorous and optimal.)

---

⏱ Time Complexity:
O(1)

* The solution returns `true` in constant time.

Space Complexity:
O(1) Auxiliary Space

* Requires zero extra memory allocation.
*/

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        // Alice can always choose to take all even-indexed piles or all odd-indexed piles.
        // Since the total sum is odd, one group is strictly greater than the other.
        // Therefore, Alice can always force a win.
        return true;
    }
};