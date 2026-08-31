/*
Problem: Lexicographically Smallest Array by Swapping Elements
Link: LeetCode 2948 - Make Lexicographically Smallest Array by Swapping Elements

Difficulty: Medium
Tags: Array, Union Find, Sorting, Two Pointers

Intuition:
If element A can be swapped with element B (|A - B| <= limit), and element B can be swapped 
with element C (|B - C| <= limit), then A, B, and C all belong to the same connected component. 
Within any connected component, we can rearrange the elements into any order we want.

To get the lexicographically smallest array:
1. Sort pairs of `(nums[i], i)`.
2. Group adjacent elements in the sorted array into connected components if `sorted[k] - sorted[k-1] <= limit`.
3. For each group/component:
   - Collect all values (which are already sorted).
   - Collect all original indices and sort them.
   - Place the sorted values back into the sorted original indices.

---

Approach:

1. Pair Values with Original Indices:
   * Create a vector of pairs `pair<int, int>` storing `(nums[i], i)`.
   * Sort the pairs by value.

2. Group into Connected Components:
   * Iterate through sorted pairs and split into groups whenever `sorted[k].first - sorted[k-1].first > limit`.

3. Reassign Values:
   * For each group, extract the values and indices.
   * Sort the indices in ascending order.
   * Assign `group_values[j]` to `result[group_indices[j]]`.

---

⏱ Time Complexity:
O(N log N)

* Sorting the `pairs` vector takes O(N log N) time.
* Sorting the indices of each component takes O(N log N) total across all components.
* Total Runtime: O(N log N) time.

Space Complexity:
O(N) Auxiliary Space

* Vectors for storing pairs, group values, and indices take linear space.
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = nums.size();
        vector<pair<int, int>> sorted_pairs(n);
        for (int i = 0; i < n; ++i) {
            sorted_pairs[i] = {nums[i], i};
        }

        // Sort pairs by value
        sort(sorted_pairs.begin(), sorted_pairs.end());

        vector<int> result(n);

        // Group connected components
        for (int i = 0; i < n; ) {
            int j = i + 1;
            while (j < n && sorted_pairs[j].first - sorted_pairs[j - 1].first <= limit) {
                j++;
            }

            // Group spans from index i to j - 1
            vector<int> indices;
            for (int k = i; k < j; ++k) {
                indices.push_back(sorted_pairs[k].second);
            }

            // Sort indices to place values in earliest original positions
            sort(indices.begin(), indices.end());

            for (int k = i; k < j; ++k) {
                result[indices[k - i]] = sorted_pairs[k].first;
            }

            i = j;
        }

        return result;
    }
};