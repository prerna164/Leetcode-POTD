/*
Problem: Minimum Initial Energy to Finish Tasks
Link: LeetCode 1665

Date: 2026-05-12
Difficulty: Hard
Tags: Array, Greedy, Sorting

🧠 Intuition:

Each task has two values: 'actual' (what you spend) and 'minimum' (what you need 
to have to start). The "hidden cost" or "buffer" of a task is: 
buffer = (minimum - actual).

This buffer represents energy that must be present in your tank but isn't 
consumed. To minimize the total starting energy, we want to satisfy the 
most "demanding" buffers first. If we leave a task with a large buffer for 
the end, we might have enough energy to cover the consumption, but we won't 
have enough "spare" energy left to satisfy the starting requirement.

Therefore, the greedy strategy is to sort tasks by the difference (minimum - actual) 
in descending order.

--------------------------------------------------------

⚙️ Approach:

1. Use a custom comparator to sort the 'tasks' vector. Tasks with a larger 
   difference between 'minimum' and 'actual' come first.
2. Track two integers:
   - 'totalRequired': The answer we will return (minimum initial energy).
   - 'currentEnergy': The amount of energy available at any point during execution.
3. Iterate through each task:
   a. If 'currentEnergy' is less than the 'minimum' requirement of the task:
      - We calculate the deficit: (minimum - currentEnergy).
      - Add this deficit to 'totalRequired' (meaning we should have started 
        with this much more energy).
      - Increase 'currentEnergy' by this deficit so it exactly equals 'minimum'.
   b. Deduct 'actual' energy from 'currentEnergy'.
4. Return 'totalRequired'.

--------------------------------------------------------

⏱ Time Complexity:

O(N log N)

- N is the number of tasks.
- Sorting the tasks takes O(N log N).
- The single pass to calculate the energy takes O(N).

📦 Space Complexity:

O(1) (or O(log N) for sort stack)

- We sort the input array in place.
- Only a few integer variables are used for tracking energy.

*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minimumEffort(vector<vector<int>>& tasks) {
        // Step 1: Sort tasks based on the "buffer" (minimum - actual) 
        // in descending order.
        sort(tasks.begin(), tasks.end(), [](const vector<int>& a, const vector<int>& b) {
            // (a[1] - a[0]) is the buffer for task A
            // (b[1] - b[0]) is the buffer for task B
            return (a[1] - a[0]) > (b[1] - b[0]);
        });

        int totalRequired = 0;
        int currentEnergy = 0;

        // Step 2: Iterate through the sorted tasks and adjust 
        // the initial requirement as we encounter deficits.
        for (const auto& task : tasks) {
            int actual = task[0];
            int minimum = task[1];

            // If we don't meet the starting threshold for the current task
            if (currentEnergy < minimum) {
                // Calculate how much more energy we needed to have brought
                int deficit = minimum - currentEnergy;
                totalRequired += deficit;
                
                // Add that deficit to our current "tank"
                currentEnergy += deficit;
            }
            
            // Spend the actual energy required for the task
            currentEnergy -= actual;
        }

        return totalRequired;
    }
};