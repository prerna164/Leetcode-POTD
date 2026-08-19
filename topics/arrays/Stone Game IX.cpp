/*
Problem: Stone Game IX
Link: LeetCode 2029 - Stone Game IX

Difficulty: Medium
Tags: Array, Math, Greedy, Game Theory

Intuition:
Only the remainder of each stone modulo 3 matters (0, 1, or 2).
Let:
- cnt[0] = number of stones with remainder 0
- cnt[1] = number of stones with remainder 1
- cnt[2] = number of stones with remainder 2

Rules & Strategy:
1. Turn 1 (Alice's Choice):
   - Alice CANNOT pick a remainder 0 stone on her first turn because 0 % 3 = 0, causing an immediate loss.
   - She must pick either a remainder 1 stone or a remainder 2 stone.

2. Impact of Remainder 0 Stones:
   - Remainder 0 stones do not change the total sum modulo 3.
   - They act as "pass cards" to swap turn parity.
   - If `cnt[0]` is EVEN: Turn order effectively remains unchanged for the key decisions.
   - If `cnt[0]` is ODD: Turn order is flipped between the players.

3. Game Analysis:
   
   Case A: `cnt[0]` is EVEN
   - Alice can choose to start with remainder 1 or remainder 2.
   - If she starts with 1: The sequence of pick remainders forced is: 1 -> 1 -> 2 -> 1 -> 2 -> 1 -> 2 ...
     For Alice to win, Bob must be forced to pick a stone that makes the sum divisible by 3, which happens if there are enough 1s and 2s such that Bob runs out of valid moves or is forced into a move divisible by 3.
   - Specifically, if `cnt[0]` is EVEN, Alice wins if `cnt[1] >= 1` AND `cnt[2] >= 1`.

   Case B: `cnt[0]` is ODD
   - The extra remainder 0 stone flips the parity.
   - Alice wins if `abs(cnt[1] - cnt[2]) > 2`.

---

Approach:

1. Count the frequencies of stone values modulo 3 into `cnt[0]`, `cnt[1]`, and `cnt[2]`.
2. Check `cnt[0] % 2`:
   * If `cnt[0]` is EVEN:
     Alice wins if both `cnt[1] > 0` and `cnt[2] > 0`.
   * If `cnt[0]` is ODD:
     Alice wins if `abs(cnt[1] - cnt[2]) > 2`.

---

⏱ Time Complexity:
O(N)

* A single pass over the `stones` array computes the remainders.
* Total Runtime: O(N) linear time.

Space Complexity:
O(1) Auxiliary Space

* Only a fixed array of size 3 is used for counting frequencies.
*/

#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        vector<int> cnt(3, 0);
        for (int stone : stones) {
            cnt[stone % 3]++;
        }

        // If cnt[0] is even, Alice wins if both remainder 1 and remainder 2 stones exist
        if (cnt[0] % 2 == 0) {
            return cnt[1] >= 1 && cnt[2] >= 1;
        }

        // If cnt[0] is odd, Alice wins if the difference between cnt[1] and cnt[2] is greater than 2
        return abs(cnt[1] - cnt[2]) > 2;
    }
};