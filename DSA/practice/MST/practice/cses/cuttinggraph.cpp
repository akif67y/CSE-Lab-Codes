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

class queri{
    public : 
    string s;
    int u,v;

    queri(string t, int x, int y){
        s = t;
        u = x;
        v = y;
    }
    

};

class Edge
{
public:
    int w, to, from;
    Edge(int weight, int target, int source)
    {
        w = weight;
        from = target;
        to = source;
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
    int n, m, k;
    cin >> n >> m >> k;
   // int adj[n+1][n+1];
    vector<Edge> edges;
    for (int i = 0; i <= n; i++)
        make_set(i);

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v ;
       // adj[u][v] = 1;
        //adj[v][u] = 1;
        edges.push_back({1, u, v});
        //  edges.push_back({w,u,v});
    }
    vector<queri>q;
    while(k--){
        string s;
        int u,v;
        cin >> s >> u >> v;
        // if(s.compare("cut") == 0){
        //     //forbidden.pb({1,u,v});
        //    // adj[u][v]= 2;
        //    // adj[v][u] = 2;
        // }
        q.pb({s,u,v});
    }

    // for(auto &var : edges){
    //     ll from = var.from;
    //     ll to = var.to;
    //     from = find_set(from);
    //     to = find_set(to);
    //     if(adj[from][to] != 2){
    //         union_sets(from,to);
    //     }
    // }
    reverse(all(q));
    vector<string>answer;
    for(auto &var : q){
        if(var.s.compare("ask") == 0){
            if(find_set(var.u) != find_set(var.v)){
                    answer.pb("NO");
            }
            else{
                answer.pb("YES");
            }
        }
        else{
            union_sets(var.u,var.v);
        }
    }
    reverse(all(answer));
    for(auto &var : answer){
        cout << var <<"\n";
    }





   

  
}

int main()
{
    kruskal();
}
