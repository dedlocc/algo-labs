#include <iostream>
#include <vector>
#include <iterator>
#include <unordered_map>

using namespace std;

struct Edge
{
    size_t from {};
    size_t to {};

    Edge() = default;
    Edge(size_t from, size_t to) : from(from), to(to)
    {}

    Edge operator+() const
    {
        return {min(from, to), max(from, to)};
    }

    bool operator==(const Edge &other) const
    {
        return from == other.from && to == other.to;
    }

    Edge operator!() const
    {
        return {to, from};
    }
};

namespace std
{
template<>
struct hash<Edge>
{
    size_t operator()(const Edge &e) const
    {
        return e.from * 20'000 + e.to;
    }
};
}

struct Graph
{
    explicit Graph(size_t n) : edges(n), marked(n), tIn(n), up(n)
    {}

    void addEdge(Edge e)
    {
        edges[e.from].push_back(e.to);
    }

    void dfs()
    {
        for (size_t u = 0; u < edges.size(); ++u) {
            if (!marked[u]) {
                dfs(u, u);
            }
        }
    }

    void dfs(size_t u, size_t p)
    {
        marked[u] = true;
        tIn[u] = tCounter++;
        up[u] = tIn[u];

        for (auto v : edges[u]) {
            if (v == p) {
                continue;
            }
            Edge cur(u, v);
            if (marked[v]) {
                up[u] = min(up[u], tIn[v]);
                if (tIn[v] < tIn[u]) {
                    buff.push_back(cur);
                }
            } else {
                buff.push_back(cur);
                dfs(v, u);
                up[u] = min(up[u], up[v]);
                if (up[v] >= tIn[u]) {
                    ++compCounter;
                    Edge e;
                    do {
                        e = buff.back();
                        buff.pop_back();
                        components[+e] = compCounter;
                    } while (e != cur);
                }
            }
        }
    }

    vector<vector<size_t>> edges;
    vector<bool> marked;
    size_t tCounter = 0;
    vector<size_t> tIn;
    vector<size_t> up;
    vector<Edge> buff;

    size_t compCounter = 0;
    unordered_map<Edge, size_t> components;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    Graph g(n);

    vector<Edge> edgeOrder;

    for (size_t i = 1; i <= m; ++i) {
        size_t u, v;
        cin >> u >> v;
        Edge e {u - 1, v - 1};
        g.addEdge(e);
        g.addEdge(!e);
        edgeOrder.push_back(e);
    }

    g.dfs();

    cout << g.compCounter << '\n';
    for (auto e : edgeOrder) {
        cout << g.components.at(+e) << ' ';
    }

    return 0;
}