#include <iostream>
#include <unordered_set>
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

    size_t m, k, n;
    cin >> m >> k >> n;

    size_t t;
    cin >> t;

    unordered_set<size_t> bad;
    bad.reserve(t);

    for (size_t i = 0; i < t; ++i) {
        size_t a, b;
        cin >> a >> b;
        bad.emplace((a - 1) * 200 + b - m - 1);
    }

    size_t q;
    cin >> q;

    unordered_set<size_t> notLonely;

    for (size_t i = 0; i < q; ++i) {
        size_t a;
        cin >> a;
        notLonely.insert(a - 1);
    }

    Kuhn kuhn(m + k - n, m + k - n);

    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < k; ++j) {
            if (!bad.contains(i * 200 + j)) {
                kuhn.addEdge(i, j);
            }
        }
    }

    for (size_t i = 0; i < m; ++i) {
        if (!notLonely.contains(i)) {
            for (size_t j = k; j < m + k - n; ++j) {
                kuhn.addEdge(i, j);
            }
        }
    }

    for (size_t i = 0; i < k; ++i) {
        if (!notLonely.contains(m + i)) {
            for (size_t j = m; j < m + k - n; ++j) {
                kuhn.addEdge(j, i);
            }
        }
    }

    auto matching = kuhn.run();

    if (matching.size() != m + k - n) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        for (auto [u, v] : matching) {
            if (u < m && v < k) {
                cout << (u + 1) << ' ' << (v + m + 1) << '\n';
            }
        }
    }

    return 0;
}