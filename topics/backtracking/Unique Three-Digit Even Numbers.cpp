/*
Problem: Unique Three-Digit Even Numbers
Difficulty: Easy
Tags: Array, Hash Table, Enumeration, Backtracking

Intuition:
Instead of generating all possible 3-digit permutations from the input array (which can produce duplicates), 
it is far simpler and cleaner to iterate through all possible 3-digit even numbers in the range [100, 998] 
and check if each number can be formed using the frequency of available digits.

A valid 3-digit even number must satisfy:
1. It is between 100 and 998 (no leading zeros, exactly 3 digits).
2. It ends with an even digit (0, 2, 4, 6, 8).
3. The frequency of each digit used in the candidate number must not exceed the frequency of that digit in `digits`.

---

Approach:

1. Count Digit Frequencies:
   * Build a frequency array `freq` of size 10 to count occurrences of each digit in `digits`.

2. Iterate Candidate Numbers:
   * Loop through numbers `num` from `100` to `998` with a step size of `2` (even numbers only).
   * For each candidate `num`, break it into its individual digits:
     - `d1 = num / 100` (hundreds place)
     - `d2 = (num / 10) % 10` (tens place)
     - `d3 = num % 10` (units place)
   * Count required frequencies for `d1`, `d2`, and `d3`.

3. Validate Candidate:
   * Check if the required digit counts are available in `freq`.
   * If available, increment the `valid_count` result.

---

⏱ Time Complexity:
O(N)

* Building the frequency array takes O(N) time where N = `digits.size()`.
* Checking candidates from 100 to 998 takes O(450) constant operations.
* Total Runtime: O(N) linear time.

Space Complexity:
O(1) Auxiliary Space

* Uses fixed-size arrays of length 10 for digit frequency counting.
*/

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        vector<int> freq(10, 0);
        for (int d : digits) {
            freq[d]++;
        }

        int valid_count = 0;

        // Iterate through all 3-digit even numbers
        for (int num = 100; num <= 998; num += 2) {
            int d1 = num / 100;
            int d2 = (num / 10) % 10;
            int d3 = num % 10;

            vector<int> req(10, 0);
            req[d1]++;
            req[d2]++;
            req[d3]++;

            bool possible = true;
            for (int i = 0; i < 10; ++i) {
                if (req[i] > freq[i]) {
                    possible = false;
                    break;
                }
            }

            if (possible) {
                valid_count++;
            }
        }

        return valid_count;
    }
};