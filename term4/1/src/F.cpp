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
        edges[u].push_back(v);
    }

    size_t run()
    {
        for (size_t u = 0; u < lVisited.size(); ++u) {
            dfs1(u);
            fill(lVisited.begin(), lVisited.end(), false);
        }

        for (size_t u = 0; u < lMatching.size(); ++u) {
            if (lMatching[u] == NO_MATCHING) {
                dfs2(u);
            }
        }

        return count(lVisited.begin(), lVisited.end(), true) + count(rVisited.begin(), rVisited.end(), false);
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
    vector<vector<size_t>> edges;
    vector<size_t> lMatching, rMatching;
    vector<unsigned char> lVisited, rVisited;

    static constexpr size_t NO_MATCHING = -1;
};

struct Segment
{
    size_t x1, y1, x2, y2;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<Segment> horizontal, vertical;

    for (size_t i = 0; i < n; ++i) {
        size_t x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        (y1 == y2 ? horizontal : vertical).push_back(Segment{min(x1, x2), min(y1, y2), max(x1, x2), max(y1, y2)});
    }

    Kuhn kuhn(horizontal.size(), vertical.size());

    for (size_t i = 0; i < horizontal.size(); ++i) {
        auto const &h = horizontal[i];
        for (size_t j = 0; j < vertical.size(); ++j) {
            auto const &v = vertical[j];
            if (h.x1 <= v.x1 && h.x2 >= v.x1 && v.y1 <= h.y1 && v.y2 >= h.y1) {
                kuhn.addEdge(i, j);
            }
        }
    }

    cout << kuhn.run();

    return 0;
}