#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;

void solveFloydWarshall(int n, vector<vector<int>>& dist) {
    // Standard Floyd-Warshall Triple Loop
    // k = intermediate node
    // i = source node
    // j = destination node
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                
                // CORE LOGIC:
                // The flow through k is limited by the smaller of the two segments:
                // segment (i -> k) and segment (k -> j).
                int pathThroughK = min(dist[i][k], dist[k][j]);
                
                // We want to maximize this bottleneck capacity.
                // If the path through k allows a wider bottleneck than the current
                // best known path (dist[i][j]), we update it.
                dist[i][j] = max(dist[i][j], pathThroughK);
            }
        }
    }
}

int main() {
    // Example: 4 nodes
    int n = 6;
    
    // Initialize matrix with 0 (assuming 0 means no connection)
    // Using 1-based indexing for convenience (size n + 1)
    vector<vector<int>> matrix(n + 1, vector<int>(n + 1, 0));

    // Input Edges (u, v, width)
    // Graph setup:
    // 1 -> 2 (width 10)
    // 2 -> 4 (width 5)  -> Path 1-2-4 bottleneck is 5
    // 1 -> 3 (width 8)
    // 3 -> 4 (width 7)  -> Path 1-3-4 bottleneck is 7
    
   // Input for your specific graph
    matrix[1][2] = 100; matrix[2][1] = 100;
    matrix[2][3] = 100; matrix[3][2] = 100;
    matrix[3][4] = 5;   matrix[4][3] = 5;
    matrix[4][5] = 100; matrix[5][4] = 100;
    matrix[5][6] = 100; matrix[6][5] = 100;
    matrix[2][5] = 80;  matrix[5][2] = 80;
    
    // ... run solveFloydWarshall(6, matrix) ...
    
    // Output matrix[1][6] will be 80.

    // Run Algorithm
    solveFloydWarshall(n, matrix);

    // Output query: Widest path from 1 to 4
    cout << "Max Bottleneck Capacity from 1 to 6: " << matrix[1][6] << endl; 
    // Output should be 7

    return 0;
}