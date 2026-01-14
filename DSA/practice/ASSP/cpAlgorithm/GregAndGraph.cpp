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
    ll n, m, q;
    cin >> n;
   vector<vector<ll>>graph(n+1, vector<ll>(n+1, INF));
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            cin >> graph[i][j];
        }
    }
    vector<vector<ll>>answer(graph);
    vector<ll>order(n,-1);
    for(int i = 0; i < n; i++){
        cin >> order[i];
    }
    reverse(all(order));
    vector<bool>present(n+1,false);
    ll ans = 0;
    vector<ll>stuffs;
    for(int k = 0; k < n; k++){
        present[order[k]] = true;
        for(int i = 1; i <= n; i++){
            if(present[i]){
                ans += answer[i][order[k]];
                ans += answer[order[k]][i];
            }
        }
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                if( answer[i][j] > answer[i][order[k]] + answer[order[k]][j] ){
                    
                    if(present[i] && present[j]){
                        ans += answer[i][order[k]] + answer[order[k]][j] - answer[i][j];
                    }
                    answer[i][j] =  answer[i][order[k]] + answer[order[k]][j];
                }
            }
        }

        stuffs.pb(ans);
    }

     reverse(all(stuffs));
        for(auto &var : stuffs){
            cout << var <<" ";
        }
        cout <<"\n";
}

int main(){
    fastio();
    solve();
 
}


