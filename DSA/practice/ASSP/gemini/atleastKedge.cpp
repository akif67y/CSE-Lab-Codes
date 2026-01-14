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

    Matrix W(N, vector<long long>(N, INF));
    Matrix FW(N, vector<long long>(N, INF));

    for (int i = 0; i < N; i++) FW[i][i] = 0;

    for (int i = 0; i < E; i++) {
        int u, v; long long w;
        cin >> u >> v >> w;
        W[u][v] = min(W[u][v], w);
        FW[u][v] = min(FW[u][v], w);
    }

    // 1. Calculate Standard Floyd-Warshall (Any number of edges)
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (FW[i][k] < INF && FW[k][j] < INF)
                    FW[i][j] = min(FW[i][j], FW[i][k] + FW[k][j]);
            }
        }
    }

    // 2. Calculate Exactly K edges using Binary Exponentiation
    Matrix exactlyK = power(W, K, N);

    // 3. Combine: Path = (Exactly K) + (Standard Shortest Path)
    long long final_min = INF;
    int start_node = 0, end_node = N-1;

    for (int v = 0; v < N; v++) {
        if (exactlyK[start_node][v] < INF && FW[v][end_node] < INF) {
            final_min = min(final_min, exactlyK[start_node][v] + FW[v][end_node]);
        }
    }

    cout << (final_min >= INF ? -1 : final_min);
    return 0;
}