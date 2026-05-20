/*
Problem: Find the Prefix Common Array of Two Arrays
Link: LeetCode 2657

Date: 2026-05-20
Difficulty: Medium
Tags: Array, Hash Table, Frequency Counting

🧠 Intuition:
We want to find how many numbers have appeared in both arrays `A` and `B` up to each index `i`. 
Since `A` and `B` are permutations of numbers from 1 to `n`, every number appears exactly once in `A` 
and exactly once in `B`.

Instead of checking all previous elements using nested loops, we can use a frequency tracker. 
As we scan through the arrays, we keep tabs on how many times each number has been seen. 
At any index `i`, we look at two numbers: `A[i]` and `B[i]`.
1. We increment the frequency count for `A[i]`. If it hits 2, it means both arrays have contributed this number.
2. We increment the frequency count for `B[i]`. If it hits 2, it also means both arrays have contributed this number.

By keeping a running counter of how many elements have reached a frequency of 2, we can build our 
result array `C` dynamically in a single pass.

--------------------------------------------------------

⚙️ Approach:
1. Initialize an integer `n` representing the size of the arrays.
2. Create the output vector `C` of size `n` and a frequency tracking vector `freq` of size `n + 1` (initialized to 0).
3. Track a running total `commonCount = 0` to count elements that have appeared in both permutations.
4. Iterate from `i = 0` to `n - 1`:
   - Increment `freq[A[i]]`. If `freq[A[i]] == 2`, increment `commonCount`.
   - Increment `freq[B[i]]`. If `freq[B[i]] == 2`, increment `commonCount`.
   - Record the current state by setting `C[i] = commonCount`.
5. Return the finalized array `C`.

--------------------------------------------------------

⏱ Time Complexity:
O(n)
- We iterate through the permutations exactly once.
- Inside the loop, all operations (indexing, incrementing, and comparisons) run in O(1) constant time.

📦 Space Complexity:
O(n)
- The frequency array `freq` scales up to size n + 1, requiring linear auxiliary space.
- The output array `C` requires O(n) space to return the final answer.

*/

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        int n = A.size();
        vector<int> C(n, 0);
        vector<int> freq(n + 1, 0); // Elements are 1-indexed up to n
        
        int commonCount = 0;
        
        for (int i = 0; i < n; i++) {
            // Process the current element from array A
            freq[A[i]]++;
            if (freq[A[i]] == 2) {
                commonCount++;
            }
            
            // Process the current element from array B
            freq[B[i]]++;
            if (freq[B[i]] == 2) {
                commonCount++;
            }
            
            // Assign the running count to the prefix common array
            C[i] = commonCount;
        }
        
        return C;
    }
};