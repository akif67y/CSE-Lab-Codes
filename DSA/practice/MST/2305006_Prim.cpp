#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;
#define ll long long
const ll INF = 1e9;

class Edge {
public:
    ll w, to, from;
    Edge(ll weight, ll target, ll source) {
        w = weight;
        to = target;
        from = source;
    }
    // Operator overload for min-heap (Smallest weight on top)
    bool operator>(const Edge& other) const {
        return w > other.w;
    }
};

void prim() {
    ll n, m;
    cin >> n >> m;

    vector<vector<pair<ll, ll>>> adj(n + 1);

    for (ll i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
    }

    ll root;
    cin >> root;

    ll total_weight = 0;
    vector<ll> min_w(n + 1, INF);
    vector<bool> selected(n + 1, false);
    vector<Edge> MST;

    min_w[root] = 0;
    
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    pq.push({0, root, -1});

    ll edges_count = 0;

    while (!pq.empty()) {
        Edge top = pq.top();
        pq.pop();

        ll w = top.w;
        ll u = top.to;
        ll parent = top.from;

        // If node u is already included in MST, skip it
        if (selected[u]) {
            continue;
        }

        selected[u] = true;
        total_weight += w;

        if (parent != -1) {
            MST.push_back(top);
            edges_count++;
        }

        for (auto& edge : adj[u]) {
            ll weight = edge.first;
            ll v = edge.second;
            
            if (!selected[v] && weight < min_w[v]) {
                min_w[v] = weight;
                pq.push({weight, v, u});
            }
        }
    }

   
    if (edges_count != n - 1) {
        cout << "No MST!" << endl;
    } else {
        cout << "Total weight " << total_weight << endl;
        cout << "Root node " << root << "\n";
        for (auto& var : MST) {
            cout << var.from << " " << var.to << "\n";
        }
    }
}

ll main() {
    prim();
    return 0;
}