#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

struct Edge
{
    size_t from {};
    size_t to {};
};

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

struct NotDAG : std::exception {};

struct TopSortVisitor : DFSVisitor
{
    explicit TopSortVisitor(size_t n)
    {
        order.reserve(n);
    }

    void vertexFinished(size_t u) override
    {
        order.push_back(u + 1);
    }

    void edgeMet(Edge e, bool cycle) override
    {
        if (cycle) {
            throw NotDAG();
        }
    }

    const vector<size_t> &getOrder() const
    {
        return order;
    }

private:
    vector<size_t> order;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    Graph g(n);

    while (m-- > 0) {
        size_t u, v;
        cin >> u >> v;
        g.addEdge({u - 1, v - 1});
    }

    TopSortVisitor visitor(n);

    try {
        g.dfs(visitor);
        auto &order = visitor.getOrder();
        copy(order.rbegin(), order.rend(), ostream_iterator<size_t>(cout, " "));
    } catch (NotDAG &) {
        cout << -1;
    }

    return 0;
}