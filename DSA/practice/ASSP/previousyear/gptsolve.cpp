#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1e15;

int main() {
    int N, M, K;
    long long X;
    if (!(cin >> N >> M >> K >> X)) return 0;

    vector<int> start_cities(K);
    for (int i = 0; i < K; i++) cin >> start_cities[i];

    vector<long long> hourly_rates(K);
    for (int i = 0; i < K; i++) cin >> hourly_rates[i];

    // dist[i][j] stores the shortest time between city i and j
    // next_node[i][j] stores the next city to visit from i to get to j
    vector<vector<long long>> dist(N + 1, vector<long long>(N + 1, INF));
    vector<vector<int>> next_node(N + 1, vector<int>(N + 1, -1));

    for (int i = 1; i <= N; i++) {
        dist[i][i] = 0;
        next_node[i][i] = i;
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        long long t;
        cin >> u >> v >> t;
        if (t < dist[u][v]) {
            dist[u][v] = dist[v][u] = t;
            next_node[u][v] = v;
            next_node[v][u] = u;
        }
    }

    // --- Floyd-Warshall Algorithm ---
    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next_node[i][j] = next_node[i][k];
                    }
                }
            }
        }
    }

    int best_city = -1;
    long long min_total_cost = INF;
    long long last_lord_time = 0;

    // --- Find the optimal meeting city ---
    for (int c = 1; c <= N; c++) {
        bool possible = true;
        long long current_total_cost = 0;
        long long max_time_to_reach = 0;

        for (int i = 0; i < K; i++) {
            long long travel_time = dist[start_cities[i]][c];
            if (travel_time > X) {
                possible = false;
                break;
            }
            current_total_cost += (travel_time * hourly_rates[i]);
            max_time_to_reach = max(max_time_to_reach, travel_time);
        }

        if (possible) {
            if (current_total_cost < min_total_cost) {
                min_total_cost = current_total_cost;
                best_city = c;
                last_lord_time = max_time_to_reach;
            }
        }
    }

    if (best_city == -1) {
        cout << "No meeting" << endl;
    } else {
        cout << best_city << " " << min_total_cost << " " << last_lord_time << endl;

        // --- Print paths for each lord ---
        for (int i = 0; i < K; i++) {
            int u = start_cities[i];
            int v = best_city;
            long long cost = dist[u][v] * hourly_rates[i];

            if (u == v) {
                cout << u << " 0" << endl;
            } else {
                int curr = u;
                while (curr != v) {
                    cout << curr << " -> ";
                    curr = next_node[curr][v];
                }
                cout << v << " " << cost << endl;
            }
        }
    }

    return 0;
}