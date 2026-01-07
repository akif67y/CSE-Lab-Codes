#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18; // Use a sufficiently large number for infinity

void solve(){
    ll n, m;
    cin >> n >> m;

    // Graph adjacency list
    vector<vector<pair<ll,ll>>> graph(n + 1);
    vector<ll> slowness(n + 1);

    for(ll i = 0; i < m; i++){
        ll a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back({c, b}); 
        graph[b].push_back({c, a}); 
    }

    for(int i = 1; i <= n; i++){
        cin >> slowness[i];
    }

    // dist[node][slowness]
    // Max slowness is 1000 based on constraints.
    vector<vector<ll>> distances(n + 1, vector<ll>(1001, INF));

    // Priority Queue: {time, {city, current_bike_slowness}}
    priority_queue<pair<ll, pair<ll, ll>>, 
                   vector<pair<ll, pair<ll, ll>>>, 
                   greater<pair<ll, pair<ll, ll>>>> pq;

    // Initial State: At city 1, holding bike from city 1
    ll start_slowness = slowness[1];
    distances[1][start_slowness] = 0;
    pq.push({0, {1, start_slowness}});

    ll ans = INF;

    while(!pq.empty()){
        ll d = pq.top().first;
        ll u = pq.top().second.first;
        ll s = pq.top().second.second; // The slowness we arrived with
        pq.pop();

        // If we found a shorter path to this state already, skip
        if(d > distances[u][s]) continue;

        // CRITICAL FIX: 
        // Before traveling, check if the bike at current city 'u' is faster
        // than the one we brought with us.
        ll current_s = min(s, slowness[u]);

        // If we reached the destination, record the answer
        if(u == n) {
            ans = min(ans, d);
        }

        for(auto& edge : graph[u]){
            ll w = edge.first;
            ll v = edge.second;

            // Travel time uses the BEST bike we have right now (current_s)
            ll new_time = d + w * current_s;

            // We arrive at 'v' still holding 'current_s'
            // We do not check slowness[v] here. That happens when we process node 'v' later.
            if(new_time < distances[v][current_s]){
                distances[v][current_s] = new_time;
                pq.push({new_time, {v, current_s}});
            }
        }
    }

    // Just in case the loop finishes without hitting N inside (standard Dijkstra handles this, 
    // but calculating min at the end is also fine).
    for(int i = 1; i <= 1000; i++){
        ans = min(ans, distances[n][i]);
    }
    
    cout << ans << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}