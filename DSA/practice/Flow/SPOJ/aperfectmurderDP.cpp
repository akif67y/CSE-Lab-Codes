#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Maximum number of nodes as per constraints (N <= 1000)
const int MAXN = 1005;

vector<int> adj[MAXN];
int dp[MAXN][2];
bool visited[MAXN];

/*
 * DFS function to compute DP states
 * u: current node
 * p: parent of current node (to avoid going back up the tree)
 */
void dfs(int u, int p) {
    visited[u] = true;
    
    // Base initialization
    dp[u][0] = 0; // If we don't pick u, count starts at 0
    dp[u][1] = 1; // If we pick u, count starts at 1 (u itself)

    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);

            // Transition:
            // If u is NOT picked, we can either pick v or not pick v (take max)
            dp[u][0] += max(dp[v][0], dp[v][1]);

            // If u IS picked, we CANNOT pick v
            dp[u][1] += dp[v][0];
        }
    }
}

void solve(int t) {
    int N, M;
    cin >> N >> M;

    // Clear data for the new test case
    for (int i = 0; i <= N; i++) {
        adj[i].clear();
        visited[i] = false;
    }

    // Read edges
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int total_killed = 0;

    // The graph might be a forest (disconnected trees). 
    // We must run DFS on every unvisited node.
    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            dfs(i, -1);
            // For this component/tree, add the max possible result
            total_killed += max(dp[i][0], dp[i][1]);
        }
    }

    cout << "Case " << t << ": " << total_killed << endl;
}

int main() {
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        solve(i);
    }
    return 0;
}