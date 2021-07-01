#include <iostream>
#include <vector>

using namespace std;

class Tree
{
    const size_t m;
    vector<vector<size_t>> dp;
    vector<size_t> &p;
    vector<size_t> depth;

    explicit Tree(const size_t n, istream &in) :
        m(64 - __builtin_clzll(n - 1)),
        dp(m, vector<size_t>(n + 1)),
        p(dp.front()),
        depth(n + 1)
    {
        for (size_t i = 2; i <= n; ++i) {
            in >> p[i];
        }

        for (size_t i = 1; i <= n; ++i) {
            traverse(i);
        }

        for (size_t i = 1; i < m; ++i) {
            for (size_t j = 1; j <= n; ++j) {
                dp[i][j] = dp[i - 1][dp[i - 1][j]];
            }
        }
    }

    void traverse(const size_t pos)
    {
        if (!depth[pos] && p[pos]) {
            traverse(p[pos]);
            depth[pos] = depth[p[pos]] + 1;
        }
    }

public:
    static Tree input(istream &in)
    {
        size_t n;
        in >> n;
        return Tree(n, in);
    }

    [[nodiscard]] size_t lca(size_t u, size_t v) const
    {
        if (depth[u] > depth[v]) {
            swap(u, v);
        }

        for (size_t i = m - 1; i != -1; --i) {
            if (dp[i][v] != 0 && depth[dp[i][v]] >= depth[u]) {
                v = dp[i][v];
            }
        }

        if (u == v) {
            return u;
        }

        for (size_t i = m - 1; i != -1; --i) {
            if (dp[i][u] != dp[i][v]) {
                u = dp[i][u];
                v = dp[i][v];
            }
        }

        return p[u];
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const auto tree = Tree::input(cin);

    size_t m;
    cin >> m;

    for (size_t i = 0; i < m; ++i) {
        size_t u, v;
        cin >> u >> v;
        cout << tree.lca(u, v) << '\n';
    }

    return 0;
}
