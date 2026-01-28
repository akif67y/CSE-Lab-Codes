#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits> // For INT_MAX

using namespace std;

// Represents a directed edge in the flow network
struct Edge {
    int to;             // The destination vertex
    int capacity;       // Total capacity of this edge
    int flow;           // Current flow passing through this edge
    int reverse_edge;   // Index of the reverse edge in the "to" vertex's adjacency list
};

// Global graph storage: adj[u] contains a list of Edges starting from u
vector<vector<Edge>> adj;
// Parent array to store the path found by BFS: parent[v] = {u, edge_index_in_u}
vector<pair<int, int>> parent;

// Function to add a directed edge with a specific capacity
void add_edge(int u, int v, int cap) {
    // Forward edge: u -> v with capacity 'cap'
    Edge forward = {v, cap, 0, (int)adj[v].size()};
    
    // Backward edge: v -> u with capacity 0 (initially). 
    // This allows us to "push back" flow later if needed.
    Edge backward = {u, 0, 0, (int)adj[u].size()};
    
    adj[u].push_back(forward);
    adj[v].push_back(backward);
}

// BFS to find an augmenting path from s (source) to t (sink)
// Returns the bottleneck capacity of the path found, or 0 if no path exists.
int bfs(int s, int t) {
    fill(parent.begin(), parent.end(), make_pair(-1, -1));
    parent[s] = {-2, -2}; // Mark source as visited

    queue<pair<int, int>> q;
    q.push({s, INT_MAX}); // Push source with infinite flow possibility

    while (!q.empty()) {
        int u = q.front().first;
        int current_flow = q.front().second;
        q.pop();

        // Iterate through all edges going out of u
        for (int i = 0; i < adj[u].size(); i++) {
            Edge &e = adj[u][i];
            
            // If the neighbor is not visited AND there is residual capacity
            if (parent[e.to].first == -1 && (e.capacity - e.flow) > 0) {
                // The new flow is limited by the bottleneck of the path so far
                // and the remaining capacity of this specific edge
                int new_flow = min(current_flow, e.capacity - e.flow);
                
                parent[e.to] = {u, i}; // Store how we got here
                
                if (e.to == t) {
                    return new_flow; // We reached the sink! Return the bottleneck.
                }
                
                q.push({e.to, new_flow});
            }
        }
    }
    return 0; // No path found
}

void solve() {
    int n;
    cin >> n; // Read number of chambers

    // Reset graph for the new test case
    adj.assign(n + 1, vector<Edge>());
    parent.assign(n + 1, { -1, -1 });

    // Reading the graph
    // We iterate from 1 to n-1 because the last chamber (n) has no outgoing corridors
    for (int i = 1; i < n; i++) {
        int m;
        cin >> m; // Number of corridors exiting chamber i
        for (int j = 0; j < m; j++) {
            int target;
            cin >> target;
            
            // LOGIC FOR CAPACITIES:
            // 1. If edge leaves the Top Chamber (i == 1), capacity is 1.
            // 2. If edge enters the Bottom Chamber (target == n), capacity is 1.
            // 3. Otherwise, capacity is Infinite (we use a large enough number, e.g., N).
            // Note: If an edge is 1 -> n, it satisfies both, so capacity is 1.
            
            int cap = INT_MAX;
            if (i == 1 || target == n) {
                cap = 1;
            }
            
            add_edge(i, target, cap);
        }
    }

    // Edmonds-Karp Max Flow
    int max_flow = 0;
    int new_flow;

    // While we can find a path with available capacity...
    while (new_flow = bfs(1, n)) {
        max_flow += new_flow;
        
        // Backtrack from sink to source to update flow values along the path
        int cur = n;
        while (cur != 1) {
            int prev = parent[cur].first;
            int edge_idx = parent[cur].second;
            
            // Add flow to forward edge
            adj[prev][edge_idx].flow += new_flow;
            
            // Subtract flow from reverse edge (standard Max Flow procedure)
            int reverse_idx = adj[prev][edge_idx].reverse_edge;
            adj[cur][reverse_idx].flow -= new_flow;
            
            cur = prev;
        }
    }

    cout << max_flow << endl;
}

int main() {
    // Optimization for faster I/O operations
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}