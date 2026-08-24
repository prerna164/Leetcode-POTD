/*
Problem: Sum Game
Link: LeetCode 1925 - Sum Game

Difficulty: Medium
Tags: Math, String, Game Theory, Greedy

Intuition:
The game is played on a string `num` of even length $N$.
Let $N = \text{num.length}$.
- Left half: `num[0 ... N/2 - 1]`
- Right half: `num[N/2 ... N - 1]`

Let:
- `left_sum` = sum of known digits in left half
- `right_sum` = sum of known digits in right half
- `left_q` = count of '?' in left half
- `right_q` = count of '?' in right half

Key Observations:
1. Parity of Total '?' Count:
   - Total question marks $Q = \text{left\_q} + \text{right\_q}$.
   - If $Q$ is ODD, Alice gets the final turn. She can always adjust her last pick to ensure the left sum does NOT equal the right sum. Thus, Alice ALWAYS wins when total '?' is odd!

2. Matching Question Marks across Sides:
   - Each pair of '?' (one on the left, one on the right) can be neutralized by Bob. If Alice places digit $d$ on one side, Bob can mirror it with $d$ on the other side, contributing equal values to both sums.
   - We can subtract $\min(\text{left\_q}, \text{right\_q})$ from both `left_q` and `right_q`.
   - After this step, one side will have $0$ question marks, and the other side will have an EVEN number of question marks remaining $Q_{rem}$.

3. Game Strategy with Remaining Question Marks on One Side:
   - Suppose the left side has $Q_{rem}$ remaining '?' marks and right side has 0.
   - For Bob to win, the total sum added by the $Q_{rem}$ question marks must average $9/2 = 4.5$ per question mark over $Q_{rem}$ turns.
   - Why? Bob can force the average value of each pair of '?' to be $9$ (e.g., if Alice plays $d$, Bob plays $9 - d$).
   - Therefore, $Q_{rem}$ question marks on the left can contribute exactly $(Q_{rem} / 2) \times 9$ to the left sum under optimal play.
   - Bob wins IF AND ONLY IF:
     `left_sum - right_sum == (right_q - left_q) * 9 / 2`

---

Approach:

1. Count Known Digits and Question Marks:
   * Iterate through the first half and update `left_sum` and `left_q`.
   * Iterate through the second half and update `right_sum` and `right_q`.

2. Check Odd Question Marks:
   * If `(left_q + right_q) % 2 != 0`, return `true` (Alice wins).

3. Mathematical Equilibrium Check for Bob's Win:
   * Bob wins if `2 * (left_sum - right_sum) == (right_q - left_q) * 9`.
   * If this condition holds, return `false` (Bob wins). Otherwise, return `true` (Alice wins).

---

⏱ Time Complexity:
O(N)

* A single pass over string `num` of length `N` to compute sums and question mark counts.
* Total Runtime: O(N) linear time.

Space Complexity:
O(1) Auxiliary Space

* Uses only constant extra space for variables.
*/

#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
    bool sumGame(string num) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = num.length();
        int half = n / 2;

        int left_sum = 0, right_sum = 0;
        int left_q = 0, right_q = 0;

        for (int i = 0; i < half; ++i) {
            if (num[i] == '?') {
                left_q++;
            } else {
                left_sum += num[i] - '0';
            }
        }

        for (int i = half; i < n; ++i) {
            if (num[i] == '?') {
                right_q++;
            } else {
                right_sum += num[i] - '0';
            }
        }

        // If total '?' is odd, Alice always gets the last move and can force a win
        if ((left_q + right_q) % 2 != 0) {
            return true;
        }

        // Bob wins iff difference in sums can be balanced out by remaining '?'s averaging 4.5 each
        // 2 * (left_sum - right_sum) == (right_q - left_q) * 9
        if (2 * (left_sum - right_sum) == (right_q - left_q) * 9) {
            return false; // Bob wins
        }

        return true; // Alice wins
    }
};