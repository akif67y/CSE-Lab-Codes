#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1e15;

void solveN3() {
    int n, m;
    cin >> n >> m;

    // D[0] = 0 tickets used, D[1] = 1 ticket used
    vector<vector<long long>> d0(n + 1, vector<long long>(n + 1, INF));
    vector<vector<long long>> d1(n + 1, vector<long long>(n + 1, INF));

    for (int i = 1; i <= n; i++) {
        d0[i][i] = 0;
        d1[i][i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        // Standard edge
        d0[u][v] = min(d0[u][v], (long long)w);
        // Magic Edge: We can use our 1 ticket on this specific edge immediately
        d1[u][v] = 0; 
    }

    // O(N^3) Integrated Floyd-Warshall
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                // Update d0 (Standard FW)
                if (d0[i][k] != INF && d0[k][j] != INF) {
                    d0[i][j] = min(d0[i][j], d0[i][k] + d0[k][j]);
                }

                // Update d1 (Magic Carpet FW)
                // d1[i][j] is the min of:
                // 1. Current d1[i][j]
                // 2. Ticket already used between i and k, then normal k to j
                // 3. Normal i to k, then ticket used between k and j
                if (d1[i][k] != INF && d0[k][j] != INF)
                    d1[i][j] = min(d1[i][j], d1[i][k] + d0[k][j]);
                
                if (d0[i][k] != INF && d1[k][j] != INF)
                    d1[i][j] = min(d1[i][j], d0[i][k] + d1[k][j]);
            }
        }
    }

    // Output d1[i][j] as it represents "at most 1 ticket"
    cout << "Shortest paths using at most 1 ticket:" << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (d1[i][j] >= INF/2) cout << "INF "; // INF/2 to handle slight additions
            else cout << d1[i][j] << " ";
        }
        cout << endl;
    }
}