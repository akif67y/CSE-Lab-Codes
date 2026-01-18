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

vector<ll>parent(((int)(2 * 1e5) + 1));
vector<ll>sizet(((int)(2 * 1e5) + 1));

void make_set(ll v) {
    parent[v] = v;
    sizet[v] = 1;
}

ll find_set(ll v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}



void union_sets(ll a, ll b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (sizet[a] < sizet[b])
            swap(a, b);
        parent[b] = a;
        sizet[a] += sizet[b];
    }
}

class Edge {
public:
    ll w, to, from, status, index;
    Edge(ll weight, ll target, ll source, ll stat,ll ndex) {
        w = weight;
        to = target;
        from = source;
        status = stat;
        index = ndex;
    }
    bool operator>(const Edge& other) const {
        return w > other.w;
    }
    bool operator<(const Edge& other) const {
        return w < other.w; 
    }
};

void kruskal(){
  ll n, m, q;
    cin >> n >> m >> q;
     vector<Edge> edges;
    for(ll i = 0; i < m; i++){
        ll u,v,w;
        cin >> u >> v >> w;
        edges.push_back({w,v,u,0, -1});
      //  edges.push_back({w,u,v});
    }
   // map<Edge,ll>track;
    for(ll i = 0; i < q; i++){
        ll u,v,w;
        cin >> u >> v >> w;
       
        edges.push_back({w,v,u,1, i});
    }
    vector<bool>answert(q,false);
   

    ll cost = 0;
  //  vector<Edge> result;
    for (ll i = 0; i <= n; i++)
    make_set(i);
    ll edgecount = 0;

    sort(edges.begin(), edges.end());

    for (Edge e : edges) {
    if (find_set(e.from) != find_set(e.to)) {
        if(e.status == 1){
            answert[e.index] = true;
        }
        else{
            edgecount++;
            cost += e.w;
            // result.push_back(e);
            union_sets(e.from, e.to);
        }
        
    }
    }
    for(ll i = 0; i < answert.size(); i++){
        cout << (answert[i] ? "YES\n": "NO\n") ;
    }
    // for(ll i = 0; i < answert.size(); i++){
    //     if(answert[i]){
    //         cout << "Yes\n";
    //     }
    //     else{
    //         cout <<"No\n";
    //     }
    // }


}

int main(){
    kruskal();

}
