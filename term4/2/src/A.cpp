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
    size_t n, m;

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
        shortestPaths[0] = 0;
        std::fill(shortestPaths.begin() + 1, shortestPaths.end(), -1);

        queue<size_t> q;
        q.push(0);

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

        return shortestPaths.back() != -1;
    }

    int dfs(size_t from, int flow)
    {
        if (flow == 0 || from == n - 1) {
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

public:
    Solution() : n(input()), m(input()), edges(n), shortestPaths(n), p(n)
    {
        pipes.reserve(m * 2);

        for (size_t i = 0; i < m; ++i) {
            size_t a, b;
            int c;
            cin >> a >> b >> c;
            --a, --b;
            pipes.push_back({b, c, 0});
            pipes.push_back({a, c, 0});
            edges[a].push_back(2 * i);
            edges[b].push_back(2 * i + 1);
        }
    }

    void solve()
    {
        int flowSize = 0;

        while (bfs()) {
            std::fill(p.begin(), p.end(), 0);
            while (int flow = dfs(0, numeric_limits<int>::max())) {
                flowSize += flow;
            }
        }

        cout << flowSize << '\n';
        for (size_t i = 0; i < m; ++i) {
            cout << pipes[i * 2].flow << '\n';
        }
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution().solve();

    return 0;
}
