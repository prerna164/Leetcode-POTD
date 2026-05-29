/*
Problem: Minimum Element After Replacement With Digit Sum
Link: Custom Problem / LeetCode-style Array Transformation

Date: 2026-05-29
Difficulty: Easy
Tags: Array, Math, Simulation

Intuition:
The problem requires us to process an array of integers by transforming each element into the sum of its individual digits, and then finding the minimum value among these transformed elements.

1. Digit Isolation: To find the sum of digits of any integer, we can iteratively extract its last digit using the modulo operator (`% 10`) and reduce the number by dividing it by 10 (`/= 10`) until the number becomes zero.
2. Global Minimum Tracking: Instead of creating a brand new array to store the computed digit sums, we can find the minimum on-the-fly. By initializing a tracker variable to the maximum possible integer value (`INT_MAX`), we can compare each newly computed digit sum and instantly keep the smallest one.

---

Approach:

1. Initialize a tracker variable `minSum` to `INT_MAX`. This ensures that the very first digit sum evaluated will automatically replace it.
2. Implement a helper abstraction or direct calculation loop to process each integer element:
* For a given number, strip and sum its digits sequentially in a while loop (`while (num > 0)`).


3. Update `minSum` continuously using `std::min()` or a conditional check whenever a lower digit sum is encountered.
4. After fully iterating through the `nums` array, return the calculated `minSum`.

---

⏱ Time Complexity:
O(N * log10(M)) -> O(N)

* We iterate through each of the N elements in the array exactly once.
* For each element, the number of operations depends on its number of digits, which is bounded by O(log10(M)), where M is the maximum value of an element.
* Since the constraints specify that nums[i] <= 10^4, any number will have at most 5 digits. Thus, the inner loop runs a maximum of 5 times per number, reducing the time complexity to a highly efficient linear execution runtime of O(N).

Space Complexity:
O(1)

* The algorithm processes data in-place and relies only on primitive scalar variables (`minSum`, `currentSum`, `num`) to hold tracking states. No auxiliary data structures, dynamic vectors, or recursion stacks are utilized.
*/

#include 
#include 
#include 
#include 

using namespace std;

class Solution {
private:
// Helper function to extract and calculate the sum of digits of a given number
int getDigitSum(int n) {
int sum = 0;
while (n > 0) {
sum += n % 10; // Extract the rightmost digit
n /= 10;       // Strip the rightmost digit away
}
return sum;
}

public:
int minElement(vector& nums) {
// Optimize standard input/output streams for execution environments
ios_base::sync_with_stdio(false);
cin.tie(NULL);

```
    int minSum = INT_MAX; // Initialize to maximum upper bound
    
    // Linear scan to compute sums and track global minimum
    for (int num : nums) {
        int currentSum = getDigitSum(num);
        if (currentSum < minSum) {
            minSum = currentSum; // Maintain the lowest running value
        }
    }
    
    return minSum;
}

```

};