#include<bits/stdc++.h>

using namespace std;

#define For(a,b) for(int i=a; i<(b); i++)
#define vi vector<int>
#define vll vector<long long>
#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define INF 1e18
#define pb push_back
#define sz(x) ((int)(x).size())

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

void solve() {
    int n, m;
    cin >> n >> m;
    
   
    edges.clear();
    adj.assign(n + 1, vi());


    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        add_edge(u, v, w);
    }

    int s, t;
    cin >> s >> t;

    cout << maxflow(s, t, n) << "\n";

  
    for (int i = 0; i < m; i++) {
        int id = 2 * i; 
        cout << edges[id].u << " " << edges[id].v << " " 
             << edges[id].flow << "/" << edges[id].cap << "\n";
    }
}

int main() {
    fastio();
    solve();
}