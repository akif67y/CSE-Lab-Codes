#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <cstring> // For memset
#include <algorithm>

using namespace std;

// Maximum number of nodes: Source(1) + Sizes(6) + Contestants(50) + Sink(1) ~= 60
const int MAX_NODES = 100;
const int INF = 1e9;

// Adjacency Matrix for Capacity
int capacity[MAX_NODES][MAX_NODES];
// To keep track of the graph connectivity
vector<int> adj[MAX_NODES];

// Mapping shirt sizes to integer IDs (1-6)
int getSizeID(string s) {
    if (s == "XXL") return 1;
    if (s == "XL") return 2;
    if (s == "L") return 3;
    if (s == "M") return 4;
    if (s == "S") return 5;
    if (s == "XS") return 6;
    return 0;
}

// Function to add directed edge with capacity
void addEdge(int u, int v, int cap) {
    adj[u].push_back(v);
    adj[v].push_back(u); // Residual edge needs to exist in adjacency list
    capacity[u][v] = cap;
    // capacity[v][u] is initially 0 for the reverse edge
}

// BFS to find an augmenting path in the residual graph
int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2; // Mark source as visited
    
    queue<pair<int, int>> q;
    q.push({s, INF}); // Push start node and infinite flow
    
    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();
        
        for (int next : adj[cur]) {
            // If next node is not visited and there is residual capacity
            if (parent[next] == -1 && capacity[cur][next] > 0) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                
                if (next == t)
                    return new_flow; // Reached sink
                
                q.push({next, new_flow});
            }
        }
    }
    return 0; // No path found
}

// Edmonds-Karp Algorithm
int maxFlow(int s, int t) {
    int flow = 0;
    vector<int> parent(MAX_NODES);
    int new_flow;
    
    // While there is an augmenting path from source to sink
    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        
        // Backtrack and update residual capacities
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }
    return flow;
}

void solve(int caseNum) {
    int N, M;
    cin >> N >> M;
    
    // Reset graph for each test case
    memset(capacity, 0, sizeof(capacity));
    for(int i = 0; i < MAX_NODES; i++) adj[i].clear();
    
    int source = 0;
    int sink = M + 6 + 1; // Sink is after contestants
    
    // 1. Edges from Sizes (1-6) to Sink
    // Each size is available N times (for N colors)
    for (int i = 1; i <= 6; i++) {
        addEdge(i, sink, N);
    }
    
    // 2. Process Contestants
    // Contestants will be nodes 7 to 7 + M - 1
    for (int i = 0; i < M; i++) {
        int contestantNode = 7 + i;
        
        // Edge from Source to Contestant
        addEdge(source, contestantNode, 1);
        
        string s1, s2;
        cin >> s1 >> s2;
        
        // Edges from Contestant to their preferred Sizes
        addEdge(contestantNode, getSizeID(s1), 1);
        addEdge(contestantNode, getSizeID(s2), 1);
    }
    
    int total_flow = maxFlow(source, sink);
    
    cout << "Case " << caseNum << ": ";
    if (total_flow == M) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

int main() {
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        solve(i);
    }
    return 0;
}