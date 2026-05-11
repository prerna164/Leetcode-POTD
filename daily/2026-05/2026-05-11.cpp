/*
Problem: Separate the Digits in an Array
Link: LeetCode 2553

Date: 2024-05-24
Difficulty: Easy
Tags: Array, Simulation

🧠 Intuition:

The problem asks us to take a list of numbers and break each number down into its 
constituent digits, maintaining the order of the numbers and the digits within 
those numbers. 

For example: [13, 25] -> [1, 3, 2, 5].

The primary logic involves digit extraction. In most programming languages, 
using the modulo operator (number % 10) gives the last digit. However, this 
process extracts digits from right-to-left (3 then 1 for the number 13). 
To maintain the required order, we must either:
1. Extract digits into a temporary buffer and reverse them.
2. Convert the number to a string and iterate through its characters.

The approach below uses the mathematical extraction + reverse method, which is 
highly efficient as it avoids the overhead of string formatting.

--------------------------------------------------------

⚙️ Approach:

1. Initialize an empty result vector 'answer'.
2. For each number 'val' in the input array 'nums':
   a. Create a temporary vector 'temp' to store digits of the current number.
   b. While 'val' is greater than 0:
      - Get the last digit: digit = val % 10.
      - Store it in 'temp'.
      - Remove the last digit: val = val / 10.
   c. The digits in 'temp' are currently in reverse order. Reverse the 'temp' 
      vector to restore the original order.
   d. Append all elements of 'temp' into the 'answer' vector.
3. Return the 'answer' vector.

--------------------------------------------------------

⏱ Time Complexity:

O(N * K)

- N is the number of elements in the input array.
- K is the maximum number of digits in an integer (given constraints val <= 10^5, K is at most 6).
- Since K is small and constant, the complexity effectively scales linearly with the input size.

📦 Space Complexity:

O(N * K)

- We store all digits of all numbers in the final 'answer' vector.
- The space used is proportional to the total number of digits across all integers in the input.

*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> separateDigits(vector<int>& nums) {
        vector<int> answer;
        
        // Iterate through each number in the input list
        for (int val : nums) {
            vector<int> temp;
            
            // Extract digits from the current number (right-to-left)
            while (val > 0) {
                temp.push_back(val % 10);
                val /= 10;
            }
            
            // Reverse the temporary vector to get digits in correct left-to-right order
            reverse(temp.begin(), temp.end());
            
            // Append the separated digits to the final result
            for (int digit : temp) {
                answer.push_back(digit);
            }
        }
        
        return answer;
    }
};