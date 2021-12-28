#include <iostream>
#include <numeric>
#include <set>
#include <vector>
#include <queue>

using namespace std;

using weight_t = int64_t;
constexpr weight_t INF_WEIGHT = numeric_limits<weight_t>::max();

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m, s;
    cin >> n >> m >> s;

    vector<vector<pair<size_t, weight_t>>> edges(n);

    for (size_t i = 0; i < m; ++i) {
        size_t u, v;
        weight_t w;
        cin >> u >> v >> w;
        edges[u - 1].emplace_back(v - 1, w);
    }

    vector<weight_t> d(n, INF_WEIGHT);
    d[s - 1] = 0;

    for (size_t i = 1; i < n; ++i) {
        for (size_t u = 0; u < n; ++u) {
            for (auto [v, w] : edges[u]) {
                if (d[u] != INF_WEIGHT) {
                    d[v] = min(d[v], d[u] + w);
                }
            }
        }
    }

    queue<size_t> q;
    vector<bool> neg(n);

    for (size_t u = 0; u < n; ++u) {
        for (auto [v, w] : edges[u]) {
            if (!neg[v] && d[u] != INF_WEIGHT && d[v] > d[u] + w) {
                q.push(v);
                neg[v] = true;
            }
        }
    }

    while (!q.empty()) {
        auto u = q.front();
        q.pop();

        for (auto [v, _] : edges[u]) {
            if (!neg[v]) {
                q.push(v);
                neg[v] = true;
            }
        }
    }

    for (size_t i = 0; i < n; ++i) {
        if (d[i] == INF_WEIGHT) {
            cout << '*';
        } else if (neg[i]) {
            cout << '-';
        } else  {
            cout << d[i];
        }
        cout << '\n';
    }

    return 0;
}