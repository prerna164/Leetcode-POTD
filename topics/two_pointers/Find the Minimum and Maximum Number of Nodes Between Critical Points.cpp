/*
Problem: Find the Minimum and Maximum Number of Nodes Between Critical Points
Link: LeetCode 2058 - Find the Minimum and Maximum Number of Nodes Between Critical Points

Difficulty: Medium
Tags: Linked List, Two Pointers

Intuition:
A node is a critical point if it is strictly greater than or strictly less than both its previous and next neighbor.
We can iterate through the linked list while tracking:
1. The position (1-based index) of the first critical point found (`first_idx`).
2. The position of the most recent critical point found (`prev_idx`).
3. The overall minimum distance seen between consecutive critical points (`min_dist`).

Key Observations:
- Maximum Distance: Always the distance between the very first critical point and the very last critical point (`prev_idx - first_idx`).
- Minimum Distance: The minimum distance between any adjacent critical points observed during traversal.
- If fewer than 2 critical points are found, return `{-1, -1}`.

---

Approach:

1. Initialization:
   * Maintain three pointers: `prev = head`, `curr = head->next`, and `next_node = curr->next`.
   * Keep track of `curr_idx = 2` (since `curr` starts at the 2nd node).
   * Record `first_idx = -1`, `prev_idx = -1`, and `min_dist = INT_MAX`.

2. Single Pass Traversal:
   * Loop while `curr` and `curr->next` are not null.
   * Check if `curr->val` is a local maxima (`curr->val > prev->val && curr->val > curr->next->val`)
     or a local minima (`curr->val < prev->val && curr->val < curr->next->val`).
   * If `curr` is a critical point:
     - If `first_idx == -1`, set `first_idx = curr_idx`.
     - Else, update `min_dist = min(min_dist, curr_idx - prev_idx)`.
     - Update `prev_idx = curr_idx`.
   * Advance pointers and increment `curr_idx`.

3. Result Formulating:
   * If fewer than 2 critical points were encountered (`prev_idx == -1` or `first_idx == prev_idx`), return `{-1, -1}`.
   * Otherwise, return `{min_dist, prev_idx - first_idx}`.

---

⏱ Time Complexity:
O(N)

* Single pass traversal over the linked list of N nodes.

Space Complexity:
O(1) Auxiliary Space

* Requires only a few scalar pointer and integer variables.
*/

#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>

using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        if (!head || !head->next || !head->next->next) {
            return {-1, -1};
        }

        ListNode* prev = head;
        ListNode* curr = head->next;
        int curr_idx = 2;

        int first_idx = -1;
        int prev_idx = -1;
        int min_dist = INT_MAX;

        while (curr->next != nullptr) {
            ListNode* next_node = curr->next;

            // Check if current node is a local maxima or local minima
            bool is_maxima = (curr->val > prev->val) && (curr->val > next_node->val);
            bool is_minima = (curr->val < prev->val) && (curr->val < next_node->val);

            if (is_maxima || is_minima) {
                if (first_idx == -1) {
                    first_idx = curr_idx;
                } else {
                    min_dist = min(min_dist, curr_idx - prev_idx);
                }
                prev_idx = curr_idx;
            }

            prev = curr;
            curr = curr->next;
            curr_idx++;
        }

        // If fewer than two critical points exist
        if (first_idx == -1 || first_idx == prev_idx) {
            return {-1, -1};
        }

        int max_dist = prev_idx - first_idx;

        return {min_dist, max_dist};
    }
};