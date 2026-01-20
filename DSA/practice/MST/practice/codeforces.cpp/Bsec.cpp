#include <bits/stdc++.h>

using namespace std;

// #define unordered_map<long long, int, custom_hash> ulli
#define For(a, b) for (int i = a; i < (b); i++)
#define vi vector<int>
#define vll vector<long long>
#define fastio()                      \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
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
#define debug(x)       \
    cerr << #x << " "; \
    _print(x);         \
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

void make_set(int v)
{
    parent[v] = v;
    sizet[v] = 1;
}

int find_set(int v)
{
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b)
{
    a = find_set(a);
    b = find_set(b);
    if (a != b)
    {
        if (sizet[a] < sizet[b])
            swap(a, b);
        parent[b] = a;
        sizet[a] += sizet[b];
    }
}

class Edge
{
public:
    int w, to, from;
    Edge(int weight, int target, int source)
    {
        w = weight;
        to = target;
        from = source;
    }
    bool operator>(const Edge &other) const
    {
        return w > other.w;
    }
    bool operator<(const Edge &other) const
    {
        return w < other.w;
    }
};

void kruskal()
{
    int n, m;
    cin >> n >> m;
    vector<Edge> edges;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({w, v, u});
        //  edges.push_back({w,u,v});
    }

    int cost = 0;
    // vector<Edge> result;
    ll mini = INF;

    sort(edges.begin(), edges.end());

    for(int i = 0; i < edges.size(); i++){
        int edgecount = 0;
        for (int k = 1; k <= n; k++){
            make_set(k);
        }
        
        ll lasttaken = -1;
        for(int j = i; j < edges.size(); j++){
            if (find_set(edges[j].from) != find_set(edges[j].to))
        {
            edgecount++;
            lasttaken = j;
            union_sets(edges[j].from, edges[j].to);
        }
        }
        ll diff ;
        if(edgecount == n-1){
            diff = abs(edges[lasttaken].w - edges[i].w);
            mini = min(diff, mini);
        }
    }
    
    cout << (mini == INF ? -1 : mini)<<"\n";

    
}

int main()
{
    kruskal();
}
