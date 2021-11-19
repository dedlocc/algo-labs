#include <iostream>
#include <vector>
#include <iterator>
#include <unordered_map>
#include <set>

using namespace std;

struct Edge
{
    size_t from {};
    size_t to {};

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
    bool operator()(const Edge &e) const
    {
        return e.from * 20'000 + e.to;
    }
};
}

struct DFSVisitor
{
    virtual void vertexRoot(size_t v) {}
    virtual void vertexDiscovered(size_t v) {}
    virtual void vertexFinished(size_t v) {}

    virtual void edgeDiscovered(Edge e) {}
    virtual void edgeFinished(Edge e) {}

    virtual void edgeForward(Edge e) {}
    virtual void edgeBack(Edge e) {}
    virtual void edgeMet(Edge e, bool cycle) {}
};

class Graph
{
    using Neighbors = vector<size_t>;
    using Edges = vector<Neighbors>;

    enum class Color
    {
        UNMET,
        IN_PROCESS,
        FINISHED,
    };

public:
    explicit Graph(size_t n) : edges(n, Neighbors())
    {}

    void addEdge(Edge e)
    {
        edges[e.from].push_back(e.to);
    }

    void dfs(DFSVisitor &visitor) const
    {
        vector<Color> colors(edges.size());
        for (size_t v = 0; v < edges.size(); ++v) {
            if (colors[v] == Color::UNMET) {
                visitor.vertexRoot(v);
                dfs(v, colors, visitor);
            }
        }
    }

private:
    void dfs(size_t u, vector<Color> &colors, DFSVisitor &visitor) const
    {
        colors[u] = Color::IN_PROCESS;
        visitor.vertexDiscovered(u);

        for (size_t v : edges[u]) {
            Edge e {u, v};
            visitor.edgeDiscovered(e);
            if (colors[v] == Color::UNMET) {
                visitor.edgeForward(e);
                dfs(v, colors, visitor);
                visitor.edgeBack(e);
            } else {
                visitor.edgeMet(e, colors[v] == Color::IN_PROCESS);
            }
            visitor.edgeFinished(e);
        }

        colors[u] = Color::FINISHED;
        visitor.vertexFinished(u);
    }

    Edges edges;
};

struct BridgeVisitor : DFSVisitor
{
    explicit BridgeVisitor(size_t n) : tIn(n), up(n)
    {}

    void vertexDiscovered(size_t u) override
    {
        up[u] = tIn[u] = tCounter++;
    }

    void edgeForward(Edge e) override
    {
        up[e.from] = min(up[e.from], up[e.to]);
    }

    void edgeBack(Edge e) override
    {
        if (up[e.to] == tIn[e.to]) {
            bridges.push_back(e);
        }
    }

    void edgeMet(Edge e, bool) override
    {
        up[e.from] = min(up[e.from], tIn[e.to]);
    }

    const vector<Edge> &getBridges() const
    {
        return bridges;
    }

private:
    size_t tCounter = 0;
    vector<size_t> tIn;
    vector<size_t> up;

    vector<Edge> bridges;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    Graph g(n);

    unordered_map<Edge, size_t> edges;

    for (size_t i = 1; i <= m; ++i) {
        size_t u, v;
        cin >> u >> v;
        Edge e {u - 1, v - 1};
        g.addEdge(e);
        g.addEdge(!e);
        edges[{min(u, v), max(u, v)}] = i;
    }

    BridgeVisitor visitor(n);
    g.dfs(visitor);
    auto &bridges = visitor.getBridges();

    set<size_t> sortedBridges;
    for (auto b : bridges) {
        sortedBridges.insert(edges[{min(b.from, b.to), max(b.from, b.to)}]);
    }

    cout << bridges.size() << '\n';
    for (auto b : sortedBridges) {
        cout << b << ' ';
    }

    return 0;
}