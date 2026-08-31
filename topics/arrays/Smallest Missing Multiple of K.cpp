/*
Problem: Smallest Missing Multiple of K
Link: LeetCode (Missing Multiple of K)

Difficulty: Easy
Tags: Array, Hash Table

Intuition:
We are asked to find the smallest positive multiple of `k` (i.e., `k`, `2k`, `3k`, `4k`, ...) that is NOT present in `nums`.

1. Efficient Lookup:
   - Insert all elements of `nums` into an `unordered_set<int>` (or a boolean frequency table/lookup table) for O(1) existence checks.

2. Search for the Missing Multiple:
   - Start checking multiples of `k` sequentially: `target = k`, `2k`, `3k`, ...
   - Return the first `target` that is missing from our set.

---

Approach:

1. Insert Elements into Set:
   * Populate an `unordered_set<int>` with elements from `nums`.

2. Iterate Multiples of K:
   * Initialize `target = k`.
   * While `target` exists in the set, increment `target += k`.
   * Return `target`.

---

⏱ Time Complexity:
O(N)

* Building the hash set takes O(N) time where N = nums.length.
* Checking and incrementing `target` takes at most O(N) steps since `nums` has at most N elements.
* Total Runtime: O(N) linear time.

Space Complexity:
O(N) Auxiliary Space

* Hash set requires storage for at most N elements.
*/

#include <vector>
#include <unordered_set>
#include <iostream>

using namespace std;

class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        unordered_set<int> present(nums.begin(), nums.end());

        int target = k;
        while (present.count(target)) {
            target += k;
        }

        return target;
    }
};