/*
Problem: Mirror Distance of an Integer
Date: 2026-04-18
Difficulty: Easy
Tags: Math, Simulation

🧠 Intuition:
The "Mirror Distance" is simply the gap between a number and its reversed 
counterpart on the number line. To calculate this, we need to perform two 
primary steps:
1. Generate the reverse of the input number 'n'.
2. Find the absolute difference between 'n' and its reverse.

The core challenge is the digit reversal logic, specifically handling cases 
like 120 -> 021 (which becomes 21).

⚙️ Approach:
1. Preserve the Original: Since we will be modifying 'n' to extract its 
   digits, we first store its value in a variable `original`.

2. Reverse Logic: 
   - Initialize `rev_n` to 0.
   - Use a `while` loop that continues as long as `n > 0`.
   - In each iteration, take the last digit of `n` using the modulo operator 
     (`n % 10`).
   - "Shift" the existing `rev_n` to the left by multiplying it by 10, then 
     add the extracted digit.
   - Remove the last digit from `n` using integer division (`n /= 10`).

3. Final Calculation:
   - Subtract `rev_n` from `original`.
   - Use the `abs()` function to ensure the result is positive, regardless of 
     which number was larger.

⏱ Time Complexity:
O(log10(N)) — The number of iterations in the while loop is equal to the 
number of digits in 'n'. For a number up to 10^9, this is at most 10 iterations.

📦 Space Complexity:
O(1) — We only use a constant amount of extra space (a few integer variables) 
regardless of the input size.

*/

#include <iostream>
#include <cmath>

class Solution {
public:
    /**
     * Calculates the absolute difference between n and its digit-reversal.
     */
    int mirrorDistance(int n) {
        int original = n; // Store original value to calculate difference later
        long long rev_n = 0; // Use long long to prevent overflow during reversal
        
        // Step 1: Reverse the digits
        while (n > 0) {
            // Extract last digit and append to reversed number
            rev_n = rev_n * 10 + (n % 10);
            // Move to the next digit
            n /= 10;
        }
        
        // Step 2: Calculate absolute difference
        // We cast back to int as the result is guaranteed to fit in int constraints
        return std::abs(original - (int)rev_n);
    }
};