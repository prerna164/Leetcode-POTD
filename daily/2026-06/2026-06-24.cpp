/*
Problem: Number of ZigZag Arrays II
Link: Matrix Exponentiation for ZigZag Constraints

Date: 2026-06-24
Difficulty: Hard
Tags: Dynamic Programming, Matrix Exponentiation, Math

Intuition:
In this variation of the problem, the length of the array $n$ can be up to $10^9$, while the range size $M = r - l + 1$ is relatively small ($M \le 75$). This large constraint on $n$ with a small $M$ strongly suggests using **Matrix Exponentiation**.

Let $M = r - l + 1$. We have $2M$ states for a given position in the array:
- $M$ states representing that the last step was an increase (`up[v]`).
- $M$ states representing that the last step was a decrease (`down[v]`).

For a state transition from length $k$ to $k+1$:
- $up_{new}[v] = \sum_{prev < v} down[prev]$
- $down_{new}[v] = \sum_{prev > v} up[prev]$

Because these transitions are linear combinations of the previous state values, we can represent the transition using a matrix $T$ of size $2M \times 2M$:
$$\begin{pmatrix} \mathbf{up}_{new} \\ \mathbf{down}_{new} \end{pmatrix} = T \times \begin{pmatrix} \mathbf{up} \\ \mathbf{down} \end{pmatrix}$$

The base state at length $n = 2$ is:
- $up[v] = v$ (the number of choices strictly smaller than $v$)
- $down[v] = M - 1 - v$ (the number of choices strictly greater than $v$)

To find the state configuration at length $n$, we multiply our base vector by the transition matrix raised to the power of $n-2$:
$$\text{Final State} = T^{n-2} \times \text{Base Vector}$$

We can calculate $T^{n-2} \pmod{10^9 + 7}$ efficiently in $O(M^3 \log n)$ time using binary matrix exponentiation.

---

Approach:

1. Base Configuration setup:
   * Calculate $M = r - l + 1$.
   * Create a base vector `V` of size $2M$, filling the first $M$ indices with $v$ and the next $M$ indices with $M - 1 - v$.

2. Transition Matrix Design:
   * Construct a $2M \times 2M$ grid matrix `T`.
   * For row $v$ ($0 \le v < M$), set `T[v][M + prev] = 1` for all $0 \le prev < v$.
   * For row $M + v$ ($0 \le v < M$), set `T[M + v][prev] = 1` for all $v < prev < M$.

3. Binary Matrix Exponentiation:
   * Raise matrix `T` to the power of $n - 2$ using modular matrix multiplication techniques.
   * Multiply the exponentiated matrix by the base vector `V` to obtain the final states vector.
   * Accumulate all entries in the final vector to return the answer modulo $10^9 + 7$.

---

⏱ Time Complexity:
O(M^3 * log N)

* Matrix multiplication of a $2M \times 2M$ matrix takes $O((2M)^3) = O(8M^3)$ operations.
* Binary exponentiation requires repeating this multiplication $\log n$ times.
* With $M \le 75$ and $n \le 10^9$, the total operations are roughly $\approx 8 \times 75^3 \times 30 \approx 10^8$, which executes comfortably within 0.15 seconds in C++.

Space Complexity:
O(M^2) Auxiliary Space

* The memory is primarily occupied by the $2M \times 2M$ dimension matrices used during multiplication, taking negligible storage.
*/

#include <vector>
#include <iostream>

using namespace std;

class Solution {
private:
    long long MOD = 1000000007;

    // Helper function to multiply two square matrices
    vector<vector<long long>> multiply(const vector<vector<long long>>& A, const vector<vector<long long>>& B, int size) {
        vector<vector<long long>> C(size, vector<long long>(size, 0));
        for (int i = 0; i < size; ++i) {
            for (int k = 0; k < size; ++k) {
                if (A[i][k] == 0) continue;
                for (int j = 0; j < size; ++j) {
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
                }
            }
        }
        return C;
    }

    // Helper function for matrix binary modular exponentiation
    vector<vector<long long>> powerMatrix(vector<vector<long long>> A, long long p, int size) {
        vector<vector<long long>> res(size, vector<long long>(size, 0));
        for (int i = 0; i < size; ++i) res[i][i] = 1; // Identity Matrix

        while (p > 0) {
            if (p % 2 == 1) res = multiply(res, A, size);
            A = multiply(A, A, size);
            p /= 2;
        }
        return res;
    }

public:
    int zigZagArrays(int n, int l, int r) {
        // Optimize standard I/O streams for competitive programming speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int M = r - l + 1;
        int size = 2 * M;

        // Base vector for length = 2
        vector<long long> base(size, 0);
        for (int v = 0; v < M; ++v) {
            base[v] = v;             // up[v]: elements < v
            base[M + v] = M - 1 - v; // down[v]: elements > v
        }

        // Construct the structural transition matrix
        vector<vector<long long>> T(size, vector<long long>(size, 0));
        for (int v = 0; v < M; ++v) {
            // next_up[v] relies on down[prev] for prev < v
            for (int prev = 0; prev < v; ++prev) {
                T[v][M + prev] = 1;
            }
            // next_down[v] relies on up[prev] for prev > v
            for (int prev = v + 1; prev < M; ++prev) {
                T[M + v][prev] = 1;
            }
        }

        // Exponentiate the transition matrix to the power of (n - 2)
        T = powerMatrix(T, n - 2, size);

        // Multiply the resulting transformation matrix by our base vector
        long long total_valid_arrays = 0;
        for (int i = 0; i < size; ++i) {
            long long current_state_val = 0;
            for (int j = 0; j < size; ++j) {
                current_state_val = (current_state_val + T[i][j] * base[j]) % MOD;
            }
            total_valid_arrays = (total_valid_arrays + current_state_val) % MOD;
        }

        return total_valid_arrays;
    }
};