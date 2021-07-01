#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Tree
{
    vector<vector<size_t>> edges;
    vector<size_t> sizes;
    vector<bool> centroids;
    vector<size_t> parents;

    constexpr static auto ROOT_PARENT = std::numeric_limits<size_t>::max();

    void hang(const size_t v, const size_t p = ROOT_PARENT)
    {
        sizes[v] = 1;

        for (auto &u : edges[v]) {
            if (u != p && !centroids[u]) {
                hang(u, v);
                sizes[v] += sizes[u];
            }
        }
    }

    [[nodiscard]] size_t centroid(const size_t v, const size_t s, const size_t p = ROOT_PARENT) const
    {
        for (auto &u : edges[v]) {
            if (u != p && !centroids[u] && sizes[u] > s) {
                return centroid(u, s, v);
            }
        }

        return v;
    }

public:
    explicit Tree(const size_t n) : edges(n), sizes(n), centroids(n), parents(n, ROOT_PARENT)
    {
    }

    void addEdge(const size_t u, const size_t v)
    {
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    void calculate(const size_t v, const size_t p = ROOT_PARENT)
    {
        hang(v);
        const auto c = centroid(v, sizes[v] / 2);
        centroids[c] = true;
        parents[c] = p == ROOT_PARENT ? 0 : p + 1;
        for (const auto u : edges[c]) {
            if (!centroids[u]) {
                calculate(u, c);
            }
        }
    }

    size_t getParent(const size_t v)
    {
        return parents[v];
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    cin >> n;

    Tree tree(n);

    for (size_t i = 1; i < n; ++i) {
        size_t u, v;
        cin >> u >> v;
        tree.addEdge(u - 1, v - 1);
    }

    tree.calculate(0);

    for (size_t i = 0; i < n; ++i) {
        cout << tree.getParent(i) << ' ';
    }

    return 0;
}