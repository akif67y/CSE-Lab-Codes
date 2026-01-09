#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

const long long INF = 1e18;

struct Edge {
    int to;
    int cost;
};

struct State {
    long long dist;
    int u, k1, k2, k3;

    // Custom comparator for min-priority queue
    bool operator>(const State& other) const {
        return dist > other.dist;
    }
};

void solve() {
    int n, m, K1, K2, K3, D;
    if (!(cin >> n >> m >> K1 >> K2 >> K3 >> D)) return;

    vector<vector<Edge>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].push_back({v, c});
        adj[v].push_back({u, c}); // Assuming undirected graph
    }

    // dist[node][k1_used][k2_used][k3_used]
    // Using a flat vector or a nested array depending on constraints
    // For readability, we'll use a 4D-like indexing or a 1D flattened array
    vector<long long> dist((n + 1) * (K1 + 1) * (K2 + 1) * (K3 + 1), INF);

    auto get_idx = [&](int u, int i, int j, int l) {
        return u * (K1 + 1) * (K2 + 1) * (K3 + 1) +
               i * (K2 + 1) * (K3 + 1) +
               j * (K3 + 1) +
               l;
    };

    priority_queue<State, vector<State>, greater<State>> pq;

    // Starting point: Node 1, 0 coupons used, distance 0
    int start_idx = get_idx(1, 0, 0, 0);
    dist[start_idx] = 0;
    pq.push({0, 1, 0, 0, 0});

    long long min_total_cost = INF;

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        int u = current.u;
        int i = current.k1;
        int j = current.k2;
        int l = current.k3;
        long long d = current.dist;

        if (d > dist[get_idx(u, i, j, l)]) continue;

        // If we reached the target node, track the minimum cost
        if (u == n) {
            min_total_cost = min(min_total_cost, d);
        }

        for (auto& edge : adj[u]) {
            int v = edge.to;
            int c = edge.cost;

            // Option 0: Use no coupon
            if (dist[get_idx(v, i, j, l)] > d + c) {
                dist[get_idx(v, i, j, l)] = d + c;
                pq.push({dist[get_idx(v, i, j, l)], v, i, j, l});
            }

            // Option 1: Use Type A (Reduce to c/2)
            if (i < K1) {
                int new_c = c / 2;
                if (dist[get_idx(v, i + 1, j, l)] > d + new_c) {
                    dist[get_idx(v, i + 1, j, l)] = d + new_c;
                    pq.push({dist[get_idx(v, i + 1, j, l)], v, i + 1, j, l});
                }
            }

            // Option 2: Use Type B (Reduce by fixed amount D)
            if (j < K2) {
                int new_c = max(0, c - D);
                if (dist[get_idx(v, i, j + 1, l)] > d + new_c) {
                    dist[get_idx(v, i, j + 1, l)] = d + new_c;
                    pq.push({dist[get_idx(v, i, j + 1, l)], v, i, j + 1, l});
                }
            }

            // Option 3: Use Type C (Reduce to c/3)
            if (l < K3) {
                int new_c = c / 3;
                if (dist[get_idx(v, i, j, l + 1)] > d + new_c) {
                    dist[get_idx(v, i, j, l + 1)] = d + new_c;
                    pq.push({dist[get_idx(v, i, j, l + 1)], v, i, j, l + 1});
                }
            }
        }
    }

    cout << min_total_cost << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}