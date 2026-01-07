#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const long long INF = 1e18;

struct Edge {
    int to;
    int weight;
};

struct State {
    int node;
    long long max_edge;
    long long total_sum;

    // Custom priority logic: smaller max_edge first, then smaller total_sum
    bool operator>(const State& other) const {
        if (max_edge != other.max_edge) return max_edge > other.max_edge;
        return total_sum > other.total_sum;
    }
};

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;

    vector<vector<Edge>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // Assuming undirected based on "path" context
    }

    // dist_max[i] stores the minimum possible "maximum edge weight" to node i
    vector<long long> dist_max(n + 1, INF);
    // dist_sum[i] stores the minimum "total cost" for that dist_max[i]
    vector<long long> dist_sum(n + 1, INF);

    priority_queue<State, vector<State>, greater<State>> pq;

    // Initialization for source node 1
    dist_max[1] = 0;
    dist_sum[1] = 0;
    pq.push({1, 0, 0});

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        int u = current.node;
        long long d_max = current.max_edge;
        long long d_sum = current.total_sum;

        // Standard Dijkstra optimization
        if (d_max > dist_max[u] || (d_max == dist_max[u] && d_sum > dist_sum[u])) {
            continue;
        }

        for (auto& edge : adj[u]) {
            int v = edge.to;
            long long weight = edge.weight;

            // The new bottleneck (max edge) for this path
            long long new_max = max(d_max, weight);
            long long new_sum = d_sum + weight;

            // Relaxation Step
            // 1. If we found a smaller max edge weight
            // 2. Or if max edge weight is equal but total sum is smaller
            if (new_max < dist_max[v] || (new_max == dist_max[v] && new_sum < dist_sum[v])) {
                dist_max[v] = new_max;
                dist_sum[v] = new_sum;
                pq.push({v, dist_max[v], dist_sum[v]});
            }
        }
    }

    // Output results for every node from 2 to n
    for (int i = 2; i <= n; ++i) {
        if (dist_max[i] == INF) {
            cout << "Node " << i << ": Path not found" << endl;
        } else {
            cout << "Node " << i << ": " << dist_max[i] << " " << dist_sum[i] << endl;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}