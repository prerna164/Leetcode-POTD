/*
Problem: Earliest Finish Time for Land and Water Rides II
Link: Custom Theme Park Attraction Scheduling (Optimized)

Date: 2026-06-03
Difficulty: Medium
Tags: Array, Greedy, Optimization

Intuition:
The problem requires us to choose exactly one land ride and exactly one water ride and complete them in either order (Land -> Water or Water -> Land). The constraints are up to 5 * 10^4, meaning an O(N * M) solution is too slow and will yield Time Limit Exceeded (TLE). We need an efficient linear O(N + M) approach.

Let's break down the sequencing formula. For a specific sequence Land(i) -> Water(j):
- Land ride i finishes at: landFinish = landStartTime[i] + landDuration[i]
- Water ride j finishes at: max(landFinish, waterStartTime[j]) + waterDuration[j]

Mathematically, max(A, B) + C can be rewritten as max(A + C, B + C). Therefore, the total finish time is:
  totalFinish = max(landFinish + waterDuration[j], waterStartTime[j] + waterDuration[j])

To minimize this entire expression globally over all i and j, we can observe that:
1. The right term (waterStartTime[j] + waterDuration[j]) depends entirely on choice j.
2. The left term (landFinish + waterDuration[j]) reaches its structural minimum when 'landFinish' is as small as possible. 

Thus, for the Land -> Water sequence, the global minimum is achieved by finding the absolute minimum land finish time across all land rides, and then finding which water ride minimizes the sequence when paired with this optimal land finish time.

The exact same greedy symmetric property holds for the reverse sequence Water(j) -> Land(i). We find the absolute minimum water finish time first, then pair it with the optimal subsequent land ride. By isolating these decisions, we reduce a nested loop problem to two sequential passes.

---

Approach:

1. Process Scenario 1 (Land Ride First, then Water Ride):
   * Iterate through all land rides to find the one that finishes earliest: 
     minLandFinishTime = min(landStartTime[i] + landDuration[i]) for all i.
   * With this absolute minimum landmark fixed, iterate through all water rides to find the one that minimizes the overall combination:
     minFinishLandFirst = min(max(minLandFinishTime, waterStartTime[j]) + waterDuration[j]) for all j.

2. Process Scenario 2 (Water Ride First, then Land Ride):
   * Iterate through all water rides to find the one that finishes earliest:
     minWaterFinishTime = min(waterStartTime[j] + waterDuration[j]) for all j.
   * With this absolute minimum landmark fixed, iterate through all land rides to find the one that minimizes the overall combination:
     minFinishWaterFirst = min(max(minWaterFinishTime, landStartTime[i]) + landDuration[i]) for all i.

3. Minimize Outcomes: The absolute lowest finish time possible for the tourist is the minimum between the two best independent sequence outcomes: min(minFinishLandFirst, minFinishWaterFirst).

---

⏱ Time Complexity:
O(N + M)

* We perform a linear scan over the land array (size N) and then a linear scan over the water array (size M) for Scenario 1.
* We perform a linear scan over the water array (size M) and then a linear scan over the land array (size N) for Scenario 2.
* This results in a total of 2 * (N + M) operations. For the maximum constraint of N, M = 50,000, the loop runs roughly 200,000 times, which executes seamlessly within a few milliseconds.

Space Complexity:
O(1)

* The algorithm relies entirely on a few localized scalar integer variables to keep track of minimum values.
* No additional vectors, hash maps, or dynamic data structures are allocated, maintaining strict constant space complexity.
*/

#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>

using namespace std;

class Solution {
public:
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration, 
                           vector<int>& waterStartTime, vector<int>& waterDuration) {
        // Optimize standard standard I/O streams for competitive programming speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = landStartTime.size();
        int m = waterStartTime.size();
        
        // =============================================================
        // SCENARIO 1: Land Ride First -> Water Ride Second
        // =============================================================
        
        // Step 1: Find the land ride that finishes at the earliest possible global time
        int minLandFinishTime = INT_MAX;
        for (int i = 0; i < n; ++i) {
            minLandFinishTime = min(minLandFinishTime, landStartTime[i] + landDuration[i]);
        }
        
        // Step 2: Find the water ride that minimizes the completion time given our optimal land start
        int minFinishLandFirst = INT_MAX;
        for (int j = 0; j < m; ++j) {
            int currentFinish = max(minLandFinishTime, waterStartTime[j]) + waterDuration[j];
            minFinishLandFirst = min(minFinishLandFirst, currentFinish);
        }
        
        // =============================================================
        // SCENARIO 2: Water Ride First -> Land Ride Second
        // =============================================================
        
        // Step 1: Find the water ride that finishes at the earliest possible global time
        int minWaterFinishTime = INT_MAX;
        for (int j = 0; j < m; ++j) {
            minWaterFinishTime = min(minWaterFinishTime, waterStartTime[j] + waterDuration[j]);
        }
        
        // Step 2: Find the land ride that minimizes the completion time given our optimal water start
        int minFinishWaterFirst = INT_MAX;
        for (int i = 0; i < n; ++i) {
            int currentFinish = max(minWaterFinishTime, landStartTime[i]) + landDuration[i];
            minFinishWaterFirst = min(minFinishWaterFirst, currentFinish);
        }
        
        // The overall minimum finish time is the best path out of both sequence choices
        return min(minFinishLandFirst, minFinishWaterFirst);
    }
};