#include<bits/stdc++.h>

using namespace std;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
//#define unordered_map<long long, int, custom_hash> ulli 
#define For(a,b) for(int i=a; i<(b); i++)
#define vi vector<int>
#define vll vector<long long>
#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
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
// typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update > pbds; // find_by_order, order_of_key

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x <<" "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

void _print(ll t) {cerr << t;}
void _print(int t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(lld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}



void setkthbit(ll &n, int k){
    n = n |(1 << k);
}
void resetkthbit(ll &n, int k){
    n = n & (~(1 << k));
}
void setrangebit(ll &n, int s, int e){
    int bit = e - s + 1;
    ll mask = (~(-1 << bit))<<s;
    n|= mask;
}
void resetrangebit(ll &n, int s, int e){
    int bit = e - s + 1;
    ll mask = (~(-1 << bit))<<s;
    n&= ~mask;
}
void printbit(ll n){
    if(n == 0) {cout << 0 ;
    return;}
    else if(n == 1) {
        cout << 1;
        return ;
    }
    else{
        printbit(n/2);
        cout << n % 2;
    }
}
#define M 100000007  //might need to change this;

long long binarymulti(ll a, ll b);
long long binaryexp(ll a, ll b){
    ll ans = 1;
    while(b > 0){
        if(b&1){
        ans = binarymulti(ans,a) % M;
        }
        a = binarymulti(a , a) % M  ;
        b >>= 1;
    }
    return ans;
}
long long binarymulti(ll a, ll b){
      ll ans = 0;
    while(b > 0){
        if(b&1){
        ans = (ans + a) % M;
        }
        a = (a + a) % M  ;  // prevents overflow of multiplying a and b, asuming 2a doesn't cause overflow
        b >>= 1;
    }
    return ans;

}


template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.ff); cerr << ","; _print(p.ss); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}

 vector<bool> sievealgo(){
    int size = 1e7 + 10;
    vector<bool>primes(size, 1);
    primes[0] = false;
    primes[1] = false;
    for (int i = 2; i * i < size; i++)
    {
        if (primes[i])
        {
            for (int j = i * i; j < size; j += i)
            {
                primes[j] = false;
            }
        }
    }
    return primes;
}

void solve(){
    ll n, m, s, t;
    cin >> n >> m ;
    s = 1;
    t = n;

    vector<vector<pair<ll,ll>>> graph(n+1);
    vector<ll>slowness(n+1);

    for(ll i = 0; i < m; i++){
        ll a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back({c, b}); 
        graph[b].push_back({c, a}); 
    }
    for(int i = 1; i <= n; i++){
        cin >> slowness[i];
    }

    priority_queue<pair<ll,pair<ll,ll>>, vector<pair<ll,pair<ll,ll>>>, greater<pair<ll,pair<ll,ll>>>> pq; 
    //{weight, {city, smallest s(i)}}
    ll distances[n+1][1001];
    for(auto &var : distances){
        for(auto &var2 : var){
            var2 = INF;
        }
    }
   // vector<ll> distances(n+1, INF); 
    // vector<int> parents(n+1, -1);
    
    distances[s][slowness[1]] = 0;
    pq.push({0, {s, slowness[1]}});

    while(!pq.empty()){
        ll d = pq.top().first;
        ll u = pq.top().second.first; //city
        ll parentslowness = pq.top().second.second;
        pq.pop();


        if(d > distances[u][parentslowness]) continue;

        for(auto& edge : graph[u]){
            ll weight = edge.first;
            ll v = edge.second;
            ll childslowness = min(parentslowness, slowness[v]);
            if(distances[u][parentslowness] + weight * parentslowness < distances[v][childslowness]){
                distances[v][childslowness] = distances[u][parentslowness] + weight * parentslowness;
                pq.push({distances[v][childslowness], {v, childslowness}});
            }
        }
    }
    ll answer = INF;
    for(int i = 1; i <= 1000; i++){
        auto var = distances[n][i];
        answer = min(answer, var);
    }
    cout << answer <<"\n";
}

int main() {

#ifndef ONLINE_JUDGE
	freopen("Error.txt", "w", stderr);
#endif
    fastio();
   int t;
   cin >> t;
    while(t--){
        solve();
    }
   
}


