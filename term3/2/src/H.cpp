#include <iostream>
#include <vector>

using namespace std;

enum Status
{
    Unknown,
    Winning,
    Losing,
};

struct Data
{
    explicit Data(size_t n) : n(n), deg(n), backEdges(n), status(n, Unknown)
    {}

    void addEdge(size_t u, size_t v)
    {
        ++deg[u];
        backEdges[v].push_back(u);
    }

    void dfs(size_t u)
    {
        for (auto v : backEdges[u]) {
            if (status[v] != Unknown) {
                continue;
            }
            if (status[u] == Losing) {
                status[v] = Winning;
            } else if (--deg[v] == 0) {
                status[v] = Losing;
            } else {
                continue;
            }
            dfs(v);
        }
    }

    size_t n;
    vector<size_t> deg;
    vector<vector<size_t>> backEdges;
    vector<Status> status;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m, s;
    cin >> n >> m >> s;

    Data data(n);

    for (size_t i = 0; i < m; ++i) {
        size_t u, v;
        cin >> u >> v;
        data.addEdge(u - 1, v - 1);
    }

    for (size_t i = 0; i < n; ++i) {
        if (data.deg[i] == 0 && data.status[i] == Unknown) {
            data.status[i] = Losing;
            data.dfs(i);
        }
    }

    cout << (data.status[s - 1] == Winning ? "First" : "Second") << " player wins";

    return 0;
}