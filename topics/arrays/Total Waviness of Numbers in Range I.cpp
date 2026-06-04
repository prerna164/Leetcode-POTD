/*
Problem: Total Waviness of Numbers in Range I
Link: https://leetcode.com/problems/total-waviness-of-numbers-in-range-i/description/?envType=daily-question&envId=2026-06-04

Date: 2026-06-04
Difficulty: Easy/Medium
Tags: Array, Simulation, Digit Manipulation, Enumeration

Intuition:
The problem asks us to find the total 'waviness' of all integers in the given range [num1, num2]. 
Waviness is a localized property of a number's digits: a digit qualifies as a peak if it is strictly greater than its adjacent digits, and a valley if it is strictly less than its adjacent digits. By definition, a number must have at least 3 digits to contain any peaks or valleys, because the boundary digits (first and last) cannot be peaks or valleys.

Given the upper constraint where num2 <= 10^5, the total number of elements we need to process is at most 100,000. For each number, converting it into its structural digits or processing them sequentially takes a very small number of operations (since any number <= 10^5 has at most 6 digits). Therefore, a direct simulation that iterates through each number in the range, extracts its digits, and counts its peaks/valleys will comfortably pass within the execution limit without requiring complex digit dynamic programming.

---

Approach:

1. Initialization: Create a tracking variable `sumWaviness` initialized to 0 to keep track of the cumulative waviness score of all numbers.
2. Range Iteration: Loop through each integer `i` from `num1` to `num2` inclusive.
3. Helper Function for Single Number: For each number `i`:
   * If `i < 100`, it has fewer than 3 digits, so its waviness is automatically 0. Skip to the next number.
   * Otherwise, extract the digits of `i`. This can be done by taking `i % 10` repeatedly and storing them in an array/vector, then reversing it so they sit in their normal positional order (left to right).
   * Loop through the extracted digits from index `1` to `digits.size() - 2`.
   * For each digit at position `k`, check if it forms a peak (`digits[k] > digits[k-1] && digits[k] > digits[k+1]`) or a valley (`digits[k] < digits[k-1] && digits[k] < digits[k+1]`). If either condition is true, increment the local waviness counter.
4. Accumulate Results: Add the waviness of the current number to `sumWaviness`.
5. Return Result: Once the loop completes across the entire range, return `sumWaviness`.

---

⏱ Time Complexity:
O((num2 - num1 + 1) * D)

* We iterate through the range of numbers, which has a maximum span of N = 10^5 numbers.
* For each number, digit extraction and peak/valley checks take time proportional to the number of digits D. Since the maximum value is 100,000, D is at most 6.
* Total operations are roughly bounded by 10^5 * 6 = 600,000 operations, which runs well within 2–3 milliseconds in C++.

Space Complexity:
O(D)

* For each number, we use a small vector to temporarily store its digits. The size of this vector never exceeds 6 elements.
* No additional structural memory allocations are made, yielding effectively constant O(1) auxiliary space overall.
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
private:
    // Helper function to calculate the waviness of a single number
    int getWaviness(int num) {
        if (num < 100) return 0;
        
        // Extract digits
        vector<int> digits;
        while (num > 0) {
            digits.push_back(num % 10);
            num /= 10;
        }
        // Reverse to align digits from left to right
        reverse(digits.begin(), digits.end());
        
        int waviness = 0;
        int len = digits.size();
        
        // First and last digits cannot be peaks or valleys
        for (int k = 1; k < len - 1; ++k) {
            // Check for Peak
            if (digits[k] > digits[k - 1] && digits[k] > digits[k + 1]) {
                waviness++;
            }
            // Check for Valley
            else if (digits[k] < digits[k - 1] && digits[k] < digits[k + 1]) {
                waviness++;
            }
        }
        
        return waviness;
    }

public:
    int totalWaviness(int num1, int num2) {
        // Optimize standard I/O operations for performance
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        
        int sumWaviness = 0;
        
        // Iterate through all numbers in the inclusive range
        for (int i = num1; i <= num2; ++i) {
            sumWaviness += getWaviness(i);
        }
        
        return sumWaviness;
    }
};