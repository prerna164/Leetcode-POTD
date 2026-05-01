/*
Problem: Rotate Function
Link: LeetCode 396

Date: 2026-05-01
Difficulty: Medium
Tags: Array, Math, Prefix Sum, Recurrence Relation

🧠 Intuition:

At first glance, the problem asks us to calculate F(k) for every clockwise rotation
of the array and return the maximum among all values.

The direct thought is:
- Rotate the array each time
- Recalculate the weighted sum again

But that would be very expensive because:
there are n possible rotations and each rotation requires O(n) work.

So total O(n²), which will not work for n = 10^5.

--------------------------------------------------------
The key observation is:

When we rotate the array clockwise by 1 position,
all elements shift one step to the right.

That means:
every element's multiplier increases by +1.

So if we know the total sum of all elements,
then one full shift seems like adding totalSum once.

However, one special thing happens:

the last element jumps from multiplier (n-1) to multiplier 0.

So we added +1 multiplier to it along with everyone else,
but in reality its contribution is removed from the end and comes to the front.

Thus we need to subtract n * movedElement.

This gives us a recurrence relation:

F(k) = F(k-1) + totalSum - n * nums[n-k]

Meaning:
instead of recalculating every rotation from scratch,
we can derive current rotation value from previous rotation value in O(1).

This reduces the whole problem to linear time.

⚙️ Approach:

1. Compute totalSum of all elements in the array.

2. Compute F(0):
   weighted sum without any rotation.

3. Initialize:
   curr = F(0)
   ans = F(0)

4. For every rotation k from 1 to n-1:
   - the element coming to front is nums[n-k]
   - use recurrence:
     curr = curr + totalSum - n * nums[n-k]
   - update ans = max(ans, curr)

5. Return ans.

--------------------------------------------------------
Why recurrence works:

Suppose:

F(0) = 0*a0 + 1*a1 + 2*a2 + ... + (n-1)*a(n-1)

After one clockwise rotation:

[a(n-1), a0, a1, a2, ...]

Now every old element gets index +1,
so total contribution increases by totalSum.

But a(n-1) was previously multiplied by (n-1),
and now it is multiplied by 0.

Hence we must subtract n * a(n-1).

Therefore:

F(1) = F(0) + totalSum - n*a(n-1)

Similarly generalized:

F(k) = F(k-1) + totalSum - n*nums[n-k]

⏱ Time Complexity:

O(n)

- One pass to compute totalSum and F(0)
- One pass to compute all remaining F(k)

Total linear traversal only.

📦 Space Complexity:

O(1)

Only a few variables are used.
No extra array or DP table required.

*/

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxRotateFunction(vector<int>& nums) {
        int n = nums.size();

        long long totalSum = 0;
        long long f0 = 0;

        // Step 1: Compute total sum and F(0)
        for (int i = 0; i < n; i++) {
            totalSum += nums[i];
            f0 += 1LL * i * nums[i];
        }

        long long ans = f0;
        long long curr = f0;

        // Step 2: Use recurrence to calculate all F(k)
        for (int k = 1; k < n; k++) {
            curr = curr + totalSum - 1LL * n * nums[n - k];
            ans = max(ans, curr);
        }

        return (int)ans;
    }
};