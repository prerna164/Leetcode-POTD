/*
Problem: Longest Substring of One Repeating Character
Link: LeetCode 2213 - Longest Substring of One Repeating Character

Difficulty: Hard
Tags: String, Segment Tree, Ordered Set

Intuition:
We are given a string `s` and `k` point-update queries. After each query, we need to output the length of the longest substring consisting of a single repeating character.

Since $N, K \le 10^5$, updating the string and rescanning it naively would take $O(N)$ per query, leading to $O(N \cdot K)$ total time (TLE).
This is a dynamic point-update range-query problem on an array, which fits a Segment Tree.

Segment Tree Node Structure:
Each segment tree node for range `[L, R]` stores:
1. `max_len`: Length of the longest repeating character substring fully contained in `[L, R]`.
2. `pref_len`: Length of the longest repeating prefix in `[L, R]`.
3. `suff_len`: Length of the longest repeating suffix in `[L, R]`.
4. `left_char`: The character at index `L`.
5. `right_char`: The character at index `R`.

Merging Two Child Nodes (Left and Right):
When combining `left_child` [L, Mid] and `right_child` [Mid+1, R]:
- The base `max_len` is `max(left_child.max_len, right_child.max_len)`.
- If `left_child.right_char == right_child.left_char`, the repeating suffix of the left child joins with the repeating prefix of the right child across the boundary:
  `max_len = max(max_len, left_child.suff_len + right_child.pref_len)`.
- `pref_len` extends into the right child if the left child consists of a single repeating character.
- `suff_len` extends into the left child if the right child consists of a single repeating character.

---

Approach:

1. Build Segment Tree:
   * Construct the segment tree over `s` of length `N`.

2. Process Queries:
   * For each query `i`, update character at `queryIndices[i]` to `queryCharacters[i]`.
   * The answer after query `i` is simply the `max_len` stored at the root of the segment tree (`tree[1].max_len`).

---

⏱ Time Complexity:
O((N + K) log N)

* Building the segment tree takes O(N) time.
* Each point update takes O(log N) time.
* Total Runtime: O((N + K) log N), well within the execution time limit.

Space Complexity:
O(N) Auxiliary Space

* Segment tree array requires O(4 * N) memory allocation.
*/

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct Node {
    int max_len;
    int pref_len;
    int suff_len;
    char left_char;
    char right_char;
    int len;
};

class SegmentTree {
private:
    int n;
    vector<Node> tree;

    Node merge(const Node& left, const Node& right) {
        Node res;
        res.len = left.len + right.len;
        res.left_char = left.left_char;
        res.right_char = right.right_char;

        res.max_len = max(left.max_len, right.max_len);
        res.pref_len = left.pref_len;
        res.suff_len = right.suff_len;

        // Merge boundary if characters at mid and mid + 1 are identical
        if (left.right_char == right.left_char) {
            res.max_len = max(res.max_len, left.suff_len + right.pref_len);

            if (left.pref_len == left.len) {
                res.pref_len = left.len + right.pref_len;
            }
            if (right.suff_len == right.len) {
                res.suff_len = right.len + left.suff_len;
            }
        }

        return res;
    }

    void build(int node, int start, int end, const string& s) {
        if (start == end) {
            tree[node] = {1, 1, 1, s[start], s[start], 1};
            return;
        }
        int mid = start + (end - start) / 2;
        build(2 * node, start, mid, s);
        build(2 * node + 1, mid + 1, end, s);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int node, int start, int end, int idx, char ch) {
        if (start == end) {
            tree[node] = {1, 1, 1, ch, ch, 1};
            return;
        }
        int mid = start + (end - start) / 2;
        if (idx <= mid) {
            update(2 * node, start, mid, idx, ch);
        } else {
            update(2 * node + 1, mid + 1, end, idx, ch);
        }
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

public:
    SegmentTree(const string& s) {
        n = s.length();
        tree.resize(4 * n);
        build(1, 0, n - 1, s);
    }

    void update(int idx, char ch) {
        update(1, 0, n - 1, idx, ch);
    }

    int getMaxLen() const {
        return tree[1].max_len;
    }
};

class Solution {
public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int k = queryIndices.size();
        vector<int> lengths(k);

        SegmentTree st(s);

        for (int i = 0; i < k; ++i) {
            st.update(queryIndices[i], queryCharacters[i]);
            lengths[i] = st.getMaxLen();
        }

        return lengths;
    }
};