/*
Problem: Longest Common Suffix Queries (Find Longest Common Suffix with Constraints)
Link: LeetCode 3093

Date: 2026-05-28
Difficulty: Hard
Tags: Array, String, Trie, Memory Optimization

Intuition:
The problem asks us to find a word in `wordsContainer` that shares the longest common *suffix* with a given query word. If there's a tie, we minimize the length of the string, and if there is still a tie, we minimize the index.

1. Suffix to Prefix: A common suffix problem can always be transformed into a common prefix problem by reversing the strings. Finding the longest common suffix of "abcd" and "bcd" is exactly equivalent to finding the longest common prefix of "dcba" and "dcb".
2. Multi-Criteria Optimal Selection: As we traverse or build our Prefix Tree (Trie), each node represents a shared suffix matching state. Instead of evaluating the "best string" criteria (shortest length, then lowest index) during runtime for each query, we can proactively calculate and store the `best_index` at every single node during insertion.
3. Memory Optimization Trick: Standard dynamic Trie nodes allocate an array of 26 pointers (`TrieNode* children[26]`). On 64-bit systems, this costs 208 bytes per node just for pointers. Under tight memory limits with deeply repeating patterns (e.g., "aaaaa..."), this causes a Memory Limit Exceeded (MLE) error due to pointer overhead and heap fragmentation. We fix this by utilizing a flat `std::vector<TrieNode>` as a localized memory pool where child pointers are replaced by small 4-byte `int` array indices.

--------------------------------------------------------
Approach:
1. Determine a Global Default: Find the index of the absolute shortest string (and earliest, if tied) in `wordsContainer`. If a query shares absolutely no common suffix with any container word, it will hit the root node of the Trie, which should instantly fall back to this global optimal index.
2. Structure the Flat Trie: Define a `TrieNode` using an integer array `children[26]` initialized to -1, along with a `best_index` field. Maintain a global `vector<TrieNode> trie` pool, initializing index 0 as our root node with the global default index.
3. Build the Trie (Insert Phase): Loop through each string in `wordsContainer`.
   - Update the root node's `best_index` against the current word based on the rules: prioritize shorter length, then smaller original index.
   - Loop through the string backwards (from last character to first).
   - If `children[idx]` is -1, instantiate a new node by pushing it onto our `trie` vector, linking the current node's child pointer to `trie.size() - 1`.
   - Move to the child node and immediately evaluate if the current word's index is a better fit than its existing `best_index`.
4. Process Queries (Search Phase): Loop through each string in `wordsQuery`.
   - Start at root index 0. Track the `last_valid_index = trie[0].best_index`.
   - Traverse the query string backwards. If a child mapping exists, navigate down and update `last_valid_index = trie[curr].best_index`.
   - If the path breaks (no matching child node), break the traversal early. The `last_valid_index` holds the optimal result at the deepest common suffix node reached.
5. Save the result to an answer vector and return.

--------------------------------------------------------
⏱ Time Complexity:
O(N * L_C + M * L_Q)
- Building the Trie takes O(N * L_C) time, where N is the size of `wordsContainer` and L_C is the average length of a container word, because we iterate through every character of each word once.
- Processing Queries takes O(M * L_Q) time, where M is the size of `wordsQuery` and L_Q is the average length of a query string, as we trace down the tree for each character.
- Given the sum of all lengths is <= 5 * 10^5, this linear execution safely finishes well under the time limit.

Space Complexity:
O(Σ L_C)
- The space complexity scales linearly with the total number of characters across all words in `wordsContainer` that form distinct node paths.
- By flattening the Trie structure into a primitive vector (`vector<TrieNode>`), we eliminate structural heap allocation overhead and 8-byte pointer padding, bringing down the storage footprint dramatically to fit safely within strict Memory Limits.
*/

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

// Compact Trie Node using array indexing instead of raw heap pointers
struct TrieNode {
    int children[26];
    int best_index;

    TrieNode(int index) {
        fill(begin(children), end(children), -1);
        best_index = index;
    }
};

class Solution {
private:
    vector<TrieNode> trie;

    // Helper to evaluate if the new word is better than the current recorded best word
    bool isBetter(int new_idx, int current_best, const vector<string>& wordsContainer) {
        if (wordsContainer[new_idx].length() < wordsContainer[current_best].length()) {
            return true;
        }
        if (wordsContainer[new_idx].length() == wordsContainer[current_best].length()) {
            return new_idx < current_best;
        }
        return false;
    }

    void insert(const string& word, int word_index, const vector<string>& wordsContainer) {
        int curr_node_idx = 0; // The Root node is always located at index 0
        
        // Update root node fallback criteria
        if (isBetter(word_index, trie[curr_node_idx].best_index, wordsContainer)) {
            trie[curr_node_idx].best_index = word_index;
        }

        // Standard Trie insertion processed in reverse order (Suffix to Prefix)
        for (int i = word.length() - 1; i >= 0; --i) {
            int idx = word[i] - 'a';
            
            // If the node does not exist, allocate it within our contiguous vector memory pool
            if (trie[curr_node_idx].children[idx] == -1) {
                trie.push_back(TrieNode(word_index));
                trie[curr_node_idx].children[idx] = trie.size() - 1;
            }
            
            curr_node_idx = trie[curr_node_idx].children[idx];
            
            // Proactively update the current node's optimal index
            if (isBetter(word_index, trie[curr_node_idx].best_index, wordsContainer)) {
                trie[curr_node_idx].best_index = word_index;
            }
        }
    }

    int search(const string& query) {
        int curr_node_idx = 0;
        int last_valid_index = trie[0].best_index;

        // Trace the query backwards to extract the longest matched suffix path
        for (int i = query.length() - 1; i >= 0; --i) {
            int idx = query[i] - 'a';
            if (trie[curr_node_idx].children[idx] == -1) {
                break; // Path split/mismatch encountered, terminate lookup
            }
            curr_node_idx = trie[curr_node_idx].children[idx];
            last_valid_index = trie[curr_node_idx].best_index;
        }
        return last_valid_index;
    }

public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        // Optimize standard input/output streams for LeetCode runtime evaluation
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        // Step 1: Precompute global default optimal index for absolute mismatches
        int default_best = 0;
        for (int i = 1; i < wordsContainer.size(); ++i) {
            if (wordsContainer[i].length() < wordsContainer[default_best].length()) {
                default_best = i;
            }
        }

        // Reset the memory arena and instantiate the root node
        trie.clear();
        trie.push_back(TrieNode(default_best));

        // Step 2: Populate the Trie
        for (int i = 0; i < wordsContainer.size(); ++i) {
            insert(wordsContainer[i], i, wordsContainer);
        }

        // Step 3: Resolve Query Constraints
        vector<int> ans;
        ans.reserve(wordsQuery.size());
        for (const string& query : wordsQuery) {
            ans.push_back(search(query));
        }

        return ans;
    }
};