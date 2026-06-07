/*
Problem: Create Binary Tree From Descriptions
Link: Binary Tree Generation from Relational Slices

Date: 2026-06-07
Difficulty: Medium
Tags: Hash Table, Tree, Binary Tree

Intuition:
The problem provides parent-child relationships alongside left/right edge configurations and asks us to reconstruct the unique binary tree. 

We can solve this problem in two main steps:
1. Node Creation and Graph Linking: 
   As we iterate through the relations, we might encounter parent or child node values that haven't been instantiated yet. We can use a hash map (`unordered_map<int, TreeNode*>`) to instantly map a numeric value to its corresponding `TreeNode` object. If a value isn't in the map, we create it. Once both the parent and child nodes are retrieved or created, we link them according to the `isLeft` flag.

2. Identifying the Root Node:
   The root of a valid tree is structurally unique because it is the only node that has no parent. Every other node in the tree appears exactly once as a child. By tracking all values that appear as children in a hash set (`unordered_set<int>`), we can scan all unique parent values at the end; the parent value missing from the child set must be the root of the tree.

---

Approach:

1. Initialization:
   * Create an `unordered_map<int, TreeNode*>` named `nodeMap` to keep track of created tree nodes by their values.
   * Create an `unordered_set<int>` named `children` to store all node values that act as a child.

2. Build Nodes and Edges:
   * Loop through each relation `[parentVal, childVal, isLeft]` in `descriptions`:
     - If `parentVal` does not exist in `nodeMap`, instantiate a new `TreeNode(parentVal)` and store it.
     - If `childVal` does not exist in `nodeMap`, instantiate a new `TreeNode(childVal)` and store it.
     - If `isLeft == 1`, set `nodeMap[parentVal]->left = nodeMap[childVal]`.
     - If `isLeft == 0`, set `nodeMap[parentVal]->right = nodeMap[childVal]`.
     - Insert `childVal` into the `children` set.

3. Find the Root:
   * Iterate through the descriptions list again (or iterate through the keys of `nodeMap`). For each relation, look at the `parentVal`.
   * Check if `parentVal` exists in the `children` set. If it does not, this node is the absolute root.
   * Return `nodeMap[parentVal]`.

---

⏱ Time Complexity:
O(N)

* We iterate through the descriptions list of size N exactly twice (once to build the nodes/edges, and once to find the root).
* Inside the loops, all operations such as hash map lookups, insertions, and pointers assignments run in average O(1) time.
* Total execution time scales linearly with the number of descriptions, which perfectly satisfies the N = 10^4 constraint.

Space Complexity:
O(N)

* The `nodeMap` stores at most 2 * N unique pointers to nodes.
* The `children` set stores at most N unique child integers.
* The extra dynamic allocation scales linearly with the number of edges provided in the input tree.
*/

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 * int val;
 * TreeNode *left;
 * TreeNode *right;
 * TreeNode() : val(0), left(nullptr), right(nullptr) {}
 * TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

class Solution {
public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        // Optimize standard I/O streams for competitive programming speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        unordered_map<int, TreeNode*> nodeMap;
        unordered_set<int> children;

        // Step 1: Instantiate nodes and establish parent-child links
        for (const auto& desc : descriptions) {
            int parentVal = desc[0];
            int childVal = desc[1];
            int isLeft = desc[2];

            // If the parent node doesn't exist yet, create it
            if (nodeMap.find(parentVal) == nodeMap.end()) {
                nodeMap[parentVal] = new TreeNode(parentVal);
            }

            // If the child node doesn't exist yet, create it
            if (nodeMap.find(childVal) == nodeMap.end()) {
                nodeMap[childVal] = new TreeNode(childVal);
            }

            // Establish the pointer connections
            if (isLeft == 1) {
                nodeMap[parentVal]->left = nodeMap[childVal];
            } else {
                nodeMap[parentVal]->right = nodeMap[childVal];
            }

            // Mark this node value as a child
            children.insert(childVal);
        }

        // Step 2: Find the root node (the only node that is never a child)
        for (const auto& desc : descriptions) {
            int parentVal = desc[0];
            if (children.find(parentVal) == children.end()) {
                return nodeMap[parentVal];
            }
        }

        return nullptr;
    }
};