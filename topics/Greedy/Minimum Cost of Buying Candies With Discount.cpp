/*
Problem: Minimum Cost of Buying Candies With Discount
Link: LeetCode 2144 - Minimum Cost of Buying Candies With Discount

Date: 2026-06-01
Difficulty: Easy
Tags: Array, Greedy, Sorting

Intuition:
The problem allows us to get a free candy for every two candies we purchase, provided the free candy is less than or equal in cost to the minimum of the two purchased ones. To minimize our overall expenditure, our goal should be to maximize the value of the candies we get for free.

A greedy strategy works perfectly here: if we always choose to buy the two most expensive available candies, we can claim the third most expensive available candy for free (since its cost will naturally be less than or equal to the costs of the two we just bought). By sorting the array in descending order, we can easily group the candies from most expensive to least expensive and eliminate the cost of every third candy.

---

Approach:

1. Sort Candies in Descending Order: Arrange the `cost` vector in descending order (highest price to lowest price). This allows us to sequentially process the most valuable items first.
2. Iterate and Group by Three: Loop through the sorted elements using a standard 0-indexed tracking index `i`.
   * The first item (`i = 0`) and second item (`i = 1`) are paid for.
   * The third item (`i = 2`) satisfies the rule: `cost[2] <= min(cost[0], cost[1])`. Thus, we take it for free and omit its value from the sum.
   * Repeat this logic for every subsequent block of three items (`i = 3, 4` are paid, `i = 5` is free, etc.).
3. General Rule for Accumulation: For any item at index `i`, it is free if and only if `(i + 1) % 3 == 0`. We only add `cost[i]` to our running total if it does not meet this condition.
4. Return Total: Once the entire array is scanned, return the accumulated cost. Any leftover 1 or 2 candies at the end of the list will correctly be paid for at full price because they won't reach a multiple-of-three index.

---

⏱ Time Complexity:
O(N * log(N))

* Sorting the array of N elements dominates the processing bottleneck, taking O(N * log(N)) time complexity.
* The subsequent linear scan checks each element exactly once, requiring O(N) execution time.
* Combining these stages results in an overall runtime of O(N * log(N)), which easily processes 10^2 elements well within the standard time limit.

Space Complexity:
O(1) or O(log(N))

* The algorithm performs the operations in-place on the provided vector, utilizing only a primitive scalar variable (`totalCost`) to maintain state.
* Depending on the implementation of `std::sort` in the C++ Standard Template Library, it may use O(log(N)) auxiliary stack space for quicksort variations. No extra heap memory is allocated.
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int minimumCost(vector<int>& cost) {
        // Optimize standard input/output streams for competitive execution environments
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        // Sort costs in descending order to maximize the value of free items greedily
        sort(cost.rbegin(), cost.rend());
        
        int totalCost = 0;
        int n = cost.size();
        
        // Accumulate cost, skipping every 3rd candy (index 2, 5, 8, ...)
        for (int i = 0; i < n; i++) {
            if ((i + 1) % 3 != 0) {
                totalCost += cost[i];
            }
        }
        
        return totalCost;
    }
};