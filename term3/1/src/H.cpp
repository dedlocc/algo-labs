#include <iostream>
#include <vector>

using namespace std;

struct Graph
{
    explicit Graph(size_t n) : edges(n), backEdges(n), marked(n)
    {}

    void addEdge(size_t from, size_t to, size_t weight)
    {
        edges[from].emplace_back(to, weight);
        backEdges[to].emplace_back(from, weight);
    }

    bool dfs(size_t max)
    {
        fill(marked.begin(), marked.end(), false);
        dfs1(0, max);
        if (find(marked.begin(), marked.end(), false) != marked.end()) {
            return false;
        }
        fill(marked.begin(), marked.end(), false);
        dfs2(0, max);
        if (find(marked.begin(), marked.end(), false) != marked.end()) {
            return false;
        }
        return true;
    }

private:
    void dfs1(size_t u, size_t max)
    {
        marked[u] = true;
        for (auto [v, w] : edges[u]) {
            if (w <= max && !marked[v]) {
                dfs1(v, max);
            }
        }
    }

    void dfs2(size_t u, size_t max)
    {
        marked[u] = true;
        for (auto [v, w] : backEdges[u]) {
            if (w <= max && !marked[v]) {
                dfs2(v, max);
            }
        }
    }

    vector<vector<pair<size_t, size_t>>> edges;
    vector<vector<pair<size_t, size_t>>> backEdges;
    vector<bool> marked;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    cin >> n;

    Graph g(n);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            unsigned w;
            cin >> w;
            if (i != j) {
                g.addEdge(i, j, w);
            }
        }
    }

    if (n == 1 || g.dfs(0)) {
        cout << 0;
        return 0;
    }

    size_t l = 0, r = 1e9 - 1;
    while (l + 1 < r) {
        size_t m = (l + r) / 2;

        if (g.dfs(m)) {
            r = m;
        } else {
            l = m;
        }
    }

    cout << r;

    return 0;
}