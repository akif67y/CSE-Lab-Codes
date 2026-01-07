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

#define M 100000007 // might need to change this;

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

void solve() {
  ll n, m;
  cin >> n >> m;

  vector<vector<pair<ll, ll>>> graph(n + 1);
  vector<pair<ll, pair<ll, ll>>> edge_list; //{weight, {from, to}}
  for (int i = 0; i < m; i++) {
    int from, to, weight;
    cin >> from >> to >> weight;
    edge_list.push_back({weight, {from, to}});
    graph[from].push_back({weight, to}); //{weight, to}
  }

  vector<ll> distances(n + 1, 0);
  vector<bool> reachable_neg(n + 1, false);
  //  distances[s] = 0;
  vector<ll> prev_distances(n + 1, 0);
  vector<ll> parent(n + 1, -1);

  for (int i = 0; i < n - 1; i++) {
    for (auto &var : edge_list) {
      ll weight = var.first;
      ll from = var.second.first;
      ll to = var.second.second;
      if (distances[to] > distances[from] + weight) {
        distances[to] = distances[from] + weight;
        parent[to] = from;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    prev_distances[i] = distances[i];
  }
  for (auto &var : edge_list) {
    ll weight = var.first;
    ll from = var.second.first;
    ll to = var.second.second;
    if (distances[to] > distances[from] + weight) {
      distances[to] = distances[from] + weight;
      parent[to] = from;
    }
  }
  ll culprit = -1;
  debug(distances);
  debug(prev_distances);
  for (int i = 1; i <= n; i++) {
    if (distances[i] < prev_distances[i]) {
      culprit = i;
      break;
    }
  }
  if (culprit == -1) {
    cout << "-1" << "\n";
    return;
  }
  vector<bool> visited(n + 1, false);
  ll cur = culprit;
  while (cur != -1) {
    if (visited[cur]) {
      culprit = cur;
      break;
    }
    visited[cur] = true;
    cur = parent[cur];
  }
  vector<ll> answer;
  debug(parent);
  debug(culprit);
  answer.push_back(cur);
  ll temp = parent[cur];
  while (temp != cur) {
    answer.push_back(temp);
    temp = parent[temp];
  }
  for (int i = answer.size() - 1; i >= 0; i--) {
    cout << answer[i] << " ";
  }
  // cout << answer[answer.size()-1];
}

int main() {

#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
#endif
  fastio();
  solve();
}
