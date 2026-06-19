/*
Problem: Find the Highest Altitude
Link: Road Trip Altitude Tracking

Date: 2026-06-19
Difficulty: Easy
Tags: Array, Prefix Sum, Simulation

Intuition:
The problem asks us to track the net altitude changes of a biker along a road trip and determine the maximum height reached. 

The biker starts at point 0 with an altitude of 0. For each segment `i`, the altitude updates dynamically based on the net gain value provided:
  current_altitude[i + 1] = current_altitude[i] + gain[i]

This is a classic prefix sum problem. We can continuously update a running sum tracking variable representing our `current_altitude` as we loop through the `gain` array. At each point, we compare it against a running maximum tracker `max_altitude` to keep a snapshot record of the peak elevation achieved.

---

Approach:

1. Initialization:
   * Instantiate an integer variable `current_altitude` at 0 to track the real-time height profile.
   * Instantiate an integer variable `max_altitude` at 0 to record the highest summit reached.

2. Sequential Simulation:
   * Loop through each gain entry in the `gain` array.
   * Add the active gain value to `current_altitude`.
   * Compare and update `max_altitude = max(max_altitude, current_altitude)`.

3. Return Payload:
   * After checking all road points, return `max_altitude`.

---

⏱ Time Complexity:
O(N)

* We iterate through the `gain` array exactly once.
* Each element addition and maximum comparison operation runs in strict O(1) constant time.
* The total computation scales perfectly linearly with the array length N.

Space Complexity:
O(1) Auxiliary Space

* The solution does not allocate any extra arrays, vectors, or data configurations.
* Memory usage remains flat and constant irrespective of the size of the input configuration.
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int largestAltitude(vector<int>& gain) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int max_altitude = 0;
        int current_altitude = 0;

        // Process net changes sequentially to track the altitude curve profile
        for (int net_gain : gain) {
            current_altitude += net_gain;
            max_altitude = max(max_altitude, current_altitude);
        }

        return max_altitude;
    }
};