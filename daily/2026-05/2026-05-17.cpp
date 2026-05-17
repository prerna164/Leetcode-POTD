/*
Problem: Jump Game III
Link: LeetCode 1306

Difficulty: Medium
Tags: Array, Depth-First Search (DFS), Breadth-First Search (BFS)

🧠 Intuition:
From any given index `i`, we have at most two choices: jump forward to `i + arr[i]` or jump backward to `i - arr[i]`. 
This structure naturally forms a graph where each index is a node, and the possible jumps are directed edges. 

The goal is to determine if a path exists from the `start` node to any node whose value is `0`. 

To solve this efficiently and avoid infinite loops caused by cycling back to already visited indices, 
we keep track of the indices we have already checked. We do this in-place by marking visited elements as negative, 
eliminating the need for an extra hash set or boolean array.

--------------------------------------------------------

⚙️ Approach:
1. Base Cases for Recursion:
   - If `start` goes out of bounds (`start < 0` or `start >= arr.size()`), return `false`.
   - If `arr[start] < 0`, it means we have visited this index before. Return `false` to break the cycle.
2. Target Found:
   - If `arr[start] == 0`, we have successfully reached a zero element. Return `true`.
3. State Modification (Marking Visited):
   - Cache the current jump value: `int jump = arr[start]`.
   - Mark the current index as visited by flipping its sign: `arr[start] = -arr[start]`.
4. Recursive Exploration:
   - Recurse in both valid directions: forward (`start + jump`) and backward (`start - jump`).
   - If either direction returns `true`, propagate `true` up the call stack.

--------------------------------------------------------

⏱ Time Complexity:
O(n) - In the worst case, we will visit every index in the array exactly once.

📦 Space Complexity:
O(n) - Call stack space for recursion in the worst-case scenario.

*/

#include <vector>

using namespace std;

class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        // Base case: Out of bounds or already visited
        if (start < 0 || start >= arr.size() || arr[start] < 0) {
            return false;
        }
        
        // Target condition reached
        if (arr[start] == 0) {
            return true;
        }
        
        // Cache the jump value and mark the current index as visited
        int jump = arr[start];
        arr[start] = -arr[start];
        
        // Explore both forward and backward paths
        return canReach(arr, start + jump) || canReach(arr, start - jump);
    }
};