/*
Problem: Asteroids Destroyed
Link: LeetCode 2126 - Asteroids Destroyed

Date: 2026-05-31
Difficulty: Medium
Tags: Array, Greedy, Sorting

Intuition:
The problem allows us to destroy asteroids in any arbitrary order. To maximize our planet's mass as quickly as possible and ensure we can handle heavier obstacles down the road, a greedy approach is mathematically optimal. 

If we always target the smallest available asteroid that our planet can currently destroy, we safely accumulate its mass. If the planet's mass ever falls short of even the smallest remaining asteroid, it is impossible to progress further, and we must return false. Sorting the asteroids array in non-decreasing order allows us to naturally implement this greedy strategy.

---

Approach:

1. Dynamic Data Range Considerations: The planet's initial mass is at most 10^5, and there are up to 10^5 asteroids, each weighing up to 10^5. The cumulative mass can reach 10^5 + (10^5 * 10^5) = 10^10. This value exceeds the maximum limit of a standard 32-bit signed integer (`INT_MAX` ≈ 2 * 10^9). To prevent arithmetic overflow during summation, we must track the planet's running mass using a 64-bit integer (`long long`).
2. Sort the Asteroids: Sort the `asteroids` vector in ascending order.
3. Linear Verification: Iterate sequentially through the sorted array:
   * If the current planet mass is greater than or equal to the asteroid's mass, add the asteroid's weight to our planet's total mass.
   * If the planet's mass is strictly smaller than the current asteroid, it cannot destroy this or any subsequent (larger) asteroid. Return `false` immediately.
4. If the loop completes successfully, all asteroids have been destroyed. Return `true`.

---

⏱ Time Complexity:
O(N * log(N))

* Sorting the array of N elements dominates the processing bottleneck, taking O(N * log(N)) time complexity.
* The subsequent linear scan checks each element exactly once, requiring O(N) execution time.
* Combining these stages results in an overall runtime of O(N * log(N)), which easily processes 10^5 elements well within the standard time limit.

Space Complexity:
O(1) or O(log(N))

* The algorithm performs the operations in-place on the provided vector, utilizing only a primitive scalar variable (`currentMass`) to maintain state.
* Depending on the implementation of `std::sort` in the C++ Standard Template Library, it may use O(log(N)) auxiliary stack space for quicksort variations. No extra heap memory is allocated.
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    bool asteroidsDestroyed(int mass, vector<int>& asteroids) {
        // Optimize standard input/output streams for competitive execution environments
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        // Convert the starting mass to 64-bit to safely prevent accumulation overflow
        long long currentMass = mass;

        // Sort asteroids in ascending order to satisfy the greedy requirement
        sort(asteroids.begin(), asteroids.end());

        // Process each asteroid sequentially from smallest to largest
        for (int asteroid : asteroids) {
            if (currentMass >= asteroid) {
                currentMass += asteroid; // Absorb the asteroid mass upon destruction
            } else {
                return false; // Planet is destroyed by a heavier asteroid
            }
        }

        return true; // Successfully destroyed all asteroids
    }
};