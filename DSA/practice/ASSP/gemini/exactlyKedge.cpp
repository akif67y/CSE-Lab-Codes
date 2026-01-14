#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1e18; // Use a large value for infinity

// Function to perform one step of Min-Plus Multiplication
// This extends a path of 'm-1' edges by 1 edge to get 'm' edges
vector<vector<long long>> multiply(const vector<vector<long long>>& A, 
                                   const vector<vector<long long>>& B, int N) {
    vector<vector<long long>> C(N, vector<long long>(N, INF));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                if (A[i][k] != INF && B[k][j] != INF) {
                    C[i][j] = min(C[i][j], A[i][k] + B[k][j]);
                }
            }
        }
    }
    return C;
}

int main() {
    int N, E, K;
    cin >> N >> E >> K;

    // Weight matrix (Initial state: exactly 1 edge)
    vector<vector<long long>> W(N, vector<long long>(N, INF));

    for (int i = 0; i < E; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        // Using 0-indexed nodes
        W[u][v] = min(W[u][v], w); 
    }

    // Result matrix starts as the weight matrix (exactly 1 edge)
    vector<vector<long long>> res = W;

    // We already have paths of length 1, so we need K-1 more multiplications
    for (int m = 1; m < K; m++) {
        res = multiply(res, W, N);
    }

    // Output shortest path from node 0 to node N-1 with exactly K edges
    if (res[0][N - 1] == INF) cout << "No path";
    else cout << res[0][N - 1];

    return 0;
}