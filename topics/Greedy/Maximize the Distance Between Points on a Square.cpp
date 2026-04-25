/*
Problem: Maximize the Distance Between Points on a Square (Maximize Minimum Manhattan Distance)
Link: https://leetcode.com/problems/maximize-the-minimum-game/ (Contest 438)

Date: 2024-04-24
Difficulty: Hard
Tags: Array, Binary Search, Geometry, Sorting, Greedy

-----------------------------------------------------

🧠 Intuition:
- The problem asks to "maximize the minimum distance," a classic hint for Binary Search on the Answer.
- All points lie on the boundary of a square. Instead of treating them as 2D coordinates (x, y), 
  we can "unroll" the perimeter of the square into a 1D line of length 4 * side.
- On a square's boundary, the Manhattan distance between two points is generally equivalent to 
  their distance along the perimeter (unless they are on opposite sides, but the perimeter path 
  still serves as a valid monotonic mapping for selection).
- Once points are sorted on this 1D line, we can greedily check if it's possible to place k points 
  with at least 'mid' distance between them.

-----------------------------------------------------

⚙️ Approach:
1. Linearization: Convert each (x, y) point to a 1D position `d` based on which edge it sits on:
   - Bottom (y=0): d = x
   - Right (x=side): d = side + y
   - Top (y=side): d = 2*side + (side - x)
   - Left (x=0): d = 3*side + (side - y)
2. Sorting: Sort the 1D positions to enable greedy placement.
3. Binary Search: Range [1, 4 * side / k].
4. Greedy Check (canPlace):
   - Because the square is a closed loop, the choice of the first point matters.
   - However, since k is small (up to 25), we can try starting from the first few points.
   - For a starting point, pick the next point that is at least `mid` distance away.
   - After picking k points, ensure the distance from the last point back to the first 
     (around the loop) is also >= `mid`.

-----------------------------------------------------

⏱ Time Complexity:
- O(N log N + N * log(Perimeter)): 
  - N log N to sort the points.
  - log(Perimeter) iterations for binary search.
  - In each iteration, we check potential starting points (effectively O(N) in worst case, 
    but highly pruned by the circular constraint).

📦 Space Complexity:
- O(N): To store the 1D linearized coordinates.

-------------------------------------
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxDistance(int side, vector<vector<int>>& points, int k) {
        int n = points.size();
        vector<long long> dists;

        // Step 1: Linearize the 2D points into 1D positions along the perimeter
        for (const auto& p : points) {
            long long x = p[0], y = p[1];
            if (y == 0) {
                dists.push_back(x);
            } else if (x == side) {
                dists.push_back(side + y);
            } else if (y == side) {
                dists.push_back(2LL * side + (side - x));
            } else {
                dists.push_back(3LL * side + (side - y));
            }
        }

        sort(dists.begin(), dists.end());

        // Step 2: Binary Search on the minimum Manhattan distance
        long long low = 1, high = 4LL * side;
        long long ans = 0;
        long long perimeter = 4LL * side;

        while (low <= high) {
            long long mid = low + (high - low) / 2;
            if (check(mid, dists, k, perimeter)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return (int)ans;
    }

private:
    bool check(long long mid, const vector<long long>& dists, int k, long long perimeter) {
        int n = dists.size();
        
        // We only need to test starting points within the first gap 
        // covered by 'mid', because if a solution exists, one must 
        // start within distance 'mid' of the first point.
        for (int i = 0; i < n; ++i) {
            if (dists[i] - dists[0] >= mid) break;

            int count = 1;
            long long lastPos = dists[i];
            for (int j = i + 1; j < n; ++j) {
                if (dists[j] - lastPos >= mid) {
                    count++;
                    lastPos = dists[j];
                    if (count == k) break;
                }
            }

            // Circular constraint: Distance from last point back to first point
            if (count == k && (perimeter - (lastPos - dists[i])) >= mid) {
                return true;
            }
        }
        return false;
    }
};