/*
Problem: Minimum Jumps to Reach End with Prime Teleportation
Link: https://leetcode.com/problems/minimum-jumps-to-reach-end-via-prime-teleportation/

Date: 2026-05-08
Difficulty: Hard
Tags: Array, BFS, Sieve of Eratosthenes, Number Theory, Graph

🧠 Intuition:

1. Shortest Path: Since we need the minimum number of jumps in an unweighted graph 
   (each step/teleport counts as 1), Breadth-First Search (BFS) is the optimal strategy[cite: 1, 2].

2. The Teleportation Challenge: If nums[i] is a prime p, you can jump to any index j 
   where nums[j] is a multiple of p. A naive graph construction would create O(N^2) 
   edges if many numbers share the same prime factor (like the prime 2 in an array of 
   even numbers), which is too slow for N = 10^5[cite: 1, 2].

3. Optimization via Prime Mapping: Instead of connecting every index to every other 
   index, we connect each prime factor to a list of indices that contain it. 
   To prevent redundant work, once we "use" a prime factor to explore its connected 
   indices, we mark that prime as visited. This ensures we traverse each index 
   and each prime factor association only once, keeping the complexity linear[cite: 1, 2].

--------------------------------------------------------

⚙️ Approach:

1. Sieve of Eratosthenes (SPF): 
   Precompute the Smallest Prime Factor (SPF) for all numbers up to 1,000,000. 
   This allows us to factorize any nums[i] into its prime components in logarithmic 
   time O(log(nums[i]))[cite: 1, 2].

2. Factor-to-Index Map: 
   Create an adjacency list where the key is a prime factor and the value is a list 
   of all indices in 'nums' that are divisible by that prime[cite: 1, 2].

3. BFS Implementation:
   - Use a queue for BFS, starting at index 0.
   - Maintain a `dist` array to track the minimum jumps to each index.
   - For every index `i` popped from the queue:
     a. Check adjacent moves: i + 1 and i - 1.
     b. If nums[i] is prime: Retrieve all indices mapped to this prime factor 
        that haven't been visited yet, add them to the queue, and mark the 
        prime as "used" to avoid O(N^2) cycles[cite: 1, 2].

--------------------------------------------------------

⏱ Time Complexity:

O(M log log M + N log M)

- Sieve of Eratosthenes: O(M log log M), where M is the maximum value in nums (10^6)[cite: 1, 2].
- Factorization and Mapping: O(N log M), as each number has at most log(M) factors[cite: 1, 2].
- BFS Traversal: O(N + M), because each index and each prime factor is processed once[cite: 1, 2].

📦 Space Complexity:

O(M + N log M)

- SPF array: O(M)[cite: 1, 2].
- Prime-to-Indices mapping: O(N log M) to store index lists for factors[cite: 1, 2].
- BFS queue and distance array: O(N)[cite: 1, 2].

*/

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minJumps(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;

        int max_val = *max_element(nums.begin(), nums.end());

        // 1. Precompute Smallest Prime Factor (SPF) for fast factorization
        vector<int> spf(max_val + 1);
        for (int i = 2; i <= max_val; ++i) spf[i] = i;
        for (int i = 2; i * i <= max_val; ++i) {
            if (spf[i] == i) {
                for (int j = i * i; j <= max_val; j += i)
                    if (spf[j] == j) spf[j] = i;
            }
        }

        // 2. Map each prime to the indices whose values are divisible by it
        vector<vector<int>> prime_to_indices(max_val + 1);
        for (int i = 0; i < n; ++i) {
            int temp = nums[i];
            while (temp > 1) {
                int p = spf[temp];
                prime_to_indices[p].push_back(i);
                while (temp % p == 0) temp /= p; // Skip duplicate prime factors
            }
        }

        // 3. BFS for Shortest Path
        queue<int> q;
        q.push(0);
        
        vector<int> dist(n, -1);
        dist[0] = 0;
        
        // Track which primes have already been "activated" to avoid re-scanning lists
        vector<bool> prime_used(max_val + 1, false);

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            if (curr == n - 1) return dist[curr];

            // --- Rule 1: Adjacent Steps ---
            for (int next_idx : {curr - 1, curr + 1}) {
                if (next_idx >= 0 && next_idx < n && dist[next_idx] == -1) {
                    dist[next_idx] = dist[curr] + 1;
                    q.push(next_idx);
                }
            }

            // --- Rule 2: Prime Teleportation ---
            // We can only teleport IF the current number itself is prime
            int p = nums[curr];
            if (p > 1 && spf[p] == p && !prime_used[p]) {
                prime_used[p] = true; // Mark prime as used
                for (int target_idx : prime_to_indices[p]) {
                    if (dist[target_idx] == -1) {
                        dist[target_idx] = dist[curr] + 1;
                        q.push(target_idx);
                    }
                }
            }
        }

        return -1; // Should not be reached per constraints
    }
};