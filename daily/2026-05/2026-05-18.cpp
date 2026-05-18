/*
Problem: Jump Game IV
Link: LeetCode 1345

Date: 2026-05-18
Difficulty: Hard
Tags: Array, Hash Table, Breadth-First Search (BFS)

🧠 Intuition:
This problem asks for the minimum number of steps to reach the last index of an array. 
Finding the shortest path in an unweighted step-based scenario makes Breadth-First Search (BFS) 
the perfect algorithmic approach.

From any given index `i`, we can transition to:
1. `i + 1` (Forward)
2. `i - 1` (Backward)
3. Any index `j` where `arr[i] == arr[j]` (Value-based jumps)

To handle the value-based jumps without scanning the entire array repeatedly, we pre-group 
all identical values to their corresponding list of indices using a hash map (`unordered_map<int, vector<int>>`).

⚠️ Crucial Optimization to Prevent TLE (Time Limit Exceeded):
If an array contains thousands of identical numbers in a sequence (e.g., [7, 7, 7, ..., 7]), 
a standard BFS loop would constantly inspect all other identical indices from every single 
one of those nodes. This results in a nested constraint blowup of O(n^2). 
To circumvent this, the moment we extract and explore the "same-value" indices list for a specific 
value, we immediately clear or erase that key from our hash map. This guarantees that any group 
of identical indices is processed exactly once throughout the entire search.

--------------------------------------------------------

⚙️ Approach:
1. Corner Case: If the array length is 1, we are already at the destination; return 0.
2. Group Values: Populate an `unordered_map<int, vector<int>> valueToIndices` to record 
   the positions of every element.
3. Queue Initialization: Standardize a BFS queue `queue<int> q` and push the starting index `0`.
4. Visited Array: Maintain a `vector<bool> visited(n, false)` to prevent cycle processing, 
   marking `visited[0] = true`.
5. Level-by-Level Traverse: Track an integer variable `steps = 0`. For each loop step, 
   isolate the snapshot size of the current queue level.
6. Node Expansion:
   - If `curr == n - 1`, we have reached the last index. Return `steps`.
   - Check `curr + 1`: if valid and unvisited, push to queue and mark visited.
   - Check `curr - 1`: if valid and unvisited, push to queue and mark visited.
   - Access the hash map for `arr[curr]`. Iterate through its entire list of indices. 
     For any unvisited index, push it to the queue and mark visited.
   - Clear/erase `arr[curr]` from the map to lock out duplicate traversals.
7. Step Increment: Increment `steps` by 1 after wrapping up a complete queue level.

--------------------------------------------------------

⏱ Time Complexity:
O(n)
- Every index is pushed and popped from the BFS queue at most once.
- Clearing the hash map entry right after its first use ensures that the total time spent 
  looping through the value-based indices collectively takes at most O(n) operations across 
  the lifespan of the entire program.

📦 Space Complexity:
O(n)
- The hash map keeps a record of all n indices mapped by their specific integer values.
- The `visited` vector and the BFS queue will scale up to hold a maximum of n elements.

*/

#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

class Solution {
public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();
        if (n <= 1) return 0;

        // Group indices by their corresponding values
        unordered_map<int, vector<int>> valueToIndices;
        for (int i = 0; i < n; i++) {
            valueToIndices[arr[i]].push_back(i);
        }

        queue<int> q;
        vector<bool> visited(n, false);

        // Initialize BFS from index 0
        q.push(0);
        visited[0] = true;
        int steps = 0;

        // Execute level-order BFS
        while (!q.empty()) {
            int size = q.size();

            for (int i = 0; i < size; i++) {
                int curr = q.front();
                q.pop();

                // Base condition check: Destination reached
                if (curr == n - 1) {
                    return steps;
                }

                // Neighbor Option 1: Jump to i + 1
                if (curr + 1 < n && !visited[curr + 1]) {
                    visited[curr + 1] = true;
                    q.push(curr + 1);
                }

                // Neighbor Option 2: Jump to i - 1
                if (curr - 1 >= 0 && !visited[curr - 1]) {
                    visited[curr - 1] = true;
                    q.push(curr - 1);
                }

                // Neighbor Option 3: Jump to any index j where arr[i] == arr[j]
                if (valueToIndices.count(arr[curr])) {
                    for (int nextIndex : valueToIndices[arr[curr]]) {
                        if (!visited[nextIndex]) {
                            visited[nextIndex] = true;
                            q.push(nextIndex);
                        }
                    }
                    // CRITICAL OPTIMIZATION: Erase value group to prevent O(n^2) worst-case TLE
                    valueToIndices.erase(arr[curr]);
                }
            }
            steps++;
        }

        return -1; 
    }
};