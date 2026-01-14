//{took 20 minutes to implement}

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



#define M 100000007  //might need to change this;


class vertex{
    public :
    ll w;
    ll u;
    ll v;
    vertex(ll w, ll u, ll v ){
        this->w = w;
        this->u = u;
        this->v = v;
    }

};

bool comparatorfnc(vertex a, vertex b){
    return a.w > b.w;
}




void solve(){
    ll n, m, k;
    cin >> n >> m >> k;
    vector<vector<ll>>graph(n+1, vector<ll>(n+1, INF));
    vector<ll>armiesidx(n+1,-1);
    vector<ll>targetidx(n+1,-1);
    for(int i = 1; i <= n; i++){
        cin >> armiesidx[i];
    }
    for(int i = 1; i <= n; i++){
        cin >> targetidx[i];
    }

    for(int i = 0; i < m; i++){
        ll u,v,w;
        cin >> u >> v >> w;
        graph[u][v] = min(w,graph[u][v]);
    }
    
    for(int i = 1; i <= n; i++){
        graph[i][i] = min(graph[i][i], (ll)0);
    }
    
    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
            }
        }
    }
    vector<vertex>armyTransport;
    for(int i = 1; i <= n;i++){
        ll u = armiesidx[i];
        ll v = targetidx[i];
        ll w = graph[u][v];
        if(w != INF){
            armyTransport.pb(vertex(w,u,v));
        }
    }
    sort(all(armyTransport), comparatorfnc);
    ll costfk = 1;
    ll minsum = 0;
    for(int i = 0; i < armyTransport.size(); i++){
        if(i > 0 && i % k == 0){
            costfk *= 2;
        }
        minsum += armyTransport[i].w * costfk;
    } 

    cout << minsum <<"\n";


 
}

int main() {
solve();
 
}


