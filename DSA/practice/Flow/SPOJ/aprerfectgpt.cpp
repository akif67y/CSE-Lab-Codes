#include <iostream>
#include <vector>
#include <cstring> // for memset

using namespace std;

const int MAXN = 1005;

vector<int> adj[MAXN];
int match[MAXN];      // Stores the partner of node i
bool vis[MAXN];       // Visited array for the matching DFS
int color[MAXN];      // To store the color (0 or 1) of each node

// DFS to 2-color the graph (Split into Bipartite Sets)
void colorGraph(int u, int c) {
    color[u] = c;
    for (int v : adj[u]) {
        if (color[v] == -1) {
            colorGraph(v, 1 - c);
        }
    }
}

// DFS for Maximum Bipartite Matching (Kuhn's Algorithm)
bool dfs_match(int u) {
    for (int v : adj[u]) {
        // If v is not visited in this matching attempt
        if (!vis[v]) {
            vis[v] = true;
            // If v is not matched OR we can find a new partner for v's current partner
            if (match[v] == -1 || dfs_match(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

void solve(int t) {
    int N, M;
    cin >> N >> M;

    // Reset data structures
    for (int i = 0; i <= N; i++) {
        adj[i].clear();
        color[i] = -1; 
        match[i] = -1;
    }

    // Read Input
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Step 1: Divide vertices into two sets (Color 0 and Color 1)
    // We must loop 1 to N because the graph might be disconnected (Forest)
    for (int i = 1; i <= N; i++) {
        if (color[i] == -1) {
            colorGraph(i, 0);
        }
    }

    // Step 2: Calculate Maximum Matching
    int matching_count = 0;
    for (int i = 1; i <= N; i++) {
        // We only try to match nodes from "Set 0" to "Set 1" to avoid double counting
        if (color[i] == 0) {
            // Reset visited array for each matching attempt
            memset(vis, 0, sizeof(vis));
            if (dfs_match(i)) {
                matching_count++;
            }
        }
    }

    // Step 3: Konig's Theorem
    // Max Independent Set = Total Nodes - Max Matching
    int ans = N - matching_count;

    cout << "Case " << t << ": " << ans << endl;
}

int main() {
    // Optimize I/O operations
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        solve(i);
    }
}