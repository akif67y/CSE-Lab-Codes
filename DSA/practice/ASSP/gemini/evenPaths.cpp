#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Using a large value for Infinity. 
// Be careful not to use LLONG_MAX to avoid overflow during addition.
const long long INF = 1e15; 

/**
 * Problem: The "Even" Commute
 * Technique: State-Space Expansion with Floyd-Warshall
 */
void solve() {
    int n, m;
    cout << "Enter number of cities (N) and roads (M): ";
    cin >> n >> m;

    // We expand the graph to 2*N nodes.
    // Index 1 to n: Even state
    // Index n+1 to 2n: Odd state
    int totalNodes = 2 * n;
    vector<vector<long long>> dist(totalNodes + 1, vector<long long>(totalNodes + 1, INF));

    // Distance to self is 0
    for (int i = 1; i <= totalNodes; i++) {
        dist[i][i] = 0;
    }

    cout << "Enter roads (u v weight):" << endl;
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;

        // u_even -> v_odd (u -> v+n)
        dist[u][v + n] = min(dist[u][v + n], w);
        // u_odd -> v_even (u+n -> v)
        dist[u + n][v] = min(dist[u + n][v], w);

        // If the graph is undirected, add the reverse transitions:
        dist[v][u + n] = min(dist[v][u + n], w);
        dist[v + n][u] = min(dist[v + n][u], w);
    }

    // Standard Floyd-Warshall Algorithm
    for (int k = 1; k <= totalNodes; k++) {
        for (int i = 1; i <= totalNodes; i++) {
            for (int j = 1; j <= totalNodes; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    int s, d;
    cout << "Enter source (S) and destination (D): ";
    cin >> s >> d;

    // We want the distance from S_even to D_even.
    // In our indexing, S_even is 's' and D_even is 'd'.
    long long result = dist[s][d];

    if (result >= INF) {
        cout << "No even-length path exists." << endl;
    } else {
        cout << "Shortest even-length path weight: " << result << endl;
    }
}

int main() {
    solve();
    return 0;
}