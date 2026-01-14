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






void solve(){
    ll n, m, q;
    cin >> n;
    vector<vector<double>>graph(n+1, vector<double>(n+1, -INF));
    map<string,int>trackVertex;
    for(int i = 1; i <= n; i++){
        string temp;
        cin >> temp;
        trackVertex[temp] = i; //index of that vertex
    }
    cin >> m;
    for(int i = 0; i < m; i++){
        string u,v;
        double w;
        cin >> u >> w >> v;
        graph[trackVertex[u]][trackVertex[v]] = w;
        //graph[trackVertex[v]].pb(vertex(w,trackVertex[u]));
    }
    
    for(int i = 1; i <= n; i++){
        graph[i][i] = max(graph[i][i] , 1.0);
    }
  
    
    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
               if(graph[i][k] != -INF && graph[k][j] != -INF) graph[i][j] = max(graph[i][j], graph[i][k] * graph[k][j]);
            }
        }
    }
    bool yes = false;
    for(int i = 1; i <= n; i++){
        if(graph[i][i] > 1.0 + 1e-9){
            yes = true;
            break;
        }
    }
    if(yes){
        cout << "YES\n";
    }
    else{
        cout << "NO\n";
    }



}

int main() {
solve();
 
}


