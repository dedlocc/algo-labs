#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

struct Data
{
    explicit Data(size_t n) : n(n), edges(n), visited(n), grundy(n)
    {}

    void addEdge(size_t u, size_t v)
    {
        edges[u].push_back(v);
    }

    void dfs(size_t u)
    {
        if (visited[u]) {
            return;
        }
        visited[u] = true;

        unordered_set<size_t> mex;

        for (auto v : edges[u]) {
            dfs(v);
            mex.insert(grundy[v]);
        }

        while (mex.contains(grundy[u])) {
            ++grundy[u];
        }
    }

    size_t n;
    vector<vector<size_t>> edges;
    vector<bool> visited;
    vector<size_t> grundy;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    Data data(n);

    for (size_t i = 0; i < m; ++i) {
        size_t x, y;
        cin >> x >> y;
        data.addEdge(x - 1, y - 1);
    }

    for (size_t i = 0; i < n; ++i) {
        data.dfs(i);
    }

    for (auto g : data.grundy) {
        cout << g << '\n';
    }

    return 0;
}