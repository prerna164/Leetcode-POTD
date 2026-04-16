/*
Problem: Closest Equal Element Queries
Date: 2026-04-16
Difficulty: Medium
Tags: Array, Hash Table, Binary Search

🧠 Intuition:

We need the shortest distance in a circular array between a query index and any other
index containing the same value.

Circular Distance: For two indices i and j in an array of size N, the shortest
distance is min(|i - j|, N - |i - j|).

To avoid a brute-force O(N^2) search for each query, we group indices of the same
value together.

In a sorted list of indices for a specific value, the "closest" element to any
given index must be one of its two immediate neighbors in that sorted list
(considering the list itself as circular).

⚙️ Approach:

Grouping: Create a Hash Map (unordered_map<int, vector<int>>) where each key is
a value from the array and the value is a sorted vector of its indices.

Binary Search: For each query index qIdx:

Retrieve the list of indices for nums[qIdx].

If the list has only 1 element, no other occurrence exists; return -1.

Use lower_bound to find the position pos of qIdx in the sorted index list.

Neighbor Check:

Identify the index to the left: (pos - 1 + m) % m.

Identify the index to the right: (pos + 1) % m.

These two neighbors represent the closest same-value elements in both
directions (including the circular wrap-around).

Distance Calculation: Calculate the circular distance for both neighbors and
store the minimum.

⏱ Time Complexity:
O(N + Q log N) — O(N) to build the index map and O(log N) for each of the Q queries
using binary search.

📦 Space Complexity:
O(N) — To store the map containing all indices of the array.

*/

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
int n = nums.size();
unordered_map<int, vector<int>> posMap;

    // Step 1: Pre-process and group indices for each unique value
    for (int i = 0; i < n; ++i) {
        posMap[nums[i]].push_back(i);
    }

    vector<int> answer;
    answer.reserve(queries.size());

    // Step 2: Process each query using the pre-processed map
    for (int qIdx : queries) {
        int targetVal = nums[qIdx];
        const vector<int>& indices = posMap[targetVal];

        // If the element appears only once, no "other" index exists
        if (indices.size() <= 1) {
            answer.push_back(-1);
            continue;
        }

        // Step 3: Use binary search to locate the query index in our grouped list
        auto it = lower_bound(indices.begin(), indices.end(), qIdx);
        int pos = distance(indices.begin(), it);
        
        int m = indices.size();
        int min_dist = n; 

        // Step 4: Check the immediate circular neighbors in the index list
        // (pos - 1) handles the element to the left, (pos + 1) to the right
        int neighborIndices[] = {(pos - 1 + m) % m, (pos + 1) % m};

        for (int i : neighborIndices) {
            int otherIdx = indices[i];
            int diff = abs(qIdx - otherIdx);
            
            // Circular distance formula: min of direct path and wrap-around path
            int circularDist = min(diff, n - diff);
            min_dist = min(min_dist, circularDist);
        }

        answer.push_back(min_dist);
    }

    return answer;
}
};