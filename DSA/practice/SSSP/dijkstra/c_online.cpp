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
    ll m1, m2, w;

    vector<vector<pair<ll,ll>>> graph(n+1);
    

    for(ll i = 0; i < m; i++){
        ll a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back({c, b});  
    }
    cin >> m1 >> m2 >> w;
    

    priority_queue<pair<ll,pair<ll,ll>>, vector<pair<ll,pair<ll,ll>>>, greater<pair<ll,pair<ll,ll>>>> pq; 
    //{weight, {city, smallest s(i)}}
    ll distances[n+1][2];
    for(auto &var : distances){
        for(auto &var2 : var){
            var2 = INF;
        }
    }
   // vector<ll> distances(n+1, INF); 
    // vector<int> parents(n+1, -1);
    
    distances[s][1] = 0;
    pq.push({0, {s, 1}});

    while(!pq.empty()){
        ll d = pq.top().first;
        ll u = pq.top().second.first; //city
        ll state = pq.top().second.second;
        pq.pop();


        if(d > distances[u][state]) continue;

        for(auto& edge : graph[u]){
            ll weight = edge.first;
            ll v = edge.second;
            if(state == 1){
                //use coupon
             if(distances[u][state] + (weight/2) < distances[v][0]){
                distances[v][0] = distances[u][state] + (weight/2);
                pq.push({distances[v][0], {v, 0}});
            } 
            //don't use it
            if(distances[u][state] + weight < distances[v][1]){
                distances[v][1] = distances[u][state] + (weight);
                pq.push({distances[v][1], {v, 1}});
            }
            }
            else{
                //no coupon
                if(distances[u][state] + weight < distances[v][0]){
                distances[v][0] = distances[u][state] + (weight);
                pq.push({distances[v][0], {v, 0}});
                }   
            }
        }
    }

    priority_queue<pair<ll,pair<ll,ll>>, vector<pair<ll,pair<ll,ll>>>, greater<pair<ll,pair<ll,ll>>>> pq2; 
    //{weight, {city, smallest s(i)}}
    ll distances2[n+1][2];
    for(auto &var : distances2){
        for(auto &var2 : var){
            var2 = INF;
        }
    }
   // vector<ll> distances2(n+1, INF); 
    // vector<int> parents(n+1, -1);
    s = m2;
    distances2[s][1] = 0;
    pq2.push({0, {s, 1}});

    while(!pq2.empty()){
        ll d = pq2.top().first;
        ll u = pq2.top().second.first; //city
        ll state = pq2.top().second.second;
        pq2.pop();


        if(d > distances2[u][state]) continue;

        for(auto& edge : graph[u]){
            ll weight = edge.first;
            ll v = edge.second;
            if(state == 1){
                //use coupon
             if(distances2[u][state] + (weight/2) < distances2[v][0]){
                distances2[v][0] = distances2[u][state] + (weight/2);
                pq2.push({distances2[v][0], {v, 0}});
            } 
            //don't use it
            if(distances2[u][state] + weight < distances2[v][1]){
                distances2[v][1] = distances2[u][state] + (weight);
                pq2.push({distances2[v][1], {v, 1}});
            }
            }
            else{
                //no coupon
                if(distances2[u][state] + weight < distances2[v][0]){
                distances2[v][0] = distances2[u][state] + (weight);
                pq2.push({distances2[v][0], {v, 0}});
                }   
            }
        }
    }

    ll ans = min({
        distances[m1][1] + w/2 + distances2[n][1], 
        distances[m1][0] + w + distances2[n][1],
        distances[m1][1] + w + distances2[n][0]
    });

    cout << ans <<"\n";


    
    
 
}

int main() {

#ifndef ONLINE_JUDGE
	freopen("Error.txt", "w", stderr);
#endif
    fastio();
    solve();
   
}


