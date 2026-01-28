#include <bits/stdc++.h>

using namespace std;

#define fastio()                                                               \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(NULL);                                                               \
  cout.tie(NULL)
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e18
#define nline "\n"
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define ff first
#define ss second
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

// ---------------------- GRAPH STRUCTURE ----------------------

struct Edge {
    int u, v;
    ll cap, flow, cost; // Added 'cost' to your template struct
};

vector<Edge> edges;
vector<vector<int>> adj;
vector<int> parent_edge_index;
vector<int> parent_node;
vector<ll> dist;        // New: To store shortest path costs
vector<bool> in_queue;  // New: For SPFA optimization

// Add edge with Cost
void add_edge(int u, int v, ll cap, ll cost) {
    Edge forward = {u, v, cap, 0, cost};
    adj[u].pb(sz(edges));
    edges.pb(forward);
    
    // Backward edge has 0 capacity and negative cost
    Edge backward = {v, u, 0, 0, -cost};
    adj[v].pb(sz(edges));
    edges.pb(backward);
}

// SPFA (Shortest Path Faster Algorithm)
// Replaces BFS from your template because we need Min Cost, not Shortest Hops
bool spfa(int s, int t, int n) {
    dist.assign(n + 1, INF);
    parent_node.assign(n + 1, -1);
    parent_edge_index.assign(n + 1, -1);
    in_queue.assign(n + 1, false);

    dist[s] = 0;
    queue<int> q;
    q.push(s);
    in_queue[s] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;

        for (int id : adj[u]) {
            int v = edges[id].v;
            // Condition: Residual capacity > 0 AND we found a cheaper path
            if (edges[id].cap - edges[id].flow > 0 && dist[v] > dist[u] + edges[id].cost) {
                dist[v] = dist[u] + edges[id].cost;
                parent_node[v] = u;
                parent_edge_index[v] = id;

                if (!in_queue[v]) {
                    q.push(v);
                    in_queue[v] = true;
                }
            }
        }
    }
    return dist[t] != INF;
}

// ---------------------- SOLVER ----------------------

void solve() {
    int n, m;
    ll k; // Target flow
    cin >> n >> m >> k;

    // Resetting globals
    edges.clear();
    adj.assign(n + 1, vector<int>());
    
    for (int i = 0; i < m; i++) {
        int u, v;
        ll cap, cost;
        cin >> u >> v >> cap >> cost;
        u--; v--; // Converting 1-based input to 0-based
        add_edge(u, v, cap, cost);
    }

    int s = 0;
    int t = n - 1;

    ll total_flow = 0;
    ll min_cost = 0;

    // Main Loop: While we can reach Sink (t) and haven't met Flow (k)
    while (total_flow < k && spfa(s, t, n)) {
        ll path_flow = k - total_flow;
        int cur = t;

        // 1. Calculate Bottleneck (max flow we can push on this path)
        while (cur != s) {
            int id = parent_edge_index[cur];
            path_flow = min(path_flow, edges[id].cap - edges[id].flow);
            cur = parent_node[cur];
        }

        // 2. Update Residual Graph
        cur = t;
        while (cur != s) {
            int id = parent_edge_index[cur];
            edges[id].flow += path_flow;
            edges[id ^ 1].flow -= path_flow; // Update reverse edge
            cur = parent_node[cur];
        }

        // 3. Update Totals
        total_flow += path_flow;
        min_cost += (ll)path_flow * dist[t];
    }

    if (total_flow < k) {
        cout << -1 << nline;
    } else {
        cout << min_cost << nline;
    }
}

int main() {
    fastio();
    int t = 1;
    // cin >> t; // Uncomment if multiple test cases exist
    while(t--) {
        solve();
    }
}