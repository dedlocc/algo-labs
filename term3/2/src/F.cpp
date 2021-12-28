#include <iostream>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

using Edges = vector<vector<pair<size_t, size_t>>>;

const size_t NO_PATH = numeric_limits<size_t>::max();

vector<size_t> dijkstra(const Edges &edges, size_t s)
{
    const size_t n = edges.size();

    vector<size_t> d(n, NO_PATH);
    set<pair<size_t, size_t>> q;

    q.emplace(d[s] = 0, s);

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

    return d;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    Edges edges(n);

    for (size_t i = 0; i < m; ++i) {
        size_t u, v, w;
        cin >> u >> v >> w;
        --u; --v;
        edges[u].emplace_back(v, w);
        edges[v].emplace_back(u, w);
    }

    size_t a, b, c;
    cin >> a >> b >> c;

    auto da = dijkstra(edges, --a);
    auto ab = da[--b];
    auto ac = da[--c];
    auto bc = dijkstra(edges, b)[c];

    if (ab == NO_PATH || ac == NO_PATH || bc == NO_PATH) {
        cout << -1;
    } else {
        cout << min({ab + ac, ab + bc, ac + bc});
    }

    return 0;
}