/*
Problem: Array Rank Transform
Link: Coordinate Compression Rank Assignment Strategy

Date: 2026-07-12
Difficulty: Easy
Tags: Array, Hash Table, Sorting

Intuition:
The problem asks us to replace each element in an array with its corresponding rank. The rules specify that ranks start at 1, larger elements get larger ranks, identical elements share the exact same rank, and ranks must be continuous (as small as possible). This is a classic coordinate compression problem.

To solve this efficiently:
1. Make a copy of the original array and sort it in ascending order.
2. Traverse the sorted copy and map each unique element to an incrementing rank counter starting from 1. We can use a hash map (`unordered_map`) to store this element-to-rank association. By skipping duplicate elements during insertion, we guarantee that identical numbers share the same rank.
3. Walk back through the original array and replace each element with its mapped rank from the hash map.

---

Approach:

1. Copy and Sort:
   * Create a duplicate vector `sorted_arr = arr`.
   * Sort `sorted_arr` in non-decreasing order.

2. Map Rank Values:
   * Initialize a hash map `unordered_map<int, int> rank_map`.
   * Track the current rank sequence using `rank = 1`.
   * Iterate through `sorted_arr`. If an element is not present in `rank_map`, insert it with the value of `rank` and increment `rank`.

3. Transform In-Place:
   * Loop through the original `arr` vector and update each index with `rank_map[arr[i]]`.
   * Return the modified array.

---

⏱ Time Complexity:
O(N log N)

* Creating a copy and sorting the array dominates the time complexity, requiring $O(N \log N)$ operations.
* Populating the hash map and modifying the original array takes linear $O(N)$ time.
* For $N \le 10^5$, this solution executes seamlessly within 40 milliseconds.

Space Complexity:
O(N) Auxiliary Space

* The memory footprint is proportional to the size of the array due to storing the sorted duplicate array and the element-to-rank map keys.
*/

#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = arr.size();
        if (n == 0) return arr;

        // Step 1: Create a duplicate copy and sort it
        vector<int> sorted_arr = arr;
        sort(sorted_arr.begin(), sorted_arr.end());

        // Step 2: Assign ranks to unique elements sequentially
        unordered_map<int, int> rank_map;
        int rank = 1;

        for (int num : sorted_arr) {
            // Only assign a rank if the element hasn't been mapped yet
            if (rank_map.find(num) == rank_map.end()) {
                rank_map[num] = rank;
                rank++;
            }
        }

        // Step 3: Replace original values with their continuous compressed ranks
        for (int i = 0; i < n; ++i) {
            arr[i] = rank_map[arr[i]];
        }

        return arr;
    }
};