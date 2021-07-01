#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Tree
{
    const size_t m;
    vector<vector<size_t>> dp;
    vector<size_t> &p;
    vector<size_t> depth;
    vector<vector<size_t>> children;
    vector<size_t> et;

    explicit Tree(const size_t n, istream &in) :
        m(64 - __builtin_clzll(n - 1)),
        dp(m, vector<size_t>(n + 1)),
        p(dp.front()),
        depth(n + 1, 1),
        children(n + 1),
        et(n + 1)
    {
        size_t root = 1;

        for (size_t i = 1; i <= n; ++i) {
            int t;
            in >> t;

            if (t > 0) {
                p[i] = t;
                children[t].push_back(i);
            } else {
                p[i] = 0;
                root = i;
            }
        }

        size_t trIndex = 0;
        traverse(root, trIndex);

        for (size_t i = 1; i < m; ++i) {
            for (size_t j = 1; j <= n; ++j) {
                dp[i][j] = dp[i - 1][dp[i - 1][j]];
            }
        }
    }

    void traverse(const size_t pos, size_t &i)
    {
        et[pos] = i;

        for (const auto c : children[pos]) {
            depth[c] = depth[pos] + 1;
            traverse(c, ++i);
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

    [[nodiscard]] size_t power(vector<size_t> &group) const
    {
        std::sort(group.begin(), group.end(), [this](const size_t a, const size_t b) {
            return et[a] < et[b];
        });

        size_t result = depth[group[0]];

        for (auto it = group.begin() + 1; it != group.end(); ++it) {
            const size_t a = lca(*(it - 1), *it);
            result += depth[*it] - depth[a];
        }

        return result;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const auto tree = Tree::input(cin);

    size_t g;
    cin >> g;

    for (size_t i = 0; i < g; ++i) {
        size_t k;
        cin >> k;

        vector<size_t> group;

        for (size_t j = 0; j < k; ++j) {
            size_t m;
            cin >> m;
            group.push_back(m);
        }

        std::cout << tree.power(group) << '\n';
    }

    return 0;
}
