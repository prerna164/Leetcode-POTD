/*
Problem: Check if Strings Can be Made Equal
Link: https://leetcode.com/problems/check-if-strings-can-be-made-equal/

Date: 2026-03-30
Difficulty: Medium
Tags: String, Hashing

-----------------------------------------------------

🧠 Intuition:
- We can swap characters only between indices having same parity.
- So even indices form one group and odd indices form another.
- We can rearrange freely within each group.

-----------------------------------------------------

⚙️ Approach:
1. Count frequency of characters at even indices in both strings.
2. Count frequency of characters at odd indices in both strings.
3. Compare both frequencies.
4. If both match → return true.

-----------------------------------------------------

⏱ Time Complexity:
O(n)

📦 Space Complexity:
O(1)

-----------------------------------------------------
*/
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool checkStrings(string s1, string s2) {
        int n = s1.size();

        vector<int> even1(26, 0), odd1(26, 0);
        vector<int> even2(26, 0), odd2(26, 0);

        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) {
                even1[s1[i] - 'a']++;
                even2[s2[i] - 'a']++;
            } else {
                odd1[s1[i] - 'a']++;
                odd2[s2[i] - 'a']++;
            }
        }

        return (even1 == even2) && (odd1 == odd2);
    }
};