#include <iostream>
#include <utility>
#include <vector>

using namespace std;

struct Kuhn
{
    explicit Kuhn(size_t n, size_t m) : edges(m), matching(n, NO_MATCHING), visited(m)
    {}

    void addEdge(size_t u, size_t v)
    {
        edges[v].push_back(u);
    }

    vector<pair<size_t, size_t>> run()
    {
        for (size_t v = 0; v < edges.size(); ++v) {
            fill(visited.begin(), visited.end(), false);
            dfs(v);
        }

        vector<pair<size_t, size_t>> result;
        for (size_t v = 0; v < matching.size(); ++v) {
            if (matching[v] != NO_MATCHING) {
                result.emplace_back(v, matching[v]);
            }
        }
        return result;
    }

private:
    bool dfs(size_t u)
    {
        if (exchange(visited[u], true)) {
            return false;
        }

        for (auto v : edges[u]) {
            if (matching[v] == NO_MATCHING || dfs(matching[v])) {
                matching[v] = u;
                return true;
            }
        }
        return false;
    }

private:
    vector<vector<size_t>> edges;
    vector<size_t> matching;
    vector<unsigned char> visited;

    static constexpr size_t NO_MATCHING = -1;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    Kuhn kuhn(n, m);

    for (size_t u = 0; u < n; ++u) {
        size_t v;
        while (cin >> v && v) {
            kuhn.addEdge(u, v - 1);
        }
    }

    auto matching = kuhn.run();
    cout << matching.size() << '\n';

    for (auto [u, v] : matching) {
        cout << u + 1 << ' ' << v + 1 << '\n';
    }

    return 0;
}