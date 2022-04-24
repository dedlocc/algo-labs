#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;

size_t input()
{
    size_t x;
    cin >> x;
    return x;
}

class Solution
{
private:
    size_t n, m, s, t;

    struct Pipe {
        size_t to;
        int capacity;
        int flow;
    };

    vector<Pipe> pipes;
    vector<vector<size_t>> edges;
    vector<size_t> shortestPaths;
    vector<size_t> p;

private:
    bool bfs()
    {
        std::fill(shortestPaths.begin(), shortestPaths.end(), -1);
        shortestPaths[s] = 0;

        queue<size_t> q;
        q.push(s);

        while (!q.empty()) {
            auto from = q.front();
            q.pop();
            for (auto i : edges[from]) {
                auto & e = pipes[i];
                if (e.flow < e.capacity && shortestPaths[e.to] == -1) {
                    q.push(e.to);
                    shortestPaths[e.to] = shortestPaths[from] + 1;
                }
            }
        }

        return shortestPaths[t] != -1;
    }

    int dfs(size_t from, int flow)
    {
        if (flow == 0 || from == t) {
            return flow;
        }
        for (size_t & i = p[from]; i < edges[from].size(); ++i) {
            size_t j = edges[from][i];
            auto & e = pipes[j];
            if (shortestPaths[from] + 1 == shortestPaths[e.to]) {
                int d = dfs(e.to, min(flow, e.capacity - e.flow));
                if (d != 0) {
                    e.flow += d;
                    pipes[j ^ 1].flow -= d;
                    return d;
                }
            }
        }
        return 0;
    }

    bool dfs2(size_t from, vector<size_t> & path)
    {
        path.push_back(from);

        if (from == t) {
            return true;
        }

        for (auto i : edges[from]) {
            if (pipes[i].flow > 0) {
                pipes[i].flow = 0;
                if (dfs2(pipes[i].to, path)) {
                    return true;
                }
                path.pop_back();
            }
        }

        return false;
    }

public:
    Solution()
        : n(input()), m(input())
        , s(input() - 1), t(input() - 1)
        , edges(n)
        , shortestPaths(n)
        , p(n)
    {
        pipes.reserve(m * 2);

        for (size_t i = 0; i < m; ++i) {
            size_t a, b;
            cin >> a >> b;
            --a, --b;
            pipes.push_back({b, 1, 0});
            pipes.push_back({a, 0, 0});
            edges[a].push_back(2 * i);
            edges[b].push_back(2 * i + 1);
        }
    }

    void solve()
    {
        int flowSize = 0;

        while (bfs()) {
            std::fill(p.begin(), p.end(), 0);
            while (int flow = dfs(s, numeric_limits<int>::max())) {
                flowSize += flow;
            }

            if (flowSize >= 2) {
                cout << "YES\n";

                vector<size_t> path;
                for (size_t i = 0; i < 2; ++i) {
                    path.clear();
                    dfs2(s, path);
                    for (auto v : path) {
                        cout << v + 1 << ' ';
                    }
                    cout << '\n';
                }
                return;
            }
        }

        cout << "NO\n";
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution().solve();

    return 0;
}
