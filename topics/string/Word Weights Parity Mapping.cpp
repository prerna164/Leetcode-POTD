/*
Problem: Word Weights Parity Mapping
Link: Custom Character Weights Transformation

Date: 2026-06-13
Difficulty: Easy-Medium
Tags: String, Array, Math, Simulation

Intuition:
The problem requires us to process an array of strings, calculate a numerical weight score for each word based on a given 26-element configuration array, and map the resulting remainder to a character under a custom reverse alphabetical scheme.

Let's break down the transformation steps for an individual word:
1. Character Weight Lookup: For a lowercase English character `c`, its position in the standard alphabet is derived via zero-indexed offset logic: `idx = c - 'a'`. The corresponding weight is retrieved directly from `weights[idx]`.
2. Word Total & Modular Reduction: Summing up these custom letter values yields the word's raw scalar metric. Taking this total modulo 26 confines the state space down to an integer value `R` bounded tightly within the interval [0, 25].
3. Reverse Mapping Conversion: The problem statement explicitly defines a reverse alphabetical mapping layout:
     0  -> 'z'
     1  -> 'y'
     2  -> 'y' - 1 = 'x'
     ...
     25 -> 'a'
   Mathematically, this maps any reduction remainder `R` to its relative offset backward from the boundary pivot 'z'. Thus, the mapped character is computed explicitly via:
     Mapped Character = 'z' - R

Iterating through all words in sequential order and appending each mapped token yields the final concatenated answer.

---

Approach:

1. Initialization:
   * Instantiate an empty result string `res` to hold the output characters.
   * Pre-reserve space inside `res` to match `words.size()` to eliminate vector resizing reallocations.

2. Loop and Cumulative Calculation:
   * Iterate through each string element inside the `words` array.
   * For each string, use an accumulation tracking variable `total_weight = 0`.
   * Loop through every character in the active string, map the character to its 0-25 index array position, and add `weights[idx]` to `total_weight`.

3. Modulo Extraction and Character Shift:
   * Reduce the computed raw sum using the equation: `remainder = total_weight % 26`.
   * Derive the encoded output token by offsetting the baseline zero-state anchor: `char mapped_char = 'z' - remainder`.
   * Push `mapped_char` onto the building answer payload.

---

⏱ Time Complexity:
O(N * L)

* Let N be the total number of words in the array (`words.size()`), and L represent the maximum length of an individual word (`words[i].length()`).
* For each word, we iterate through its individual characters, bounded tightly by L <= 10.
* Character retrieval, modulo reduction, and character mapping math transformations occur in strict O(1) constant time.
* The overall system executes in total time scaling strictly bounded by O(N * L), running comfortably well under 1-2 milliseconds for the given constraints.

Space Complexity:
O(1) Auxiliary Space

* The computation processes strings sequentially utilizing primitive integer loops and requires no supplementary internal data configurations like hash maps or temporary vectors.
* Excluding the memory footprint required to assemble the actual output response string (which takes O(N) memory), the internal operational auxiliary space overhead stays purely constant at O(1).
*/

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
    string mapWordWeights(vector<string>& words, vector<int>& weights) {
        // Optimize standard I/O streams for competitive programming speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        string res = "";
        res.reserve(words.size());

        // Process each word sequence iteratively
        for (const string& word : words) {
            long long total_weight = 0;

            // Step 1: Accumulate total custom weight for the current word
            for (char c : word) {
                int letter_idx = c - 'a';
                total_weight += weights[letter_idx];
            }

            // Step 2: Extract modular remainder over the 26-character bounds
            int remainder = total_weight % 26;

            // Step 3: Map using reverse alphabetical layout (0 -> 'z', 1 -> 'y', ..., 25 -> 'a')
            char mapped_char = 'z' - remainder;

            // Append mapped character sequence directly to output container
            res.push_back(mapped_char);
        }

        return res;
    }
};