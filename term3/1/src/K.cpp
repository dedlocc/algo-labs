#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

using namespace std;

struct Edge
{
    size_t from, to;
    int weight;
};

struct Graph
{
    explicit Graph(size_t n) : marked(n), minWeight(n, numeric_limits<int>::max()), order(n), components(0)
    {}

    void addEdge(size_t from, size_t to, int weight)
    {
        edges.push_back({from - 1, to - 1, weight});
    }

    bool checkRoot()
    {
        dfs1(0, edges);

        if (!all_of(marked.begin(), marked.end(), [](bool m) { return m; })) {
            return false;
        }
        fill(marked.begin(), marked.end(), false);
        return true;
    }

    void condense()
    {
        order.empty();
        for (auto it = order.rbegin(); it != order.rend(); ++it) {
            if (components[*it] == 0) {
                ++compCounter;
                dfs2(*it);
            }
        }
    }

    uint64_t findMST(size_t root)
    {
        uint64_t res = 0;
        for (const auto &e : edges) {
            minWeight[e.to] = min(minWeight[e.to], e.weight);
        }
        for (size_t i = 0; i < marked.size(); ++i) {
            if (i != root) {
                res += minWeight[i];
            }
        }
        for (const auto &e : edges) {
            if (e.weight == minWeight[e.to]) {
                nullEdges.push_back(e);
            }
        }
        dfs1(root, nullEdges);
        if (all_of(marked.begin(), marked.end(), [](bool m) { return m; })) {
            return res;
        }
        condense();

        {
            Graph newG(compCounter);
            for (const auto &e: edges) {
                if (components[e.from] != components[e.to]) {
                    newG.addEdge(components[e.from], components[e.to], e.weight - minWeight[e.to]);
                }
            }
            root = components[root];
            *this = move(newG);
        }

        return res += findMST(root);
    }

private:
    void dfs1(size_t u, const vector<Edge> &allowedEdges)
    {
        if (!marked[u]) {
            marked[u] = true;
            for (const auto &e : allowedEdges) {
                if(e.from == u) {
                    dfs1(e.to, allowedEdges);
                }
            }
            order.push_back(u);
        }
    }

    void dfs2(size_t u)
    {
        components[u] = compCounter;
        for (const auto &e : nullEdges) {
            if (e.to == u) {
                if (components[e.from] == 0) {
                    dfs2(e.from);
                }
            }
        }
    }

    vector<Edge> edges;
    vector<bool> marked;
    vector<int> minWeight;
    vector<Edge> nullEdges;

    vector<size_t> order;
    size_t compCounter = 0;
    unordered_map<size_t, size_t> components;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    Graph g(n);

    for (size_t i = 0; i < m; ++i) {
        size_t from, to;
        int weight;
        cin >>from >> to >> weight;
        g.addEdge(from, to, weight);
    }

    if (!g.checkRoot()) {
        cout << "NO";
        return 0;
    }
    cout << "YES\n";
    cout << g.findMST(0);

    return 0;
}