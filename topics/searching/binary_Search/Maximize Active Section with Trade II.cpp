/*
Problem: Maximize Active Section with Trade II
Link: LeetCode - Max Active Sections After Trade II

Date: 2026-07-23
Difficulty: Hard
Tags: Array, String, Binary Search, Sparse Table, Range Minimum/Maximum Query

Intuition:
A valid trade requires picking a block of '1's surrounded by '0's, converting it to '0's (which merges its left and right adjacent '0' blocks), and then converting the merged '0' block to '1's.

For a query range [l, r]:
1. The tradeable '1' block must fall strictly inside (l, r) so that it is surrounded by '0's within the substring.
2. The gain added to the overall active sections is:
   (clipped length of left '0' block inside [l, r]) + (clipped length of right '0' block inside [l, r])
3. For '1' blocks completely interior to [l, r] whose adjacent '0' blocks are also fully inside [l, r], their gain is unclipped. We can precalculate these gains and query their maximum in O(1) time using a Sparse Table.
4. For boundary '1' blocks near l or r, their adjacent '0' blocks might be clipped by the query boundaries [l, r], so we explicitly compute their clipped gain.

---

Approach:

1. Identify Valid '1' Blocks:
   * Iterate through string s to locate all contiguous blocks of '1's that are flanked by '0's on both sides.
   * Record each block's start/end indices and the boundaries of its surrounding left and right '0' blocks.

2. Precompute Gains & Sparse Table:
   * Calculate the full (unclipped) gain for every identified '1' block as `left_zero_length + right_zero_length`.
   * Build a Range Maximum Query (RMQ) Sparse Table over these gains to handle queries in O(1).

3. Process Queries:
   * For each query [l, r], use binary search (`std::upper_bound`) to identify the candidate '1' blocks that lie inside (l, r).
   * Query the interior blocks via Sparse Table for their maximum unclipped gain.
   * Calculate the clipped gain for boundary blocks (the first and last candidate blocks) by intersecting their adjacent '0' blocks with [l, r].
   * The answer for each query is `(total '1's in s) + maxGain`.

---

⏱ Time Complexity:
O(N log N + Q log N)

* Identifying blocks and building the Sparse Table takes O(N log N) time, where N = |s|.
* Each query uses binary search to find candidate blocks in O(log N) time and performs an O(1) Sparse Table lookup.
* Across Q queries, overall runtime is O(N log N + Q log N).

Space Complexity:
O(N log N) Auxiliary Space

* The Sparse Table stores log(N) levels for up to N elements, requiring O(N log N) space.
*/

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
    // Internal Sparse Table for O(1) Range Maximum Query
    class SparseTable {
        int n;
        vector<vector<int>> st;
    public:
        SparseTable() : n(0) {}
        void build(const vector<int>& nums) {
            n = nums.size();
            if (n == 0) return;
            int max_log = 32 - __builtin_clz(n);
            st.assign(max_log, vector<int>(n, 0));
            
            for (int j = 0; j < n; ++j) {
                st[0][j] = nums[j];
            }
            
            for (int i = 1; i < max_log; ++i) {
                for (int j = 0; j + (1 << i) <= n; ++j) {
                    st[i][j] = max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
                }
            }
        }

        int query(int l, int r) const {
            if (n == 0 || l > r || l < 0 || r >= n) return 0;
            int i = 31 - __builtin_clz(r - l + 1);
            return max(st[i][l], st[i][r - (1 << i) + 1]);
        }
    };

    struct OneBlock {
        int start;
        int end;
        int leftZeroStart;
        int leftZeroEnd;
        int rightZeroStart;
        int rightZeroEnd;
    };

public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = s.length();
        int totalOnes = 0;
        for (char c : s) {
            if (c == '1') totalOnes++;
        }

        // Step 1: Identify all '1' blocks surrounded by '0's
        vector<OneBlock> oneBlocks;
        for (int i = 0; i < n; ) {
            if (s[i] == '1') {
                int start = i;
                while (i < n && s[i] == '1') i++;
                int end = i - 1;

                if (start > 0 && end < n - 1 && s[start - 1] == '0' && s[end + 1] == '0') {
                    // Find bounds of left '0' block
                    int lzEnd = start - 1;
                    int lzStart = lzEnd;
                    while (lzStart > 0 && s[lzStart - 1] == '0') lzStart--;

                    // Find bounds of right '0' block
                    int rzStart = end + 1;
                    int rzEnd = rzStart;
                    while (rzEnd + 1 < n && s[rzEnd + 1] == '0') rzEnd++;

                    oneBlocks.push_back({start, end, lzStart, lzEnd, rzStart, rzEnd});
                }
            } else {
                i++;
            }
        }

        int m = oneBlocks.size();
        vector<int> unclippedGains(m);
        vector<int> blockStarts(m);
        for (int i = 0; i < m; ++i) {
            int leftLen = oneBlocks[i].leftZeroEnd - oneBlocks[i].leftZeroStart + 1;
            int rightLen = oneBlocks[i].rightZeroEnd - oneBlocks[i].rightZeroStart + 1;
            unclippedGains[i] = leftLen + rightLen;
            blockStarts[i] = oneBlocks[i].start;
        }

        // Step 2: Build Sparse Table over unclipped gains
        SparseTable st;
        st.build(unclippedGains);

        vector<int> ans;
        ans.reserve(queries.size());

        // Step 3: Process queries independently
        for (const auto& q : queries) {
            int l = q[0];
            int r = q[1];

            auto itStart = upper_bound(blockStarts.begin(), blockStarts.end(), l);
            int firstIdx = distance(blockStarts.begin(), itStart);

            int maxGain = 0;

            if (firstIdx < m) {
                int low = firstIdx, high = m - 1, lastIdx = -1;
                while (low <= high) {
                    int mid = low + (high - low) / 2;
                    if (oneBlocks[mid].end < r) {
                        lastIdx = mid;
                        low = mid + 1;
                    } else {
                        high = mid - 1;
                    }
                }

                if (lastIdx >= firstIdx) {
                    // Query fully interior unclipped blocks
                    int interiorL = firstIdx + 1;
                    int interiorR = lastIdx - 1;

                    if (oneBlocks[firstIdx].leftZeroStart < l) interiorL = max(interiorL, firstIdx + 1);
                    else interiorL = firstIdx;

                    if (oneBlocks[lastIdx].rightZeroEnd > r) interiorR = min(interiorR, lastIdx - 1);
                    else interiorR = lastIdx;

                    if (interiorL <= interiorR) {
                        maxGain = max(maxGain, st.query(interiorL, interiorR));
                    }

                    // Query boundary blocks with range clipping
                    for (int idx : {firstIdx, lastIdx}) {
                        if (idx >= firstIdx && idx <= lastIdx) {
                            int lzS = max(l, oneBlocks[idx].leftZeroStart);
                            int lzE = oneBlocks[idx].leftZeroEnd;
                            int leftLen = max(0, lzE - lzS + 1);

                            int rzS = oneBlocks[idx].rightZeroStart;
                            int rzE = min(r, oneBlocks[idx].rightZeroEnd);
                            int rightLen = max(0, rzE - rzS + 1);

                            maxGain = max(maxGain, leftLen + rightLen);
                        }
                    }
                }
            }

            ans.push_back(totalOnes + maxGain);
        }

        return ans;
    }
};