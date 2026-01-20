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

vector<ll>parent(((ll)(2 * 1e5) + 1));
vector<ll>sizet(((ll)(2 * 1e5) + 1));
ll ccount = 0;

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
        ccount--;
    }
}
class Nodes{
    public : 
    double x,  y;
    Nodes(double xx, double yy){
        x = xx;
        y = yy;
    }
};

class Edge
{
public:
    double w;
    ll from, to, type;
    Edge(double weight, ll target, ll source , ll tp)
    {
        w = weight;
        to = target;
        from = source;
        type = tp;
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
    ll n, r, w, u, v;
    cin >> n >> r >> w >> u >> v;
    vector<Nodes> nodes;
    for (ll i = 0; i < n; i++)
    {
        double u, v, w;
        cin >> u >> v ;
        nodes.push_back({u, v});
        //  edges.push_back({w,u,v});
    }
     vector<Edge>edges;
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            double distance = sqrt( (nodes[i].x - nodes[j].x) *(nodes[i].x - nodes[j].x) + (nodes[i].y - nodes[j].y) * (nodes[i].y - nodes[j].y) );
            if(distance <= r){
               edges.pb({distance * u, j, i,0}); 
            }
            else  edges.pb({distance * v, j, i, 1});
        }
    }

    double cost1 = 0;
    double cost2 = 0;
    vector<Edge> result;
    for (ll i = 0; i < n; i++){
        make_set(i);
        ccount = n;
    }
        
    ll edgecount = 0;

    sort(edges.begin(), edges.end());

    for (Edge e : edges)
    {
        if(ccount <= w){
            break;
        }
        if (find_set(e.from) != find_set(e.to))
        {
            edgecount++;
            if(e.type == 0){
                cost1 += e.w;
            }
            else{
                cost2 += e.w;
            }
          //  result.push_back(e);
            union_sets(e.from, e.to);
        }
    }
    cout << fixed <<setprecision(3) <<cost1 <<" "<< cost2 <<"\n";;
}

int main()
{
    ll tt;
    cin >> tt;
    for(int i = 1; i <= tt; i++){
        cout << "Caso #"<<i<<": ";
        kruskal();
    }
    
}
