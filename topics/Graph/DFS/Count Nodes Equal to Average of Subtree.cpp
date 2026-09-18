/*
Problem: Count Nodes Equal to Average of Subtree
Link: LeetCode 2265 - Count Nodes Equal to Average of Subtree

Difficulty: Medium
Tags: Tree, Depth-First Search, Binary Tree

Intuition:
To calculate the average of a subtree rooted at any node:
1. We need the sum of all node values in its subtree.
2. We need the total count of nodes in its subtree.

Using a bottom-up Depth-First Search (DFS) / Post-order Traversal:
- For each node, we recursively calculate the `(sum, count)` of its left and right subtrees.
- Current subtree sum = `left.sum + right.sum + current_node.val`
- Current subtree count = `left.count + right.count + 1`
- The average is `current_subtree_sum / current_subtree_count` (using integer division for rounding down).
- If `current_node.val == average`, increment global match counter.

---

Approach:

1. Define a helper recursive DFS function that returns a `pair<int, int>` representing `{sum, count}` for the subtree.
2. In post-order traversal:
   * Base Case: If `root == nullptr`, return `{0, 0}`.
   * Recursively get `{left_sum, left_count}` and `{right_sum, right_count}`.
   * Calculate `total_sum = left_sum + right_sum + root->val`.
   * Calculate `total_count = left_count + right_count + 1`.
   * Check if `total_sum / total_count == root->val`. If true, increment result counter.
   * Return `{total_sum, total_count}` up to the parent.
3. Return total matching nodes from `averageOfSubtree`.

---

⏱ Time Complexity:
O(N)

* Every node in the binary tree is visited exactly once during DFS traversal.
* Total Runtime: O(N) linear time.

Space Complexity:
O(H) Auxiliary Space

* Space used by the recursion call stack, where `H` is the height of the tree.
* Worst case (skewed tree): O(N).
* Best case (balanced tree): O(log N).
*/

#include <iostream>
#include <utility>

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    int matchingNodesCount = 0;

    // Helper function returns {subtree_sum, subtree_count}
    pair<int, int> dfs(TreeNode* root) {
        if (!root) {
            return {0, 0};
        }

        auto [leftSum, leftCount] = dfs(root->left);
        auto [rightSum, rightCount] = dfs(root->right);

        int currentSum = leftSum + rightSum + root->val;
        int currentCount = leftCount + rightCount + 1;

        if (currentSum / currentCount == root->val) {
            matchingNodesCount++;
        }

        return {currentSum, currentCount};
    }

public:
    int averageOfSubtree(TreeNode* root) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        matchingNodesCount = 0;
        dfs(root);
        return matchingNodesCount;
    }
};