/*
Problem: Detect Cycles in 2D Grid
Link: https://leetcode.com/problems/detect-cycles-in-2d-grid/

Difficulty: Medium
Tags: Array, Depth-First Search, Breadth-First Search, Union Find, Matrix
-----------------------------------------------------

🧠 Intuition:
- We need to find a path of length ≥ 4 that starts and ends at the same cell
using only the same character values.
- This is essentially finding a cycle in an undirected graph where cells are
nodes
and adjacent identical characters are edges.
- The constraint "cannot move to the cell visited in last move" is key:
it means we shouldn't immediately reverse our step.
- If we encounter a cell that is already 'Visited' and is NOT the parent (the
cell
we just came from), a cycle of length at least 4 must exist.
-----------------------------------------------------

⚙️ Approach:
1. Use a 2D boolean array 'visited' to keep track of processed cells.
2. Iterate through every cell in the grid. If it's not visited, start a DFS.
3. In DFS, track the 'parent' coordinates (pr, pc) to avoid moving backward.
4. For the current cell, explore all 4 neighbors (Up, Down, Left, Right).
5. If a neighbor has the same character value as the current cell:
- If it's already visited and NOT the parent, return true (Cycle Detected).
- If it's not visited, recursively call DFS for that neighbor.
6. If no cycle is found after traversing the whole grid, return false.
-----------------------------------------------------

⏱ Time Complexity:
- O(M × N): Each cell is visited at most once by the DFS because of the
visited array.

📦 Space Complexity:
- O(M × N): Required for the visited array and the recursion stack in
the worst-case (a grid full of the same character).
-----------------------------------------------------
*/

#include <vector>
using namespace std;
class Solution {

public:
bool containsCycle(vector<vector<char>>& grid) {
int m = grid.size();
int n = grid[0].size();
vector<vector<bool>> visited(m, vector<bool>(n, false));
for (int i = 0; i < m; ++i) {
for (int j = 0; j < n; ++j) {
if (!visited[i][j]) {
if (dfs(grid, visited, i, j, -1, -1, grid[i][j])) {
return true;

}
}
}
}
return false;
}
private:
bool dfs(vector<vector<char>>& grid, vector<vector<bool>>& visited,

int r, int c, int pr, int pc, char target) {

visited[r][c] = true;
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};
for (int i = 0; i < 4; ++i) {
int nr = r + dr[i];
int nc = c + dc[i];
// Check boundaries and if character matches
if (nr >= 0 && nr < grid.size() && nc >= 0 && nc < grid[0].size()

&& grid[nr][nc] == target) {
if (visited[nr][nc]) {
// If visited and not the parent, we found a cycle
if (nr != pr || nc != pc) {
return true;

}
} else {

if (dfs(grid, visited, nr, nc, r, c, target)) {
return true;

}
}
}
}
return false;
}
};