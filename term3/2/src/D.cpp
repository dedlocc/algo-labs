#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m, k, s;
    cin >> n >> m >> k >> s;
    --s;

    vector<vector<pair<size_t, int>>> edges(n);

    for (size_t i = 0; i < m; ++i) {
        size_t u, v;
        int w;
        cin >> u >> v >> w;
        edges[v - 1].emplace_back(u - 1, w);
    }

    const int INF = numeric_limits<int>::max();
    vector<vector<int>> d(k + 1, vector<int>(n, INF));
    d[0][s] = 0;

    for (size_t i = 0; i < k; ++i) {
        for (size_t v = 0; v < n; ++v) {
            for (auto [u, w] : edges[v]) {
                if (d[i][u] != INF) {
                    d[i + 1][v] = min(d[i + 1][v], d[i][u] + w);
                }
            }
        }
    }

    for (size_t i = 0; i < n; ++i) {
        if (d[k][i] == INF) {
            cout << -1;
        } else {
            cout << d[k][i];
        }
        cout << '\n';
    }

    return 0;
}