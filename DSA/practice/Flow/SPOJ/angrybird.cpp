#include <bits/stdc++.h>

using namespace std;

// #define unordered_map<long long, int, custom_hash> ulli
#define For(a, b) for (int i = a; i < (b); i++)
#define vi vector<int>
#define vll vector<long long>
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
#define PI 3.141592653589793238462
#define set_bits __builtin_popcountll
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
// typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag,
// tree_order_statistics_node_update > pbds; // find_by_order, order_of_key

#ifndef ONLINE_JUDGE
#define debug(x)                                                               \
  cerr << #x << " ";                                                           \
  _print(x);                                                                   \
  cerr << endl;
#else
#define debug(x)
#endif

void _print(ll t) { cerr << t; }
void _print(int t) { cerr << t; }
void _print(string t) { cerr << t; }
void _print(char t) { cerr << t; }
void _print(lld t) { cerr << t; }
void _print(double t) { cerr << t; }
void _print(ull t) { cerr << t; }


typedef long long ll;
struct Edge {
    int u, v;
    ll cap, flow;
};

vector<Edge> edges;
vector<vector<int>> adj;
vector<int> parent_edge_index; 
vector<int> parent_node;       


void add_edge(int u, int v, ll cap) {
    Edge forward = {u, v, cap, 0};
    adj[u].pb(sz(edges)); 
    edges.pb(forward);
    Edge backward = {v, u, 0, 0};
    adj[v].pb(sz(edges)); 
    edges.pb(backward);
}
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

   
    parent_node.resize(n + 1);
    parent_edge_index.resize(n + 1);

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

void solve(int t_case) {
    int m_machines, w_wires;
    cin >> m_machines >> w_wires;

    // Clear previous graph
    edges.clear();
    // We need 2 nodes per machine: i and i+m_machines
    adj.assign(2 * m_machines + 2, vi());

    // 1. Read Machine Costs (Nodes 2 to M-1)
    // The Boss (1) and Server (M) have INF capacity.
    // The input gives M-2 integers for machines 2, 3 ... M-1
    
    // Boss (Node 1) cannot be destroyed -> INF capacity
    add_edge(1, 1 + m_machines, INF); 

    // Server (Node M) cannot be destroyed -> INF capacity
    // Note: We handle this later in the loop or manually, 
    // but the input loop below handles 2 to M-1.
    
    for (int i = 2; i < m_machines; i++) {
        int cost;
        cin >> cost;
        // Internal edge for destroyable machine
        add_edge(i, i + m_machines, cost);
    }
    
    // Server (Node M)
    add_edge(m_machines, m_machines + m_machines, INF);


    // 2. Read Wire Costs (Edges)
    for (int i = 0; i < w_wires; i++) {
        int u, v, cost;
        cin >> u >> v >> cost;
        
        // Wires are bidirectional. 
        // We connect u_out -> v_in AND v_out -> u_in
        // u_out is (u + m_machines), v_in is (v)
        
        add_edge(u + m_machines, v, cost);
        add_edge(v + m_machines, u, cost);
    }

    // 3. Calculate Max Flow = Min Cut
    // Source is Boss_in (1), Sink is Server_out (M + m_machines) or Server_in (M)
    // Since capacity of M is INF, flow into M is same as flow out of M.
    // Let's use 1 (start) and M + m (end of the server pipe) for clarity.
    
    int source = 1; 
    int sink = 2 * m_machines; // The 'out' side of node M (M + M)

    // Note: Pass the total number of nodes to your maxflow function
    ll min_cost = maxflow(source, sink, 2 * m_machines + 1);

    cout << "Case " << t_case << ": " << min_cost << "\n";
}

int main() {
    fastio();
    int tt;
    cin >> tt;
    while(tt--){
        solve(tt);
    }
}

