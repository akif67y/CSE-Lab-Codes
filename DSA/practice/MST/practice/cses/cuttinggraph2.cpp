#include <bits/stdc++.h>

using namespace std;

// #define unordered_map<long long, ll, custom_hash> ulli
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
vector<ll>popul(((ll)(2 * 1e5) + 1));

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
        popul[a] += popul[b];
    }
}

class queri{
    public : 
    string s;
    ll u,v;

    queri(string t, ll x, ll y){
        s = t;
        u = x;
        v = y;
    }
    

};

class Edge
{
public:
    ll w, to, from;
    bool status = true;
    Edge(){

    }
    Edge(ll weight, ll target, ll source)
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
    ll n, m, Q;
    cin >> n >> m >> Q;
    vector<Edge>edgebyindx(m+1);
    vector<ll>populations(n+1,0);
    for(ll i = 1; i <= n; i++){
        cin >> populations[i];
    }
    for (ll i = 1; i <= n; i++){
        make_set(i);
        popul[i] = populations[i];
    }
        

    for (ll i = 1; i <= m; i++)
    {
        ll u, v, w;
        cin >> u >> v ;
        edgebyindx[i] = {1,u,v};
       
    }
    vector<queri>q;
    while(Q--){
        string s;
        cin >> s;
         ll city, val = -1;
        if(s.compare("D") == 0){
            cin >> city;
            edgebyindx[city].status = false; 
        }
        else{
            cin >> city >> val;
            ll temp = val;
            val = populations[city];
            populations[city] = temp;
             
        }
       
        q.pb({s,city,val});
    }
    ll curmax = -INF;
    for(ll i = 1; i <= n; i++){
        if(curmax < popul[i]){
            curmax = popul[i];
        }
    }
    for(ll i = 1; i <= m; i++){
        auto var = edgebyindx[i];
        ll from = var.from;
        ll to = var.to;
        from = find_set(from);
        to = find_set(to);
        if(var.status){
            if(from != to && popul[from] + popul[to] > curmax){
                curmax = popul[from] + popul[to];
            }
            union_sets(from,to);
        }
    }
    reverse(all(q));
    vector<ll>answer;
    answer.pb(curmax);
    for(auto &var : q){
        if(var.s.compare("D") == 0){
        auto var2 = edgebyindx[var.u];
        ll from = var2.from;
        ll to = var2.to;
        from = find_set(from);
        to = find_set(to);
        if(var2.status){
            if(from != to && popul[from] + popul[to] > curmax){
                curmax = popul[from] + popul[to];
            }
            union_sets(from,to);
        }
        answer.pb(curmax);
        }
        else{
            ll from = find_set(var.u);
            popul[from] = popul[from] + (var.v - populations[var.u]);
            populations[var.u] = var.v;
            if(popul[from] > curmax){
                curmax = popul[from];
            }
            answer.pb(curmax);
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
