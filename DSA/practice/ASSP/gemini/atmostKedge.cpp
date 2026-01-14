#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1e18;

typedef vector<vector<long long>> Matrix;

Matrix multiply(const Matrix& A, const Matrix& B, int N) {
    Matrix C(N, vector<long long>(N, INF));
    for (int k = 0; k < N; k++) { // Optimized loop order for cache hits
        for (int i = 0; i < N; i++) {
            if (A[i][k] == INF) continue;
            for (int j = 0; j < N; j++) {
                if (B[k][j] == INF) continue;
                C[i][j] = min(C[i][j], A[i][k] + B[k][j]);
            }
        }
    }
    return C;
}

// Binary Exponentiation for Min-Plus Multiplication
Matrix power(Matrix A, int K, int N) {
    Matrix res = A;
    K--; // Start with A^1
    while (K > 0) {
        if (K & 1) res = multiply(res, A, N);
        A = multiply(A, A, N);
        K >>= 1;
    }
    return res;
}


int main() {
    int N, E, K;
    cin >> N >> E >> K;

    Matrix W(N, vector<long long>(N, INF));

    // CRITICAL CHANGE: Set self-loops to 0
    for (int i = 0; i < N; i++) W[i][i] = 0; // just eita update

    for (int i = 0; i < E; i++) {
        int u, v; long long w;
        cin >> u >> v >> w;
        // Keep the minimum weight if there are multiple edges
        W[u][v] = min(W[u][v], w); 
    }

    // Binary Exponentiation O(N^3 log K)
    Matrix res = power(W, K, N);

    cout << res[source][destination];
    return 0;
}