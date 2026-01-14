#include <iostream>
#include <vector>

using namespace std;

const long long INF = 1e15; // Represent infinity

void countShortestPaths(int n, vector<vector<long long>>& adj) {
    // D[i][j] will hold the shortest distance between i and j
    vector<vector<long long>> D = adj;
    
    // C[i][j] will hold the number of shortest paths between i and j
    vector<vector<long long>> C(n, vector<long long>(n, 0));

    // Initialization
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                D[i][j] = 0;
                C[i][j] = 1; // Path to self is 1
            } else if (D[i][j] != INF) {
                C[i][j] = 1; // Edge exists, so 1 initial shortest path
            }
        }
    }

    // Floyd-Warshall DP Extension
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // Check if paths through k are valid
                if (D[i][k] != INF && D[k][j] != INF) {
                    
                    long long newDist = D[i][k] + D[k][j];
                    long long newCount = C[i][k] * C[k][j];

                    if (newDist < D[i][j]) {
                        // Case 1: Found a strictly shorter path
                        D[i][j] = newDist;
                        C[i][j] = newCount;
                    } 
                    else if (newDist == D[i][j] && i != k && k != j) {
                        // Case 2: Found an alternative path of the same length
                        // k must be a distinct intermediate node to avoid overcounting
                        C[i][j] += newCount;
                    }
                }
            }
        }
    }

    // Displaying the Results
    cout << "Shortest Distances:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (D[i][j] == INF) cout << "INF ";
            else cout << D[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nNumber of Shortest Paths:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n = 4; // Number of vertices
    // Adjacency matrix initialization with INF
    vector<vector<long long>> adj(n, vector<long long>(n, INF));

    // Example edges: (u, v, weight)
    adj[0][1] = 2;
    adj[0][2] = 2;
    adj[1][3] = 1;
    adj[2][3] = 1;
    adj[0][3] = 4;

    countShortestPaths(n, adj);

    return 0;
}