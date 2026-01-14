#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

const long long INF = 1e18; // Use a safe infinity value

void solve() {
    int N, M, K;
    
    // Example Input hardcoded for demonstration
    // N = 3 nodes, M = 3 edges, K = 2 hops
    N = 3; 
    M = 3;
    K = 2;

    // Adjacency Matrix to store edge weights
    // cost[i][j] stores the weight of edge i -> j
    vector<vector<long long>> cost(N + 1, vector<long long>(N + 1, INF));

    // Input Edges: (u, v, weight)
    // 1 -> 2 (weight 2)
    // 2 -> 3 (weight 3)
    // 1 -> 3 (weight 10) - This is a direct edge (1 hop)
    
    cost[1][2] = 2;
    cost[2][3] = 3;
    cost[1][3] = 10; 

    // DP Table
    // dist[i][j] will store the shortest path from i to j using 'h' edges
    // Initially, for h=0, distance to self is 0, all others are INF.
    vector<vector<long long>> dist(N + 1, vector<long long>(N + 1, INF));

    // Base Case: 0 edges
    for (int i = 1; i <= N; i++) {
        dist[i][i] = 0;
    }

    // --- The DP Logic (Iterating 'K' times) ---
    for (int h = 1; h <= K; h++) {
        
        // Create a temporary matrix for the current hop count 'h'
        vector<vector<long long>> new_dist(N + 1, vector<long long>(N + 1, INF));

        // Iterate over all pairs (i, j)
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                
                // Try every intermediate node 'p'
                // Logic: Path(i->j using h edges) = Path(i->p using h-1 edges) + Edge(p->j)
                for (int p = 1; p <= N; p++) {
                    
                    if (dist[i][p] != INF && cost[p][j] != INF) {
                        new_dist[i][j] = min(new_dist[i][j], dist[i][p] + cost[p][j]);
                    }
                }
            }
        }
        
        // Update the main dist array for the next iteration
        dist = new_dist;
    }

    // Output Result
    cout << "Shortest path from 1 to 3 with exactly " << K << " edges: ";
    if (dist[1][3] >= INF) {
        cout << "Impossible" << endl;
    } else {
        cout << dist[1][3] << endl;
        // Expected: 1->2 (2) + 2->3 (3) = 5.
        // The direct edge 1->3 (10) is ignored because it is 1 hop, not 2.
    }
}

int main() {
    solve();
    return 0;
}