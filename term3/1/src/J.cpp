#include <iostream>
#include <numeric>
#include <queue>
#include <vector>

using namespace std;

template <class T>
struct DSU
{
    explicit DSU(size_t n) : p(n), r(n)
    {
        iota(p.begin(), p.end(), 0);
    }

    T get(size_t i)
    {
        if (p[i] != i) {
            p[i] = get(p[i]);
        }
        return p[i];
    }

    void unite(size_t x, size_t y)
    {
        x = get(x);
        y = get(y);
        if (x == y) {
            return;
        }
        if (r[x] == r[y]) {
            ++r[x];
        }
        if (r[x] < r[y]) {
            p[x] = y;
        } else {
            p[y] = x;
        }
    }

private:
    vector<T> p;
    vector<unsigned> r;
};

struct Edge
{
    size_t from, to;
    uint64_t weight;

    std::strong_ordering operator<=>(const Edge &other) const
    {
        return other.weight <=> weight;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    priority_queue<Edge> edges;

    for (size_t i = 0; i < m; ++i) {
        Edge e;
        cin >> e.from >> e.to >> e.weight;
        --e.from;
        --e.to;
        edges.push(e);
    }

    DSU<size_t> dsu(n);
    uint64_t sum = 0;

    for (size_t i = 1; i < n; ++i) {
        Edge e;
        do {
            e = edges.top();
            edges.pop();
        } while (dsu.get(e.from) == dsu.get(e.to));

        dsu.unite(e.from, e.to);
        sum += e.weight;
    }

    cout << sum;

    return 0;
}