#include <iostream>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<pair<size_t, size_t>>> edges(n);

    for (size_t i = 0; i < m; ++i) {
        size_t u, v, w;
        cin >> u >> v >> w;
        --u; --v;
        edges[u].emplace_back(v, w);
        edges[v].emplace_back(u, w);
    }

    vector<size_t> d(n, numeric_limits<size_t>::max());
    d.front() = 0;

    set<pair<size_t, size_t>> q;

    for (size_t i = 0; i < n; ++i) {
        q.emplace(d[i], i);
    }

    vector<bool> a(n);

    while (!q.empty()) {
        size_t v = q.begin()->second;
        q.erase(q.begin());
        a[v] = true;

        for (auto [u, w] : edges[v]) {
            if (a[u]) {
                continue;
            }
            q.erase(make_pair(d[u], u));
            d[u] = min(d[u], d[v] + w);
            q.emplace(d[u], u);
        }
    }

    for (size_t i : d) {
        cout << i << ' ';
    }

    return 0;
}