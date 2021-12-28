#include <iostream>
#include <unordered_map>
#include <vector>
#include <optional>

using namespace std;

struct Data
{
    explicit Data(size_t n) : n(n), edges(n), grundy(n)
    {}

    void addEdge(size_t u, size_t v)
    {
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    void dfs(size_t u, size_t p)
    {
        for (auto v : edges[u]) {
            if (v == p) {
                continue;
            }
            dfs(v, u);
            grundy[u] ^= grundy[v] + 1;
        }
    }

    optional<pair<size_t, size_t>> dfs2(size_t u, size_t p, size_t g = 0)
    {
        g ^= grundy[u];
        for (auto v : edges[u]) {
            if (v == p) {
                continue;
            }

            size_t gv = (g ^ (grundy[v] + 1)) - 1;

            if (gv == -1) {
                return make_pair(u, v);
            }

            if (auto opt = dfs2(v, u, gv)) {
                return opt;
            }
        }
        return {};
    }

    size_t n;
    vector<vector<size_t>> edges;
    vector<size_t> grundy;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, r;
    cin >> n >> r;
    --r;

    Data data(n);
    unordered_map<size_t, size_t> edgesOrder;

    for (size_t i = 1; i < n; ++i) {
        size_t x, y;
        cin >> x >> y;
        data.addEdge(--x, --y);
        edgesOrder[x * n + y] = edgesOrder[y * n + x] = i;
    }

    data.dfs(r, n);

    if (data.grundy[r] == 0) {
        cout << 2;
    } else {
        auto [u, v] = *data.dfs2(r, n);
        cout << "1\n" << edgesOrder[u * n + v];
    }

    return 0;
}