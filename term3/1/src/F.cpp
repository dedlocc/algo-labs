#include <iostream>
#include <ranges>
#include <vector>
#include <unordered_set>

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
    explicit Graph(size_t n) : edges(n), backEdges(n), marked(n), components(n)
    {}

    void addEdge(Edge e)
    {
        edges[e.from].push_back(e.to);
        backEdges[e.to].push_back(e.from);
    }

    void dfs()
    {
        for (size_t u = 0; u < edges.size(); ++u) {
            dfs1(u);
        }
        for (auto u : ord | views::reverse) {
            if (components[u] == 0) {
                ++compCounter;
                dfs2(u);
            }
        }
    }

    void dfs1(size_t u)
    {
        if (!marked[u]) {
            marked[u] = true;
            for (auto v : edges[u]) {
                dfs1(v);
            }
            ord.push_back(u);
        }
    }

    void dfs2(size_t u)
    {
        components[u] = compCounter;
        for (auto v : backEdges[u]) {
            auto cv = components[v];
            auto cu = components[u];
            if (cv == 0) {
                dfs2(v);
            } else if (cv != cu) {
                answer.emplace(cu, cv);
            }
        }
    }

    vector<vector<size_t>> edges;
    vector<vector<size_t>> backEdges;
    vector<bool> marked;

    vector<size_t> ord;

    size_t compCounter = 0;
    vector<size_t> components;
    unordered_set<Edge> answer;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    Graph g(n);

    for (size_t i = 1; i <= m; ++i) {
        size_t u, v;
        cin >> u >> v;
        Edge e {u - 1, v - 1};
        g.addEdge(e);
    }

    g.dfs();

    cout << g.answer.size();

    return 0;
}