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
    
    if(start == end){
        cout << start;
        return;
    }
    cout << start <<"->";
    ll i = start;
    ll j = end;
    ll count = 0;
    while(true){
        count++;
        if(next[i][j] == j){break;}
        i = next[i][j];
        
    }
    ll count2 = 0;
    i = start;
    while(true){
        count2++;
        if(count2 == count){
            cout << next[i][j];
            break;
        }
        else{
            cout << next[i][j]<<"->";
        }
        i = next[i][j];
    }
    
}


void solve(){
    ll n, m;
    cin >> n >> m ;
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
    ll u1,v1,w1;
    cin >> u1 >> v1;
    w1 = graph[u1][v1];

    
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
    

    while(true){
        ll x,y;
        cin >> x >> y;
        if(x == -1 && y == -1) break;
        ll minval = INF;
        ll minstate = -1;
        if(graph[x][u1] != INF && graph[v1][y] != INF){
            minval = graph[x][u1] + graph[v1][y] + w1;
            minstate = 1;
        }
        if(graph[x][v1] != INF && graph[u1][y] != INF &&  graph[x][v1] + graph[u1][y] + w1 < minval ){
            minval =  graph[x][v1] + graph[u1][y] + w1 ;
            minstate = 2;
        }
        if(minstate == -1){
            cout <<"No path from " << x <<" to "<< y <<" through wall street\n\n";
        }
        else if(minstate == 1){
            cout <<"shortest path weight : "<< minval<<"\n";
            cout <<"Path : ";
            printPath(x,u1,next);
            cout <<"->";
            printPath(v1,y,next);
            cout <<"\n\n";
        }
         else if(minstate == 2){
            cout <<"Shortest path weight : "<< minval<<"\n";
            cout <<"Path : ";
            printPath(x,v1,next);
            cout <<"->";
            printPath(u1,y,next);
            cout <<"\n\n";
        }
    }
   
    
}

int main() {
solve();
 
}


