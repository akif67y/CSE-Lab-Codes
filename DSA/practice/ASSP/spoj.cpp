#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define INF 1e18

void solve() {
    int n, caseNum = 1;

    // 1. Loop until n is 0
    while (cin >> n && n != 0) {
        map<string, int> trackVertex;
        
        // Read currency names and map them to indices
        for (int i = 1; i <= n; i++) {
            string temp;
            cin >> temp;
            trackVertex[temp] = i;
        }

        // 2. Initialize the answer matrix
        // We use 0.0 because it's the neutral element for maximum product
        vector<vector<double>> answer(n + 1, vector<double>(n + 1, -INF));

        // Each currency starts at 1:1 ratio with itself
        for (int i = 1; i <= n; i++) {
            answer[i][i] = 1.0;
        }

        int m;
        cin >> m;
        for (int i = 0; i < m; i++) {
            string u, v;
            double w;
            cin >> u >> w >> v;
            // Map names to their indices and store the rate
            answer[trackVertex[u]][trackVertex[v]] = max(w,answer[trackVertex[u]][trackVertex[v]]);
        }

        // 3. Floyd-Warshall for Multiplicative Paths
        // answer[i][j] stores the maximum exchange rate from currency i to j
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    if (answer[i][k] != INF && answer[k][j] != INF) {
                        answer[i][j] = max(answer[i][j], answer[i][k] * answer[k][j]);
                    }
                }
            }
        }

        // 4. Check for Arbitrage (any diagonal > 1.0)
        bool yes = false;
        for (int i = 1; i <= n; i++) {
            if (answer[i][i] > 1.0 - 1e-18) {
                yes = true;
                break;
            }
        }

        // 5. Output with specific formatting
        cout << "Case " << caseNum++ << ": " << (yes ? "Yes" : "No") << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}