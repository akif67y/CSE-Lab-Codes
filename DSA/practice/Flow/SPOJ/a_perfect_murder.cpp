#include <bits/stdc++.h>

using namespace std;

#define vi vector<int>
#define pb push_back
#define sz(x) ((int)(x).size())
#define fastio() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define INF 1e18

typedef long long ll;

struct Edge {
    int u, v;
    ll cap, flow;
};

vector<Edge> edges;
vector<vector<int>> adj;
vector<int> parent_edge_index;
vector<int> parent_node;
vector<int> color; // To store 2-coloring (0 or 1)
vector<vector<int>> graph_adj; // Adjacency list for the original graph

void add_edge(int u, int v, ll cap) {
    Edge forward = {u, v, cap, 0};
    adj[u].pb(sz(edges));
    edges.pb(forward);
    Edge backward = {v, u, 0, 0};
    adj[v].pb(sz(edges));
    edges.pb(backward);
}

// Standard BFS for Max Flow
ll bfs(int s, int t) {
    fill(parent_node.begin(), parent_node.end(), -1);
    fill(parent_edge_index.begin(), parent_edge_index.end(), -1);

    parent_node[s] = -2;
    queue<pair<int, ll>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        ll flow = q.front().second;
        q.pop();

        for (int id : adj[cur]) {
            int next = edges[id].v;
            if (parent_node[next] == -1 && edges[id].cap - edges[id].flow > 0) {
                parent_node[next] = cur;
                parent_edge_index[next] = id;
                ll new_flow = min(flow, edges[id].cap - edges[id].flow);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }
    return 0;
}

ll maxflow(int s, int t, int n) {
    ll flow = 0;
    ll new_flow;

    // Use assign to reset with correct size
    parent_node.assign(n + 1, -1);
    parent_edge_index.assign(n + 1, -1);

    while (new_flow = bfs(s, t)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int id = parent_edge_index[cur];
            int rev_id = id ^ 1;
            edges[id].flow += new_flow;
            edges[rev_id].flow -= new_flow;
            cur = parent_node[cur];
        }
    }
    return flow;
}

// DFS to 2-color the graph
void dfs_color(int u, int c) {
    color[u] = c;
    for (int v : graph_adj[u]) {
        if (color[v] == -1) {
            dfs_color(v, 1 - c);
        }
    }
}

void solve(int case_num) {
    int count, friendship;
    cin >> count >> friendship;

    // Clean up for new test case
    graph_adj.assign(count + 1, vi());
    color.assign(count + 1, -1);
    
    // Read Original Graph
    for (int i = 0; i < friendship; i++) {
        int u, v;
        cin >> u >> v;
        graph_adj[u].pb(v);
        graph_adj[v].pb(u);
    }

    // Perform 2-Coloring (The graph might be disconnected, so loop 1 to N)
    for(int i = 1; i <= count; i++) {
        if(color[i] == -1) {
            dfs_color(i, 0);
        }
    }

    // Build Flow Network
    // Nodes 1..count represent the vertices.
    // Source = 0, Sink = count + 1
    int s = 0;
    int t = count + 1;
    int flow_nodes = count + 2;

    edges.clear();
    adj.assign(flow_nodes + 1, vi());

    for (int i = 1; i <= count; i++) {
        if (color[i] == 0) {
            // Node is in Left Set (Partition A)
            add_edge(s, i, 1); // Source -> Left Node
            
            // Add edges to neighbors (which are implicitly in Right Set)
            for (int v : graph_adj[i]) {
                add_edge(i, v, 1); // Left Node -> Right Node
            }
        } else {
            // Node is in Right Set (Partition B)
            add_edge(i, t, 1); // Right Node -> Sink
        }
    }

    // Konig's Theorem: MIS = N - Max Matching
    int matching = maxflow(s, t, flow_nodes);
    int ans = count - matching;
    
    cout << "Case " << case_num << ": " << ans << "\n";
}

int main() {
    fastio();
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        solve(i);
    }
    return 0;
}