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

template <class T, class V> void _print(pair<T, V> p);
template <class T> void _print(vector<T> v);
template <class T> void _print(set<T> v);
template <class T, class V> void _print(map<T, V> v);
template <class T> void _print(multiset<T> v);
template <class T, class V> void _print(pair<T, V> p) {
  cerr << "{";
  _print(p.ff);
  cerr << ",";
  _print(p.ss);
  cerr << "}";
}
template <class T> void _print(vector<T> v) {
  cerr << "[ ";
  for (T i : v) {
    _print(i);
    cerr << " ";
  }
  cerr << "]";
}
template <class T> void _print(set<T> v) {
  cerr << "[ ";
  for (T i : v) {
    _print(i);
    cerr << " ";
  }
  cerr << "]";
}
template <class T> void _print(multiset<T> v) {
  cerr << "[ ";
  for (T i : v) {
    _print(i);
    cerr << " ";
  }
  cerr << "]";
}
template <class T, class V> void _print(map<T, V> v) {
  cerr << "[ ";
  for (auto i : v) {
    _print(i);
    cerr << " ";
  }
  cerr << "]";
}
ll M; // might need to change this;

long long binarymulti(ll a, ll b);
long long binaryexp(ll a, ll b) {
  ll ans = 1;
  while (b > 0) {
    if (b & 1) {
      ans = binarymulti(ans, a) % M;
    }
    a = binarymulti(a, a) % M;
    b >>= 1;
  }
  return ans;
}
long long binarymulti(ll a, ll b) {
  ll ans = 0;
  while (b > 0) {
    if (b & 1) {
      ans = (ans + a) % M;
    }
    a = (a + a) % M; // prevents overflow of multiplying a and b, asuming 2a
                     // doesn't cause overflow
    b >>= 1;
  }
  return ans;
}


 // adjacency matrix of graph
//const int INF = 1000000000; // weight INF means there is no edge

struct Edge {
    ll w = INF, to = -1;
};

void prim() {
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> adj(n+1, vector<ll>(n+1,INF));
    vector<bool> selected(n+1, false);
    vector<Edge> min_e(n+1);
    M = m;
    vector<ll>values(n+1,-1);
    for(ll i = 1; i <= n; i++){
        cin >> values[i];
    }
    for(ll i = 1; i <= n; i++){
        for(ll j = 1; j <= n; j++){
            if(j == i) continue;
            ll weight = (binaryexp(values[i], values[j]) + binaryexp(values[j], values[i])) % M;
            adj[i][j] = -weight;
            adj[j][i] = -weight;
        }
    }
    min_e[1].w = 0;
    
    ll total_weight = 0;

    for (int i=1; i<=n; ++i) {
        ll v = -1;
        for (int j = 1; j <= n; ++j) {
            if (!selected[j] && (v == -1 || min_e[j].w < min_e[v].w))
                v = j;
        }

        if (min_e[v].w == INF) {
            cout << "No MST!" << endl;
            exit(0);
        }

        selected[v] = true;
        total_weight += min_e[v].w;
        

        for (int to = 1; to <= n; ++to) {
            if (adj[v][to] < min_e[to].w)
                min_e[to] = {adj[v][to], v};
        }
    }

    cout << -total_weight << endl;
}
void solve() {
  
}

int main() {

#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
#endif
  fastio();
  prim();
}
