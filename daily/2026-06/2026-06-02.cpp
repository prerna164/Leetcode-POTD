/*
Problem: Earliest Finish Time for Land and Water Rides I
Link: Custom Theme Park Attraction Scheduling

Date: 2026-06-02
Difficulty: Medium
Tags: Array, Enumeration, Simulation, Greedy

Intuition:
The problem requires us to choose exactly one land ride and exactly one water ride and complete them in either order. Because we can choose any pair of indices (i, j) where i is a land ride and j is a water ride, and because we can ride them in any sequence (Land -> Water or Water -> Land), we need to compute the total duration required for every valid scenario. 

A ride can be started either immediately when it opens or at any time afterward. Thus, if a ride opens at 'startTime' and we arrive at time 'current', the ride can only begin at max(current, startTime). It will then finish at max(current, startTime) + duration.

Given the small constraints (number of rides N, M <= 100), checking all possible combinations of pairs and orderings takes O(N * M) operations. This easily fits into the execution window, allowing a complete, exhaustive simulation to find the absolute minimum finish time.

---

Approach:

1. Initialization: Create a tracking variable `minFinishTime` initialized to the maximum possible integer value (`INT_MAX`) to store the optimal outcome.
2. Exhaustive Enumeration: Use a nested loop to check every land ride `i` (from 0 to N-1) against every water ride `j` (from 0 to M-1).
3. Evaluate Order 1 (Land Ride First):
   * Start the land ride at its opening time: `landStartTime[i]`.
   * It finishes at `landFinish = landStartTime[i] + landDuration[i]`.
   * Move to the water ride. The earliest it can start is when it opens or when the land ride finishes, whichever is later: `waterStart = max(landFinish, waterStartTime[j])`.
   * The final completion time for this sequence is `totalFinish1 = waterStart + waterDuration[j]`.
4. Evaluate Order 2 (Water Ride First):
   * Start the water ride at its opening time: `waterStartTime[j]`.
   * It finishes at `waterFinish = waterStartTime[j] + waterDuration[j]`.
   * Move to the land ride. It can start at `landStart = max(waterFinish, landStartTime[i])`.
   * The final completion time for this sequence is `totalFinish2 = landStart + landDuration[i]`.
5. Minimize Outcomes: Update `minFinishTime` with the minimum of its current value, `totalFinish1`, and `totalFinish2`.
6. Return Result: Once all combinations are exhausted, return `minFinishTime`.

---

⏱ Time Complexity:
O(N * M)

* We iterate through each of the N land rides, and for each, we inner-loop through M water rides.
* Inside the loops, all calculations (max, addition, min) are O(1) scalar operations.
* For the maximum constraint of N, M = 100, the loop runs exactly 10,000 times, executing well under a millisecond.

Space Complexity:
O(1)

* The algorithm relies exclusively on a few stack variables to keep track of transition times and the minimum total time.
* No auxiliary data structures, vectors, or dynamic allocations are created, yielding constant space complexity.
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
        // Optimize standard I/O operations for performance
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = landStartTime.size();
        int m = waterStartTime.size();
        int minFinishTime = INT_MAX;

        // Exhaustive check for every land ride and water ride combination
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                
                // Scenario A: Land ride 'i' followed by Water ride 'j'
                int landFinish = landStartTime[i] + landDuration[i];
                int waterStart = max(landFinish, waterStartTime[j]);
                int totalFinish1 = waterStart + waterDuration[j];
                
                // Scenario B: Water ride 'j' followed by Land ride 'i'
                int waterFinish = waterStartTime[j] + waterDuration[j];
                int landStart = max(waterFinish, landStartTime[i]);
                int totalFinish2 = landStart + landDuration[i];
                
                // Keep track of the absolute minimum finish time across all paths
                minFinishTime = min({minFinishTime, totalFinish1, totalFinish2});
            }
        }

        return minFinishTime;
    }
};