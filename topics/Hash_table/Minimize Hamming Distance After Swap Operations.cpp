/*
Problem: 1722. Minimize Hamming Distance After Swap Operations
Link: https://leetcode.com/problems/minimize-hamming-distance-after-swap-operations/

Difficulty: Medium
Tags: Array, Union Find (DSU), Hash Table

-----------------------------------------------------

🧠 Intuition:
- The core realization is that the allowed swaps define "connected components" of indices.
- If you can swap index A with B, and index B with C, you can effectively move any element at index A, B, or C to any of those three positions.
- Because we can perform any number of swaps in any order, all indices within a connected component act as a shared pool of values.
- To minimize the Hamming distance, we want to match as many elements as possible between the 'source' and 'target' within these shared pools.
- Any target element that cannot be satisfied by its corresponding pool in the source contributes 1 to the Hamming distance.

-----------------------------------------------------

⚙️ Approach:
1. Disjoint Set Union (DSU): Use DSU to group all indices that are connected through the allowedSwaps.
2. Grouping Values: Iterate through the 'source' array. For every index i, find its root parent and store the value source[i] in a frequency map (hash table) associated with that root.
3. Matching: Iterate through the 'target' array. For every index i, find its root parent. Check if the value target[i] exists in the frequency map for that root.
   - If it exists, decrement the count in the map and consider it a "match" (Hamming distance doesn't increase).
   - If it doesn't exist, we cannot place the required value at that index, contributing to the Hamming distance.
4. Calculation: The answer is (Total elements - Total matches).

-----------------------------------------------------

⏱ Time Complexity:
O(N + S * α(N)) - where N is the number of elements and S is the number of swaps. α is the inverse Ackermann function, which is nearly constant. We perform one pass to union indices and another to count matches.

📦 Space Complexity:
O(N) - We store the parent array for DSU and frequency maps that, in total, store N elements from the source array.

-----------------------------------------------------
*/

#include <vector>
#include <numeric>
#include <unordered_map>

using namespace std;

class Solution {
    // Helper function to find the representative of a set with path compression
    int find(vector<int>& parent, int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent, parent[i]);
    }

    // Helper function to unite two sets
    void unite(vector<int>& parent, int i, int j) {
        int rootI = find(parent, i);
        int rootJ = find(parent, j);
        if (rootI != rootJ) {
            parent[rootI] = rootJ;
        }
    }

public:
    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
        int n = source.size();
        vector<int> parent(n);
        iota(parent.begin(), parent.end(), 0); 

        // Step 1: Build the connected components of indices
        for (const auto& swap : allowedSwaps) {
            unite(parent, swap[0], swap[1]);
        }

        // Step 2: Map each component root to a frequency map of its available values
        unordered_map<int, unordered_map<int, int>> componentMaps;
        for (int i = 0; i < n; ++i) {
            int root = find(parent, i);
            componentMaps[root][source[i]]++;
        }

        int matches = 0;

        // Step 3: For each index in target, see if its component in source has that value
        for (int i = 0; i < n; ++i) {
            int root = find(parent, i);
            int targetVal = target[i];
            
            if (componentMaps[root].count(targetVal) && componentMaps[root][targetVal] > 0) {
                matches++;
                componentMaps[root][targetVal]--;
            }
        }

        // Hamming distance is total indices minus the ones we managed to match
        return n - matches;
    }
};