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


void make_set(ll v)
{
    parent[v] = v;
    sizet[v] = 1;
}

ll find_set(ll v)
{
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(ll a, ll b)
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
    ll w, to, from, status = false, idx;
    Edge(){

    }
    Edge(ll weight, ll target, ll source)
    {
        w = weight;
        to = target;
        from = source;
    }
    Edge(ll weight, ll target, ll source,ll idx2)
    {
        w = weight;
        to = target;
        from = source;
        idx = idx2;
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
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++)
    {
        int u, v, wi;
        cin >> u >> v >> wi;
        edges[i]= Edge(wi,u,v,i);
        //  edges.push_back({w,u,v});
    }
     vector<Edge>cpyedges(edges);

    int cost = 0;
    vector<Edge> result;
    for (int i = 0; i <= n; i++)
        make_set(i);
    int edgecount = 0;

    sort(edges.begin(), edges.end());
    int cur = edges[0].w;
    for (int i = 0; i < edges.size();)
    {
        int j = i;
        while( j < edges.size() && edges[j].w == cur){
             if (find_set(edges[j].from) != find_set(edges[j].to)){
                edges[j].status = true;
                cpyedges[edges[j].idx].status = true;
             }
            j++;
        }
        j = i;
         while( j < edges.size() && edges[j].w == cur){
             if (find_set(edges[j].from) != find_set(edges[j].to)){
                cost += edges[i].w;
                union_sets(edges[j].from, edges[j].to);
             }
            j++;
        }
        i = j;
       if(i < edges.size()) cur = edges[i].w;
    }
    for(int i = 0; i < cpyedges.size(); i++){
        if(cpyedges[i].status){
            cout <<"YES\n";
        }
        else{
            cout <<"NO\n";
        }
    }
   
    


}

int main()
{
    kruskal();
}
