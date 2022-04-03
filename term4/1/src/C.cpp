#include <experimental/iterator>
#include <iostream>
#include <utility>
#include <unordered_set>
#include <vector>

using namespace std;

struct Kuhn
{
    explicit Kuhn(size_t n, size_t m) : edges(n), lMatching(n, NO_MATCHING), rMatching(m, NO_MATCHING), lVisited(n), rVisited(m)
    {}

    void addEdge(size_t u, size_t v)
    {
        edges[u].insert(v);
    }

    pair<vector<size_t>, vector<size_t>> run()
    {
        size_t m = rMatching.size();
        for (auto &e : edges) {
            for (size_t v = 0; v < m; ++v) {
                if (auto [it, ins] = e.insert(v); !ins) {
                    e.erase(it);
                }
            }
        }

        for (size_t u = 0; u < lVisited.size(); ++u) {
            dfs1(u);
            fill(lVisited.begin(), lVisited.end(), false);
        }

        for (size_t u = 0; u < lMatching.size(); ++u) {
            if (lMatching[u] == NO_MATCHING) {
                dfs2(u);
            }
        }

        pair<vector<size_t>, vector<size_t>> result;
        for (size_t u = 0; u < lVisited.size(); ++u) {
            if (lVisited[u]) {
                result.first.push_back(u);
            }
        }
        for (size_t v = 0; v < rVisited.size(); ++v) {
            if (!rVisited[v]) {
                result.second.push_back(v);
            }
        }

        return result;
    }

private:
    bool dfs1(size_t u)
    {
        if (exchange(lVisited[u], true)) {
            return false;
        }

        for (auto v : edges[u]) {
            if (rMatching[v] == NO_MATCHING || dfs1(rMatching[v])) {
                rMatching[v] = u;
                lMatching[u] = v;
                return true;
            }
        }
        return false;
    }

    void dfs2(size_t u)
    {
        if (u == NO_MATCHING || exchange(lVisited[u], true)) {
            return;
        }

        for (auto v : edges[u]) {
            if (auto &w = rMatching[v]; w != u && !exchange(rVisited[v], true)) {
                dfs2(w);
            }
        }
    }

private:
    vector<unordered_set<size_t>> edges;
    vector<size_t> lMatching, rMatching;
    vector<unsigned char> lVisited, rVisited;

    static constexpr size_t NO_MATCHING = -1;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t k;
    cin >> k;

    for (size_t i = 0; i < k; ++i) {
        size_t n, m;
        cin >> n >> m;

        Kuhn kuhn(n, m);

        for (size_t u = 0; u < n; ++u) {
            size_t v;
            while (cin >> v && v) {
                kuhn.addEdge(u, v - 1);
            }
        }

        auto [left, right] = kuhn.run();

        cout << left.size() + right.size() << '\n';
        cout << left.size() << ' ' << right.size() << '\n';
        transform(left.begin(), left.end(), experimental::make_ostream_joiner(cout, " "), [](size_t i) { return i + 1; });
        cout << '\n';
        transform(right.begin(), right.end(), experimental::make_ostream_joiner(cout, " "), [](size_t i) { return i + 1; });
        cout << '\n';

        cout << '\n';
    }

    return 0;
}