/*
Problem: Find the Length of the Longest Common Prefix
Link: LeetCode 3043

Date: 2026-05-21
Difficulty: Medium
Tags: Array, Hash Table, Trie, String, Math

🧠 Intuition:
The problem asks for the maximum length of a common prefix shared between any pair of integers (x, y) where x belongs to arr1 and y belongs to arr2. A naive nested loop checking all pairs would take O(N * M) time, which would trigger a Time Limit Exceeded (TLE) error given the constraints (up to 5 * 10^4 elements).

To optimize, we can use a Hash Table (specifically `std::unordered_set` in C++). 
A crucial insight is that the given numbers are positive integers bounded by 10^8. This means every number has at most 8 or 9 digits, creating a very small number of possible prefixes per element. 
For example, the number 12345 generates the prefixes: 12345, 1234, 123, 12, and 1. 

By deconstructing every integer in `arr1` into all its possible prefixes and storing them inside a hash set, we map out every prefix available from the first array in efficient O(1) average lookup time.
Then, we can evaluate each number in `arr2`. We similarly strip digits off the end of each `arr2` element to check its prefixes against our hash set. The moment a match is found, its length is calculated. Because we process the number from largest to smallest prefix (e.g., checking 4567, then 456, then 45, then 4), the first match we encounter for that specific number will be its longest matching prefix, allowing an early break optimization.

--------------------------------------------------------

⚙️ Approach:
1. Initialize an `unordered_set<int>` named `prefixes` to keep track of all valid prefixes present in `arr1`.
2. Iterate through each integer `num` in `arr1`:
   - While `num > 0`, insert the current value of `num` into the `prefixes` set.
   - Divide `num` by 10 in each step (`num /= 10`) to peel off the rightmost digit, isolating the next shorter prefix.
3. Initialize `maxLength = 0` to record the global maximum length found.
4. Iterate through each integer `num` in `arr2`:
   - While `num > 0`, check if `num` exists in the `prefixes` set using `.count(num)`.
   - If it exists, compute its digit length. Since we are dealing with integers, we can calculate it dynamically using `to_string(num).length()` or log-based math. 
   - Update `maxLength = max(maxLength, currentLength)`.
   - **Optimization:** Break out of the inner loop immediately for this number. Since we are checking from the longest prefix down to the shortest, any subsequent match for this specific number will strictly yield a smaller length.
   - If it does not exist, divide `num` by 10 (`num /= 10`) to check its next shorter prefix.
5. Return `maxLength`.

--------------------------------------------------------

⏱ Time Complexity:
O(N * log10(U) + M * log10(U))
- Let N be the length of `arr1`, M be the length of `arr2`, and U be the maximum value in the arrays (10^8).
- The number of digits for any integer is bounded by log10(U) + 1 ≈ 9 iterations.
- Inserting into and searching within `std::unordered_set` takes O(1) average time.
- Thus, the runtime scales linearly with the input sizes: O(N + M), easily executing within 20-40ms.

📦 Space Complexity:
O(N * log10(U))
- The hash set stores all unique numerical prefixes derived from `arr1`. 
- With each element contributing at most 9 prefixes, the set size is strictly bounded by 9 * N elements, which translates to O(N) auxiliary space.

*/

#include <vector>
#include <unordered_set>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        unordered_set<int> prefixes;
        
        // Step 1: Extract and store all prefixes of numbers in arr1
        for (int num : arr1) {
            while (num > 0) {
                prefixes.insert(num);
                num /= 10; // Drops the last digit to generate the next prefix
            }
        }
        
        int maxLength = 0;
        
        // Step 2: Scan numbers in arr2 and match against stored prefixes
        for (int num : arr2) {
            while (num > 0) {
                // If a matching prefix is found in our hash set
                if (prefixes.count(num)) {
                    // Determine the length of the matching numerical prefix
                    int currentLength = to_string(num).length();
                    maxLength = max(maxLength, currentLength);
                    
                    // Optimization: Smaller prefixes of the same number 
                    // cannot exceed the length of the current match.
                    break; 
                }
                num /= 10; // Drop the last digit to check the next shorter prefix
            }
        }
        
        return maxLength;
    }
};