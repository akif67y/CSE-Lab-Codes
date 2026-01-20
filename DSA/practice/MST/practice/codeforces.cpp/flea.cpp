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





void solve() {
    ll n,m,s;
    cin >> n >> m >> s;

    cout << (((n-1)%s + 1) * (ll)ceil((double)n/s)) *(((m-1)%s + 1) * (ll)ceil((double)m/s))<<"\n";

}

int main() {

#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
#endif
  fastio();
  solve();
}
