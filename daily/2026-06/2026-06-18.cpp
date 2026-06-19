/*
Problem: Angle Between Hands of a Clock
Link: Clock Geometry Calculation

Date: 2026-06-18
Difficulty: Medium
Tags: Math, Simulation, Geometry

Intuition:
The problem asks for the smaller angle between the hour and minute hands of a standard 12-hour analog clock. We can calculate this by finding the absolute position (in degrees) of both hands relative to the 12 o'clock position (0 degrees).

1. Minute Hand Position:
   * A clock face is a full circle of 360 degrees, divided into 60 minutes.
   * Each minute equals 360 / 60 = 6 degrees.
   * Thus, the minute hand angle is: `minutes * 6`.

2. Hour Hand Position:
   * The clock face is divided into 12 hours. Each hour shift equals 360 / 12 = 30 degrees.
   * However, the hour hand also shifts continuously as minutes pass. In 60 minutes, it moves 30 degrees, which means it moves 30 / 60 = 0.5 degrees per minute.
   * Thus, the hour hand angle is: `(hour % 12) * 30 + minutes * 0.5`. (Note: 12 o'clock maps to 0 degrees).

3. Final Angle Calculation:
   * Find the absolute difference: `diff = abs(hour_angle - minute_angle)`.
   * Since we want the *smaller* angle between the two hands, if the difference is greater than 180 degrees, the complement angle is the smaller one: `360 - diff`.

---

Approach:

1. Hand Angle Evaluation:
   * Compute `minute_angle = minutes * 6.0`.
   * Compute `hour_angle = (hour % 12) * 30.0 + minutes * 0.5`.

2. Calculate Absolute Difference:
   * Find `angle = abs(hour_angle - minute_angle)`.

3. Bounds Minimization:
   * If `angle > 180.0`, update `angle = 360.0 - angle`.
   * Return the final floating-point angle representation.

---

⏱ Time Complexity:
O(1)

* The calculation utilizes standard basic arithmetic equations running in fixed constant O(1) execution steps.

Space Complexity:
O(1) Auxiliary Space

* No supplementary data configurations are allocated, using purely temporary primitive floating-point metrics.
*/

#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    double angleClock(int hour, int minutes) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        // Step 1: Compute positions of both hands in degrees relative to the 12:00 baseline
        double minute_angle = minutes * 6.0;
        double hour_angle = (hour % 12) * 30.0 + minutes * 0.5;

        // Step 2: Find the absolute degree difference
        double angle = abs(hour_angle - minute_angle);

        // Step 3: Return the minimal inside angle (must be <= 180 degrees)
        if (angle > 180.0) {
            angle = 360.0 - angle;
        }

        return angle;
    }
};