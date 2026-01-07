#include<bits/stdc++.h>

using namespace std;

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
    

    for(ll i = 0; i < m; i++){
        ll a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back({c, b});  
    }
    debug(graph);

    

    priority_queue<pair<ll,pair<ll,ll>>, vector<pair<ll,pair<ll,ll>>>, greater<pair<ll,pair<ll,ll>>>> pq; 
    //{weight, {city, smallest s(i)}}
    vector<vector<ll>> distances(n + 1, vector<ll>(3, INF));
   // vector<ll> distances(n+1, INF); 
    // vector<int> parents(n+1, -1);

  /*  auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
    if (a.first != b.first) return a.first > b.first; -- this logic creates a min priority queue
    return a.second > b.second;
    };  

    // You still need decltype and you must pass 'cmp' to the constructor
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);*/
    
    distances[s][0] = 0;

    pq.push({0, {s, 0}});
    ll count = 0;
    while(!pq.empty()){
        ll d = pq.top().first;
        ll u = pq.top().second.first; //city
        ll state = pq.top().second.second;
        pq.pop();
        debug(d);
        debug(u);
        debug(state);
        count++;

        if(d > distances[u][state]) continue;
        

        for(auto& edge : graph[u]){
            
            ll weight = edge.first;
            ll v = edge.second;
            if(state == 0 || state == 1){
                //use coupon
             if(distances[u][state] + (weight/2) < distances[v][state + 1]){
                distances[v][state + 1] = distances[u][state] + (weight/2);
                pq.push({distances[v][state + 1], {v, state + 1}});
                
            } 
            }

            //don't use it
            if(distances[u][state] + weight < distances[v][state]){
                distances[v][state] = distances[u][state] + (weight);
                pq.push({distances[v][state], {v, state}});
            } 
           
        }
    }
    debug(count);
    
    cout << min(min(distances[n][1], distances[n][2] ), distances[n][0]) <<"\n";
 
}

int main() {

#ifndef ONLINE_JUDGE
	freopen("Error.txt", "w", stderr);
#endif
    fastio();
    solve();
   
}


