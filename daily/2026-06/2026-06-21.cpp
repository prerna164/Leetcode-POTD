/*
Problem: Maximum Ice Cream Bars
Link: Greedy Cost Optimization with Counting Sort

Date: 2026-06-21
Difficulty: Medium
Tags: Array, Greedy, Counting Sort, Sorting

Intuition:
The problem asks us to find the maximum number of ice cream bars a boy can buy with a given number of `coins`. To maximize the number of items purchased, a greedy approach is ideal: we should always choose the cheapest available ice cream bars first.

While a standard comparison-based sort takes $O(n \log n)$ time, the problem constraints explicitly require us to solve this using **Counting Sort**. 
Counting sort is perfectly suited here because the maximum value of any ice cream bar is strictly bounded ($costs[i] \le 10^5$). 

Instead of rearranging the original array, we can use a frequency array `freq` where `freq[c]` stores how many ice cream bars cost exactly `c` coins. We then iterate through this frequency array from the lowest cost ($1$) to the maximum possible cost ($10^5$), buying as many bars as we can afford at each price point.

---

Approach:

1. Frequency Array Construction:
   * Find the maximum element in `costs` (bounded by $10^5$) to size our counting frequency array efficiently.
   * Iterate through `costs` and populate `freq[c]`, tracking the occurrence count of each price.

2. Greedy Purchasing Simulation:
   * Maintain a count of purchased bars `bars_bought = 0`.
   * Loop through each possible cost `price` from $1$ up to the maximum cost.
   * If `freq[price] > 0`, calculate how many bars of this price we can afford:
     * We want to buy `freq[price]` bars, but we are limited by our remaining coins: `max_can_buy = coins / price`.
     * The actual amount we buy is `buy = min((long long)freq[price], max_can_buy)`.
   * Update our trackers:
     * `bars_bought += buy`
     * `coins -= buy * price`
   * If at any point we can no longer afford even a single bar of the current price (`coins < price`), we can terminate early.

---

⏱ Time Complexity:
O(N + M)

* Building the frequency table takes a single pass over the `costs` array, which requires $O(N)$ time.
* The greedy collection loop iterates through the price buckets up to the maximum price value $M$ ($M \le 10^5$), requiring $O(M)$ time.
* Total Time Complexity is linear $O(N + M)$, which executes incredibly fast (within 2–3 milliseconds).

Space Complexity:
O(M) Auxiliary Space

* We allocate a frequency tracking vector of size $M + 1$, where $M$ is the maximum price bounded by $10^5$. This uses a small and flat constant-bound memory footprint.
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int maxIceCream(vector<int>& costs, int coins) {
        // Optimize standard I/O streams for competitive programming speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int max_cost = 0;
        for (int c : costs) {
            max_cost = max(max_cost, c);
        }

        // Step 1: Create and populate the frequency array (Counting Sort mechanism)
        vector<int> freq(max_cost + 1, 0);
        for (int c : costs) {
            freq[c]++;
        }

        int bars_bought = 0;

        // Step 2: Greedily buy the cheapest ice cream bars first
        for (int price = 1; price <= max_cost; ++price) {
            if (freq[price] == 0) continue;

            // If we can't even afford one bar at this price, we can't buy anything cheaper
            if (coins < price) break;

            // Compute the maximum number of bars we can afford at the current price
            long long max_can_buy = coins / price;
            long long actual_buy = min((long long)freq[price], max_can_buy);

            // Deduct coins and update count
            bars_bought += actual_buy;
            coins -= actual_buy * price;
        }

        return bars_bought;
    }
};