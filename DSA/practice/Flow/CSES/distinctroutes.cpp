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
vector<int>edgevisitlist;    


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

// Modified DFS to find a single path in the flow graph
// u: current node, t: target node (sink)
// path: reference to vector to store the node sequence
bool get_path(int u, int t, vector<int> &path) {
    path.push_back(u); // 1. Add current node to path sequence

    if (u == t) return true; // 2. Base case: Reached the sink

    // 3. Iterate through edges
    for (int id : adj[u]) {
        // Check if edge has flow (part of solution) and hasn't been visited yet
        if (edges[id].flow == 1 && edgevisitlist[id] == 0) {
            
            edgevisitlist[id] = 1; // 4. "Burn" the edge so it isn't used again
            
            if (get_path(edges[id].v, t, path)) {
                return true; // Path found, bubble up success
            }
        }
    }

    path.pop_back(); // Backtrack if no valid path found from this node
    return false;
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
        cin >> u >> v ;
        add_edge(u, v, 1);
    }

    int s = 1, t = n;
 //   cin >> s >> t;


    ll k =  maxflow(s, t, n) ;
    cout << k <<"\n";

   fill(edgevisitlist.begin(), edgevisitlist.end(), 0);
    edgevisitlist.resize(edges.size() + 1, 0);

    // We know there are exactly 'k' paths
    for (int i = 0; i < k; i++) {
        vector<int> path; 
        get_path(s, t, path); // Call the new function

        // Print the path size
        cout << path.size() << "\n";
        
        // Print path nodes
        for (int j = 0; j < path.size(); j++) {
            cout << path[j] << (j == path.size() - 1 ? "" : " ");
        }
        cout << "\n";
    }
 
}

int main() {
    fastio();
    solve();
}

/*
mistakes : 
    edgevisitlist[]= true update korinai
*/