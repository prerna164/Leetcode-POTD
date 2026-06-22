/*
Problem: Maximum Number of Balloons
Link: Target Frequency Character Matching

Date: 2026-06-22
Difficulty: Easy
Tags: Hash Table, String, Counting

Intuition:
The problem asks us to determine how many times the word "balloon" can be formed using the characters from a given string `text`. Each character can be used at most once.

Let's examine the exact character requirements to build a single instance of the word "balloon":
  - 'b': 1 instance
  - 'a': 1 instance
  - 'l': 2 instances
  - 'o': 2 instances
  - 'n': 1 instance

This implies that the total number of "balloon" instances we can construct is limited by the scarcest resource among these five unique letters. To find the maximum count, we can calculate the frequency of each of these characters in the input text. Since 'l' and 'o' appear twice per word, their available counts must be divided by 2 (using integer division). 

The final answer will be the minimum of these adjusted frequencies:
  $$\min(\text{count}['b'], \text{count}['a'], \frac{\text{count}['l']}{2}, \frac{\text{count}['o']}{2}, \text{count}['n'])$$

---

Approach:

1. Frequency Map Initialization:
   * Create an array or frequency tracker for the 5 relevant characters. A simple 26-element integer array or dedicated variables can be used.

2. Populate Frequency Distribution:
   * Iterate through the string `text` character by character. Increment the frequency count if the character belongs to the set {'b', 'a', 'l', 'o', 'n'}.

3. Bottleneck Analysis:
   * Normalize the frequency pools: divide the counts of 'l' and 'o' by 2.
   * Compute and return the minimum value among all 5 normalized counts.

---

⏱ Time Complexity:
O(N)

* We scan the string `text` exactly once to count character frequencies, taking $O(N)$ time where $N$ is the length of the string.
* Finding the minimum of 5 fixed tracking elements takes $O(1)$ constant time.
* The overall process scales linearly, running in under 1 millisecond.

Space Complexity:
O(1) Auxiliary Space

* The frequency storage space relies on a fixed set of tracking counters (or a small 26-sized array), which uses a strictly constant amount of memory regardless of the size of `text`.
*/

#include <string>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxNumberOfBalloons(string text) {
        // Optimize standard I/O streams for competitive programming speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        // Vector to store frequencies of the 26 English lowercase letters
        vector<int> freq(26, 0);
        for (char c : text) {
            freq[c - 'a']++;
        }

        // Extract frequencies of the specific constituent characters
        int count_b = freq['b' - 'a'];
        int count_a = freq['a' - 'a'];
        int count_l = freq['l' - 'a'] / 2; // Requires 2 'l's per word
        int count_o = freq['o' - 'a'] / 2; // Requires 2 'o's per word
        int count_n = freq['n' - 'a'];

        // The maximum number of complete words is limited by the bottleneck character
        return min({count_b, count_a, count_l, count_o, count_n});
    }
};