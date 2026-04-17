/*
Problem: Minimum Absolute Distance Between Mirror Pairs
Difficulty: Medium
Tags: Array, Hash Table, Math, Two Pointers

🧠 Intuition:
A mirror pair (i, j) requires reverse(nums[i]) == nums[j] with i < j. 
To find the minimum distance |i - j|, we need to find the "mirror" of 
the current number that appeared most recently in the array.

Example: If we are at index j and nums[j] = 21, we are looking for a 
previous index i where reverse(nums[i]) was 21 (meaning nums[i] was 12).

By using a Hash Map, we can store the "requirement" for each number we pass.
When we see nums[i], we store reverse(nums[i]) in the map along with index i. 
If we encounter that value later at index j, we know we found a mirror pair.

⚙️ Approach:
1. Reverse Function: Create a helper to reverse digits (e.g., 120 -> 21).
2. Hash Map (unordered_map<int, int>): 
   - Key: The value we are looking for (the reverse of a previous number).
   - Value: The latest index where that requirement was generated.
3. Linear Scan: Iterate through the array once.
   - For each element nums[j], check if it exists as a key in our map.
   - If yes, calculate distance = j - map[nums[j]] and update global minimum.
   - Calculate reverse(nums[j]) and store/update it in the map with the current index j.
   - Updating the index is vital: if the same reverse value appears again, 
     the newer index will always provide a smaller distance for future pairs.

⏱ Time Complexity:
O(N * D) — We traverse the array once (N). For each number, we reverse its 
digits (D, where D is the number of digits, max 10 for 10^9). Effectively O(N).

📦 Space Complexity:
O(N) — In the worst case, we store the reverse of every element in the Hash Map.

*/

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    /**
     * Reverses the digits of an integer.
     * Handles leading zeros implicitly (120 -> 21).
     */
    int getReverse(int n) {
        long long rev = 0; 
        while (n > 0) {
            rev = rev * 10 + (n % 10);
            n /= 10;
        }
        return (int)rev;
    }

    int minMirrorPairDistance(vector<int>& nums) {
        // Map stores: [Target Mirror Value] -> [Latest Index seen]
        unordered_map<int, int> lastSeenRequirement;
        int min_dist = INT_MAX;
        bool found = false;

        for (int j = 0; j < nums.size(); ++j) {
            // Step 1: Check if current number matches a "reverse" we've seen before
            if (lastSeenRequirement.count(nums[j])) {
                min_dist = min(min_dist, j - lastSeenRequirement[nums[j]]);
                found = true;
            }

            // Step 2: Calculate the reverse of the current number
            // and store its index so future numbers can pair with it.
            int neededValue = getReverse(nums[j]);
            
            // We always update to the latest index 'j' to keep distances minimal
            lastSeenRequirement[neededValue] = j;
        }

        return found ? min_dist : -1;
    }
};