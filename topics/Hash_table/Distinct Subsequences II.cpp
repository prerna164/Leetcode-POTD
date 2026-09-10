/*
Problem: Distinct Subsequences II
Link: LeetCode 940 - Distinct Subsequences II

Difficulty: Hard
Tags: String, Dynamic Programming, Hash Table

Intuition:
Let's consider building subsequences character by character.
When we append a character `c` to all existing distinct subsequences (including the empty string), we generate new subsequences that end with `c`.

If character `c` has never been seen before:
- The number of new distinct subsequences ending in `c` equals (total distinct subsequences so far + 1 for the single character `c` itself).

If character `c` HAS been seen before:
- Appending `c` to existing subsequences will duplicate all subsequences that were previously generated when `c` was last encountered.
- Therefore, the number of NEW unique subsequences added by `c` is:
  `new_subsequences = (total_distinct_so_far + 1) - previous_ends_with[c]`

Instead of tracking global counts and subtracting duplicates, we can maintain an array `last[26]` where `last[c]` stores the exact count of distinct subsequences that END with character `c`.

At each step for character `c`:
- `new_count_ending_with_c = (total_distinct_subsequences_so_far + 1) % MOD`
- Update global total: `total = (total + new_count_ending_with_c - last[c] + MOD) % MOD`
- Update character record: `last[c] = new_count_ending_with_c`

---

Approach:

1. Maintain `last[26]` initialized to `0` to keep track of distinct subsequences ending with each letter.
2. Maintain `total` initialized to `0` representing total distinct non-empty subsequences.
3. For each character `ch` in `s`:
   - Compute `added = (total + 1) % MOD`.
   - Update `total = (total + added - last[ch - 'a'] + MOD) % MOD`.
   - Record `last[ch - 'a'] = added`.
4. Return `total`.

---

⏱ Time Complexity:
O(N)

* `N = s.length()`.
* Single pass over string `s` with $O(1)$ operations per character.
* Total Runtime: O(N) time.

Space Complexity:
O(1) Auxiliary Space

* Fixed size array `last[26]` of size 26.
*/

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int distinctSubseqII(string s) {
        // Optimize standard I/O streams for competitive programming execution speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        const int MOD = 1e9 + 7;
        vector<long long> last(26, 0);
        long long total = 0;

        for (char c : s) {
            int idx = c - 'a';
            long long new_count = (total + 1) % MOD;
            
            // Update global total by adding new subsequences and subtracting duplicates
            total = (total + new_count - last[idx] + MOD) % MOD;
            
            // Record the new count of subsequences ending in 'c'
            last[idx] = new_count;
        }

        return total;
    }
};