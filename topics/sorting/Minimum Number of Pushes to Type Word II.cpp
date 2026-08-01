/*
Problem: Minimum Number of Pushes to Type Word II
Link: LeetCode 3016 - Minimum Number of Pushes to Type Word II

Difficulty: Medium
Tags: Hash Table, String, Greedy, Sorting, Counting

Intuition:
We are given a string `word` containing lowercase English letters (with possible duplicates and up to length 10^5).
We want to map characters to the 8 available keypad keys (2 through 9) to minimize the total key pushes required to type `word`.

Key Observations:
1. Frequency Matters:
   - The key pushes required for a character `c` = `frequency(c) * (position_on_key)`.
   - To minimize total pushes, we should assign the most frequently occurring characters to the 1st position (1 push) across the 8 keys.
   - The next 8 most frequent characters should be assigned to the 2nd position (2 pushes), the next 8 to the 3rd position (3 pushes), and the remaining to the 4th position (4 pushes).

2. Greedy Strategy:
   - Count the frequency of each lowercase English character.
   - Sort the non-zero frequencies in descending order.
   - Assign push multipliers (1, 2, 3, or 4) to frequencies based on their rank:
     * Rank 0..7   -> 1 push
     * Rank 8..15  -> 2 pushes
     * Rank 16..23 -> 3 pushes
     * Rank 24..25 -> 4 pushes

---

Approach:

1. Count Frequencies:
   * Create a frequency vector of size 26 and populate it by iterating over `word`.

2. Sort Frequencies:
   * Sort the 26 frequencies in descending order.

3. Calculate Minimum Pushes:
   * Iterate through the sorted frequencies:
     - For index `i` (0-indexed), the push cost per occurrence is `(i / 8) + 1`.
     - Multiply the frequency by its cost and add it to `total_pushes`.

---

⏱ Time Complexity:
O(N)

* Counting frequencies takes O(N) where N = word.length.
* Sorting 26 elements takes constant O(26 log 26) = O(1) time.
* Calculating pushes takes O(26) = O(1) time.
* Total Runtime: O(N).

Space Complexity:
O(1) Auxiliary Space

* Frequency vector uses fixed size of 26 integers.
*/

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int minimumPushes(string word) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        vector<int> freq(26, 0);
        for (char c : word) {
            freq[c - 'a']++;
        }

        // Sort frequencies in descending order
        sort(freq.rbegin(), freq.rend());

        int totalPushes = 0;
        for (int i = 0; i < 26; ++i) {
            if (freq[i] == 0) break; // No more characters left
            
            int pushesPerChar = (i / 8) + 1;
            totalPushes += freq[i] * pushesPerChar;
        }

        return totalPushes;
    }
};