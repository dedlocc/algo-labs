#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct Fail : std::exception
{};

struct Graph
{
    explicit Graph(size_t n) : n(n)
    {}

    void addEdge(int from, int to)
    {
        edges[from].push_back(to);
        backEdges[to].push_back(from);
    }

    vector<size_t> dfs()
    {
        for (int i = 1; i <= n; ++i) {
            dfs1(i);
            dfs1(-i);
        }

        for (auto it = order.rbegin(); it != order.rend(); ++it) {
            if (components[*it] == 0) {
                ++compCounter;
                dfs2(*it);
            }
        }

        vector<size_t> result;

        for (int i = 1; i <= n; ++i) {
            if (components[i] > components[-i]) {
                result.push_back(i - 1);
            }
        }

        return result;
    }

private:
    void dfs1(int u)
    {
        if (!marked.contains(u)) {
            marked.insert(u);
            for (int v : edges[u]) {
                dfs1(v);
            }
            order.push_back(u);
        }
    }

    void dfs2(int u)
    {
        components[u] = compCounter;
        if (components[-u] == compCounter) {
            throw Fail();
        }
        for (int v : backEdges[u]) {
            if (auto cv = components[v]; cv == 0) {
                dfs2(v);
            }
        }
    }

    size_t n;
    unordered_map<int, vector<int>> edges;
    unordered_map<int, vector<int>> backEdges;
    unordered_set<int> marked;
    vector<int> order;

    size_t compCounter = 0;
    unordered_map<int, size_t> components;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<string> names(n);
    unordered_map<string, int> imap;

    for (size_t i = 0; i < n; ++i) {
        cin >> names[i];
        int j = static_cast<int>(i + 1);
        imap['+' + names[i]] = j;
        imap['-' + names[i]] = -j;
    }

    Graph g(n);

    for (size_t i = 0; i < m; ++i) {
        string name1, name2;
        cin >> name1 >> name2 >> name2;
        if (name1 != name2) {
            g.addEdge(imap[name1], imap[name2]);
            g.addEdge(-imap[name2], -imap[name1]);
        }
    }

    try {
        auto result = g.dfs();
        cout << result.size() << '\n';
        for (size_t i : result) {
            cout << names[i] << '\n';
        }
    } catch (Fail &) {
        cout << -1;
    }

    return 0;
}
