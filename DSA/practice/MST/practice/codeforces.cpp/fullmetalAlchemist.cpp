#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

// Function to calculate the weight (distance) between two rows
// Complexity: O(M)
int calculate_distance(const string& s1, const string& s2, int m) {
    int max_diff = 0;
    for (int i = 0; i < m; ++i) {
        int diff = abs(s1[i] - s2[i]);
        if (diff > max_diff) {
            max_diff = diff;
        }
    }
    return max_diff;
}

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;

    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }

    // Prim's Algorithm Setup
    // min_edge[i] stores the minimum cost to connect node 'i' to the current MST
    vector<int> min_edge(n, INT_MAX);
    vector<bool> visited(n, false);

    // Start from the 0th row (arbitrary start point for MST)
    min_edge[0] = 0;
    
    int max_cost_in_mst = 0;

    // Loop to add N nodes to the MST
    for (int i = 0; i < n; ++i) {
        int u = -1;

        // Step 1: Find the unvisited node with the smallest min_edge value
        // Complexity: O(N)
        for (int v = 0; v < n; ++v) {
            if (!visited[v] && (u == -1 || min_edge[v] < min_edge[u])) {
                u = v;
            }
        }

        // If no reachable node is found (should not happen in this connected graph)
        if (min_edge[u] == INT_MAX) break;

        // Step 2: Include node u in the MST
        visited[u] = true;
        // Track the maximum edge weight encountered so far
        if (min_edge[u] > max_cost_in_mst) {
            max_cost_in_mst = min_edge[u];
        }

        // Step 3: Update distances to adjacent vertices
        // Complexity: O(N * M)
        for (int v = 0; v < n; ++v) {
            if (!visited[v]) {
                int dist = calculate_distance(grid[u], grid[v], m);
                if (dist < min_edge[v]) {
                    min_edge[v] = dist;
                }
            }
        }
    }

    cout << max_cost_in_mst << endl;
}

int main() {
    // Fast I/O is crucial for N=2000
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}