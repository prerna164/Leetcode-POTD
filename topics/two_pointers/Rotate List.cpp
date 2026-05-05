/*
Problem: Rotate List
Link: LeetCode 61

Date: 2026-05-05
Difficulty: Medium
Tags: Linked List, Two Pointers

🧠 Intuition:

Rotating a linked list to the right by k places means taking the last k nodes 
and moving them to the front. 

Key Observations:
1. If k is greater than the length of the list (L), rotating k times is the 
   same as rotating (k % L) times.
2. If k % L == 0, the list remains unchanged.
3. To perform the rotation, we can connect the tail of the list to the head 
   to form a circle, then find the new tail and break the circle.

The new tail will be at position (Length - (k % Length) - 1) from the start.
The new head will be the node immediately following the new tail.

--------------------------------------------------------

⚙️ Approach:

1. Edge Cases:
   If the head is NULL, or has only one node, or k is 0, return head immediately.

2. Calculate Length:
   Traverse the list to find the total length (L) and stop at the last node.

3. Make it Circular:
   Connect the last node's 'next' pointer to the current 'head'.

4. Find New Break Point:
   - Effective rotations needed: k = k % L.
   - The number of steps to reach the new tail from the current position is (L - k).
   - Move the pointer (L - k) times.

5. Break the Circle:
   - Set the new head as newTail->next.
   - Set newTail->next = NULL to terminate the list.

--------------------------------------------------------

⏱ Time Complexity:

O(N)

- One pass to find the length and the tail: O(N).
- Another pass to find the new tail (at most N steps): O(N).
- Total time is linear relative to the number of nodes.

📦 Space Complexity:

O(1)

- We only use a few pointer variables to manipulate the existing nodes.
- No extra memory or recursion stack is used.

*/

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
    ListNode* rotateRight(ListNode* head, int k) {
        // Handle edge cases: empty list, single node, or no rotation
        if (!head || !head->next || k == 0) {
            return head;
        }

        // Step 1: Calculate the length of the list and find the tail
        ListNode* tail = head;
        int length = 1;
        while (tail->next) {
            tail = tail->next;
            length++;
        }

        // Step 2: Handle cases where k >= length
        k = k % length;
        if (k == 0) {
            return head;
        }

        // Step 3: Connect tail to head to make it circular
        tail->next = head;

        // Step 4: Find the new tail
        // The new tail is at (length - k) steps from the current head
        // or (length - k - 1) steps from the current tail
        int stepsToNewTail = length - k;
        ListNode* newTail = tail; 
        while (stepsToNewTail--) {
            newTail = newTail->next;
        }

        // Step 5: Break the circle
        ListNode* newHead = newTail->next;
        newTail->next = nullptr;

        return newHead;
    }
};