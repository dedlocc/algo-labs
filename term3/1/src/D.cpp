#include <iostream>
#include <vector>
#include <iterator>
#include <unordered_map>
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

template <class MultiEdgeMap>
struct CostalDoublyLinkedComponentsVisitor : DFSVisitor
{
    explicit CostalDoublyLinkedComponentsVisitor(size_t n, MultiEdgeMap &multiEdges) :
        tIn(n),
        up(n),
        components(n),
        multiEdges(multiEdges)
    {}

    void vertexDiscovered(size_t u) override
    {
        up[u] = tIn[u] = tCounter++;
        buff.push_back(u);
    }

    void vertexFinished(size_t u, size_t v) override
    {
        if (u == v || !multiEdges[{min(u, v), max(u, v)}] && up[v] == tIn[v]) {
            size_t x;
            ++compCounter;
            do {
                x = buff.back();
                buff.pop_back();
                components[x] = compCounter;
            } while (x != v);
        }
        up[u] = min(up[u], up[v]);
    }

    void edgeFinished(size_t u, size_t v) override
    {
        up[u] = min(up[u], tIn[v]);
    }

    const vector<size_t> &getComponents() const
    {
        return components;
    }

    size_t getNumberOfComponents() const
    {
        return compCounter;
    }

private:
    size_t tCounter = 0;
    vector<size_t> tIn;
    vector<size_t> up;
    vector<size_t> buff;
    MultiEdgeMap &multiEdges;

    size_t compCounter = 0;
    vector<size_t> components;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    Graph g(n);

    auto hash = [n](pair<size_t, size_t> p) {
        return p.first * n + p.second;
    };
    unordered_map<pair<size_t, size_t>, bool, decltype(hash)> multiEdges(0, hash);

    for (size_t i = 1; i <= m; ++i) {
        size_t u, v;
        cin >> u >> v;
        --u; --v;
        if (auto ins = multiEdges.try_emplace({min(u, v), max(u, v)}, false); !ins.second) {
            ins.first->second = true;
        } else {
            g.addEdge(u, v);
            g.addEdge(v, u);
        }
    }

    CostalDoublyLinkedComponentsVisitor visitor(n, multiEdges);
    g.dfs(visitor);

    cout << visitor.getNumberOfComponents() << '\n';
    for (auto c : visitor.getComponents()) {
        cout << c << ' ';
    }

    return 0;
}
