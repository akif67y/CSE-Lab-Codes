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
    ll node;
    vertex(ll w, ll node){
        this->w = w;
        this->node = node;
    }

};




void solve(){
    ll n, m;
    cin >> n >> m;
   vector<vector<ll>>graph(n+1, vector<ll>(n+1, INF));
    for(int i = 0; i < m; i++){
        ll u,v,w;
        cin >> u >> v >> w;
        graph[u][v] = min(w,graph[u][v]);
    }
    
    for(int i = 0; i <= n; i++){
        graph[i][i] = min(graph[i][i], (ll)0);
    }
    
    for(int k = 0; k <= n; k++){
        for(int i = 0; i <= n; i++){
            for(int j = 0; j <= n; j++){
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
            }
        }
    }
    for(int i = 0; i <= n; i++){
        if(graph[i][i] < 0){
            cout<<"YES\n";
            return;
        }
    }
    cout <<"NO\n";


  
}

int main() {
solve();
 
}


