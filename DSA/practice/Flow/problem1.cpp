#include<bits/stdc++.h>

using namespace std;

//#define unordered_map<long long, int, custom_hash> ulli 
#define For(a,b) for(int i=a; i<(b); i++)
#define vi vector<int>
#define vll vector<long long>
#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
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
// typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update > pbds; // find_by_order, order_of_key

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x <<" "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

void _print(ll t) {cerr << t;}
void _print(int t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(lld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}






template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.ff); cerr << ","; _print(p.ss); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}

class Edge{
    public : 
    ll u, v, w;
    Edge(){

    }
    Edge(ll u1, ll v1, ll w1){
        u = u1;
        v = v1;
        w = w1;
    }

};
ll bfs(ll s, ll t, vector<ll>& parent,  vector<vector<ll>>&adj, vector<vector<ll>>&capacity) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<ll, ll>> q;
    q.push({s, INF});

    while (!q.empty()) {
        ll cur = q.front().first;
        ll flow = q.front().second;
        q.pop();

        for (ll next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                ll new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

ll maxflow(ll s, ll t, ll n,vector<vector<ll>>&capacity, vector<vector<ll>>&adj ) {
    ll flow = 0;
    vector<ll> parent(n);
    ll new_flow;

    while (new_flow = bfs(s, t, parent,adj, capacity)) {
        flow += new_flow;
        ll cur = t;
        while (cur != s) {
            ll prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}


void solve(){
    ll m, n;
    cin >> n >> m;
    vector<vector<ll>>capacity(n+1, vector<ll>(n+1,INF));
    vector<vector<ll>> adj(n+1);
    vector<Edge>edgelist;
    for(int i = 0; i < m; i++){
        ll u,v,w;
        cin >> u >> v >> w;
        adj[u].pb(v) ;
        capacity[u][v] = w;
        capacity[v][u] = 0;
        edgelist.pb({u,v,w});
    }
    ll s,t;
    cin >> s >> t;
    ll ans = maxflow(s,t,n,capacity, adj);
    cout << ans <<"\n";
    for(int i = 0; i < sz(edgelist); i++){
        ll from, to , weight;
        from = edgelist[i].u;
        to = edgelist[i].v;
        weight = edgelist[i].w;
       if(capacity[from][to] == 0) cout << from <<" "<< to;
    }


}


int main() {

#ifndef ONLINE_JUDGE
	freopen("Error.txt", "w", stderr);
#endif
    fastio();
    solve();
   
}


