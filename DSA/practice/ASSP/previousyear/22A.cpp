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

void printPath(ll start, ll end, vector<vector<ll>>&next){
    cout << start;
    ll i = start;
    ll j = end;
    cout << start;
    int curr = start;
    while (curr != end) {
        curr = next[curr][end];
        cout << "->" << curr;
    }
    cout << endl;
    
}


void solve(){
    ll n, m, k, x;
    cin >> n >> m >> k >> x;
    vector<ll>lords(k+1,-1);
    vector<ll>rates(k+1,0);
    for(int i = 1; i <= k;i++){
        cin >> lords[i];
    }
    for(int i = 1; i <= k;i++){
        cin >> rates[i];
    }
   vector<vector<ll>>graph(n+1, vector<ll>(n+1, INF));
   vector<vector<ll>>next(n+1, vector<ll>(n+1,-1));
    for(int i = 0; i < m; i++){
        ll u,v,w;
        cin >> u >> v >> w;
        graph[u][v] = w;
        next[u][v] = v;
        graph[v][u] = w;
        next[v][u] = u;
    }
    
    for(int i = 1; i <= n; i++){
       graph[i][i] = 0;
        next[i][i] = i; //modification needed
    }
    
    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                if(graph[i][k] != INF && graph[k][j] != INF){
                    if(graph[i][j] > graph[i][k] + graph[k][j] ){
                        next[i][j] = next[i][k];
                    }
                    graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]); 
                }  
            }
        }
    }
    ll mincost = INF;
    ll answer = -1;
    ll maxtime = -INF;
    for(int i = 1; i <= n; i++){
        bool possible = true;
        ll totalcost = 0;
        ll maxlord = -INF;
        for(int j = 1; j <= k; j++){
            if(graph[lords[j]][i] == INF || graph[lords[j]][i] > x){
                possible = false;
            }
            if(possible) {
                totalcost += rates[j]*graph[lords[j]][i];
                maxlord = max(maxlord,graph[lords[j]][i] );
            }
        }
        if(possible && totalcost < mincost){
            answer = i;
            mincost = totalcost;
            maxtime = max(maxtime, maxlord);
        }
    }
    
    if(answer == -1){
        cout <<"NO MEETING\n";
        return;
    }
    cout << answer <<" "<< mincost <<" "<< maxtime <<"\n";
    for(int i = 1; i <= k; i++){
        printPath(lords[i], answer, next); 
        cout <<" "<<  graph[lords[i]][answer]* rates[i] <<"\n";
    }
    
}

int main() {
solve();
 
}


