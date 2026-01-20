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

class Edge {
public:
    pair<ll,ll> to, from;
    ll w;
    Edge(ll weightt, pair<ll,ll> target, pair<ll,ll> source) {
        w = weightt;
        to = target;
        from = source;
    }
    // Operator overload for min-heap (Smallest weight on top)
    bool operator>(const Edge& other) const {
        return w > other.w;
    }
};
void kruskal()
{
    ll dr[] = {-1, 1, 0, 0}; 
    ll dc[] = {0, 0, -1, 1};
    ll A,B, n, m;
    cin >>A >> B>> n >> m;
    vector<ll>fencerows(m+2,0);
    vector<ll>fencecols(n+2,0);
    
     for(ll i = 1; i <= n; i++){
        cin >> fencecols[i];
    }
    for(ll i = 1; i <= m; i++){
        cin >> fencerows[i];
    }
    fencerows[m+1] = B;
    fencecols[n+1]  = A;
    sort(all(fencerows));
    sort(all(fencecols));
   pair<ll,ll> root = {0,0};

    ll total_weight = 0;
    vector<vector<ll>> min_w(m + 1, vector<ll>(n+1,INF));
    vector<vector<bool>> selected(m + 1, vector<bool>(n+1,false));
    //vector<Edge> MST;

    min_w[root.first][root.second] = 0;
    
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    pq.push({0, root, {-1,-1}});

    ll edges_count = 0;

    while (!pq.empty()) {
        Edge top = pq.top();
        pq.pop();

        ll w = top.w;
        pair<ll,ll> u = top.to;
        auto parent = top.from;

        // If node u is already included in MST, skip it
        if (selected[u.first][u.second]) {
            continue;
        }

        selected[u.first][u.second] = true;
        total_weight += w;

        if (parent.first != -1 && parent.second != -1) {
            edges_count++;
        }

        for(ll i = 0; i < 4; i++){
            ll newr = u.first + dr[i];
            ll newc = u.second + dc[i];
            if(newr >= 0 && newr <= m && newc >= 0 && newc <= n){
                ll weight;
               if(dr[i] == 1 || dr[i] == -1)  weight = fencecols[newc+1] - fencecols[newc];
               else weight = fencerows[newr+1] - fencerows[newr];
                if(!selected[newr][newc] && weight < min_w[newr][newc]){
                    min_w[newr][newc] = weight;
                    pq.push({weight, {newr,newc} ,u});
                }
    
            }
        }
    }
    cout << total_weight <<"\n";
}

int main()
{
    kruskal();
}



/*
mistakes:
I wrongfully assumed m and n dimentions, I swapped them which was the main problem(careful)
I fortot to sort them(write stuff down)
I wrongfully did selected indexing, prothome thik diyechilam, then bhul dilam. question your actions

*/