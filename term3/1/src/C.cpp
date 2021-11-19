#include <iostream>
#include <vector>
#include <iterator>
#include <set>

using namespace std;

using Neighbors = vector<size_t>;
using Edges = vector<Neighbors>;

struct DFSVisitor
{
    virtual void vertexDiscovered(size_t u) {}
    virtual void edgeDiscovered(size_t u, size_t v) {}

    virtual void vertexFinished(size_t u, size_t v) {}
    virtual void edgeFinished(size_t u, size_t v) {}

    virtual void edgeForward(size_t u, size_t v) {}
    virtual void edgeBack(size_t u, size_t v) {}
    virtual void edgeCross(size_t u, size_t v) {}
};

class Graph
{
    enum class Color
    {
        UNMET,
        IN_PROCESS,
        FINISHED,
    };

public:
    explicit Graph(size_t n) : edges(n, Neighbors())
    {}

    void addEdge(size_t u, size_t v)
    {
        edges[u].push_back(v);
    }

    void dfs(DFSVisitor &visitor) const
    {
        vector<Color> colors(edges.size());
        for (size_t u = 0; u < edges.size(); ++u) {
            dfs(u, u, colors, visitor);
        }
    }

private:
    void dfs(size_t u, size_t from, vector<Color> &colors, DFSVisitor &visitor) const
    {
        if (colors[u] == Color::UNMET) {
            visitor.vertexDiscovered(u);
            colors[u] = Color::IN_PROCESS;
            for (size_t v : edges[u]) {
                if (v == from) {
                    continue;
                }
                visitor.edgeDiscovered(u, v);
                dfs(v, u, colors, visitor);
                visitor.edgeFinished(u, v);
            }
            visitor.vertexFinished(from, u);
            colors[u] = Color::FINISHED;
        } else if (colors[u] == Color::IN_PROCESS) {
            visitor.edgeBack(from, u);
        } else if (u != from) {
            visitor.edgeCross(from, u);
        }
    }

    Edges edges;
};

struct ArticulationPointsVisitor : DFSVisitor
{
    explicit ArticulationPointsVisitor(size_t n) : tIn(n), up(n)
    {}

    void vertexDiscovered(size_t u) override
    {
        up[u] = tIn[u] = tCounter++;
        children.emplace_back();
    }

    void vertexFinished(size_t u, size_t v) override
    {
        if (u == v && children.back() < 2) {
            points.erase(v);
        }
        children.pop_back();

        up[u] = min(up[u], up[v]);
        if (u != v && tIn[u] <= up[v]) {
            points.insert(u);
            ++children.back();
        }
    }

    void edgeFinished(size_t u, size_t v) override
    {
        up[u] = min(up[u], tIn[v]);
    }

    const set<size_t> &getPoints() const
    {
        return points;
    }

private:
    size_t tCounter = 0;
    vector<size_t> tIn;
    vector<size_t> up;
    vector<size_t> children;

    set<size_t> points;
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
        --u; --v;
        g.addEdge(u, v);
        g.addEdge(v, u);
    }

    ArticulationPointsVisitor visitor(n);
    g.dfs(visitor);
    auto &points = visitor.getPoints();

    cout << points.size() << '\n';
    for (auto ap : points) {
        cout << ap + 1 << ' ';
    }

    return 0;
}