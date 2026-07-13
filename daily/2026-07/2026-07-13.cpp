/*
Problem: Sequential Digits
Link: Window-Sliding Substring Digit Simulation

Date: 2026-07-13
Difficulty: Medium
Tags: Math, Enumeration

Intuition:
An integer has sequential digits if each digit is exactly one greater than the preceding digit (e.g., 123, 2345). 
Since the digits must strictly increment by 1, all possible sequential numbers must be substrings of the reference string `"123456789"`.

Given that the maximum value of `high` is $10^9$, the maximum length of a valid sequential number is 9 digits (the number 123456789). The total pool of possible sequential numbers is incredibly small—there are fewer than 45 sequential numbers in existence!

Instead of checking every number in the range `[low, high]` (which would cause a Time Limit Exceeded failure), we can pre-generate all possible sequential numbers using a sliding window over the master digits string, filter for those falling within the `[low, high]` boundaries, sort them, and return the result.

---

Approach:

1. Setup Master Pattern String:
   * Create a string `digits = "123456789"`.
   * Initialize a vector `result` to accumulate numbers that fall within the range.

2. Length and Window Simulation:
   * Outer loop: Iterate through possible lengths of sequential numbers, starting from the number of digits in `low` to the number of digits in `high` (bounded up to 9).
   * Inner loop: Use a sliding window of the current length to slice out substrings from the `digits` master string.
   * Convert each sliced substring to an integer. If it fits inside the range `[low, high]`, push it to the `result` vector.

3. Complete Sorting:
   * Since we grow the length incrementally and move windows from left to right, the generated sequence is naturally sorted. We can safely return the `result`.

---

⏱ Time Complexity:
O(1)

* The total number of iterations is bounded by the fixed size of the digits template string (length 9).
* The outer loops run at most 9 times, and the inner loop runs at most 9 times. This executes instantly in 0 milliseconds.

Space Complexity:
O(1) Auxiliary Space

* We only store the fixed master string and the output result array, which holds a maximum of 45 small integer components.
*/

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        // Optimize standard I/O streams for competitive programming speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        vector<int> result;
        string digits = "123456789";

        // Determine the length bounds based on constraints
        int min_len = to_string(low).length();
        int max_len = to_string(high).length();

        // Enumerate over all possible window lengths
        for (int len = min_len; len <= max_len && len <= 9; ++len) {
            for (int start = 0; start <= 9 - len; ++start) {
                string sub = digits.substr(start, len);
                int num = stoi(sub);

                // Include the generated sequential number if it fits the requested bounds
                if (num >= low && num <= high) {
                    result.push_back(num);
                }
            }
        }

        return result;
    }
};