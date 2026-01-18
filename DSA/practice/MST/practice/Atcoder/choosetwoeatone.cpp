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

//ll M; // might need to change this;

//long long binarymulti(ll a, ll b, ll M);
long long binaryexp(ll a, ll b,ll M) {
  ll ans = 1;
  while (b > 0) {
    if (b & 1) {
      ans = (ans * a) % M;
    }
    a = (a * a) % M;
    b >>= 1;
  }
  return ans;
}
// long long binarymulti(ll a, ll b, ll M) {
//     return (__int128)a * b % M;
// }

vector<ll>parent(((ll)(3 * 1e5) + 1));
vector<ll>sizet(((ll)(3 * 1e5) + 1));

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
    ll w, to, from;
    Edge(ll weight, ll target, ll source)
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
    ll n, m;
    cin >> n >> m;
    vector<Edge> edges;
    vector<ll>values(n+1,-1);
    for(ll i = 1; i <= n; i++){
        cin >> values[i];
    }
    //M = m;
    for(ll i = 1; i <= n; i++){
        for(ll j = 1; j <= n; j++){
            if(j == i) continue;
            ll weight = (binaryexp(values[i], values[j], m) + binaryexp(values[j], values[i], m)) % m;
            edges.push_back({ weight, i, j});
        }
    }

    ll cost = 0;
  //  vector<Edge> result;
    for (ll i = 0; i <= n; i++)
        make_set(i);
    ll edgecount = 0;

   sort(edges.begin(), edges.end(), greater<Edge>());

    for (Edge e : edges)
    {
        if (find_set(e.from) != find_set(e.to))
        {
            edgecount++;
            cost += e.w;
           // result.push_back(e);
            union_sets(e.from, e.to);
        }
    }

    cout << cost <<"\n";
}

int main()
{
    kruskal();
}
