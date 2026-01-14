#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    // Note: The original problem often has multiple test cases
    if (!(cin >> n) || n == 0) return;

    map<string, int> trackVertex;
    for (int i = 1; i <= n; i++) {
        string name;
        cin >> name;
        trackVertex[name] = i;
    }

    // Initialize with a large value
    vector<vector<double>> dist(n + 1, vector<double>(n + 1, 1e15));
    for (int i = 1; i <= n; i++) dist[i][i] = 0;

    cin >> m;
    for (int i = 0; i < m; i++) {
        string u, v;
        double rate;
        cin >> u >> rate >> v;
        // Transform: product > 1 becomes sum of -log(rate) < 0
        dist[trackVertex[u]][trackVertex[v]] = -log(rate);
    }

    // Floyd-Warshall
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    bool yes = false;
    for (int i = 1; i <= n; i++) {
        if (dist[i][i] < -1e-9) { 
            yes = true; 
            break; 
        }
    }

    cout << (yes ? "Yes" : "No") << endl;
}

int main() {
    // You'll likely need a loop for multiple test cases here
    solve();
    return 0;
}