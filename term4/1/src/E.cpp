#include <iostream>
#include <utility>
#include <vector>

using namespace std;

struct Kuhn
{
    explicit Kuhn(size_t n, size_t m) : m(m), edges(n * m), matching(n * m, NO_MATCHING), visited(n * m)
    {}

    void addEdge(size_t x1, size_t y1, size_t x2, size_t y2)
    {
        size_t v1 = y1 * m + x1;
        size_t v2 = y2 * m + x2;
        edges[v1].push_back(v2);
        edges[v2].push_back(v1);
    }

    size_t run()
    {
        for (size_t v = 0; v < edges.size(); ++v) {
            fill(visited.begin(), visited.end(), false);
            dfs(v);
        }

        return std::count_if(matching.begin(), matching.end(), [](size_t v) {
            return v != NO_MATCHING;
        }) / 2;
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
    size_t m;
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
    int a, b;
    cin >> n >> m >> a >> b;

    Kuhn kuhn(n, m);

    vector<unsigned char> line(m);
    int empty = 0;

    for (size_t y = 0; y < n; ++y) {
        for (size_t x = 0; x < m; ++x) {
            char c;
            cin >> c;
            if (c == '.') {
                line[x] = false;
                continue;
            }
            ++empty;
            if (exchange(line[x], true)) {
                kuhn.addEdge(x, y, x, y - 1);
            }
            if (x != 0 && line[x - 1]) {
                kuhn.addEdge(x, y, x - 1, y);
            }
        }
    }

    cout << [&] {
        if (b * 2 <= a) {
            return empty * b;
        } else {
            int matchingSize = kuhn.run();
            return matchingSize * a + (empty - matchingSize * 2) * b;
        }
    }();

    return 0;
}