#include <bits/stdc++.h>

using namespace std;

bool foo(const uint32_t &i, const uint32_t &j, const size_t &m)
{
    for (size_t k = 1; k < m; ++k) {
        const bool x1 = i & 1u << k;
        const bool x2 = i & 1u << k - 1;
        const bool y1 = j & 1u << k;
        const bool y2 = j & 1u << k - 1;

        if (x1 == y1 && x1 == x2 && y1 == y2) {
            return false;
        }
    }

    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    if (m > n) {
        swap(m, n);
    }

    const auto pm = 1u << m;
    vector<vector<bool>> p(pm, vector<bool>(pm));

    for (size_t i = 0; i < pm; ++i) {
        for (size_t j = 0; j < pm; ++j) {
            p[i][j] = foo(i, j, m);
        }
    }

    vector<vector<uint32_t>> d(n, vector<uint32_t>(pm));
    fill(d[0].begin(), d[0].end(), 1);

    for (size_t k = 1; k < n; ++k) {
        for (size_t i = 0; i < pm; ++i) {
            for (size_t j = 0; j < pm; ++j) {
                if (p[j][i]) {
                    d[k][i] += d[k - 1][j];
                }
            }
        }
    }

    cout << accumulate(d.back().begin(), d.back().end(), 0u);

    return 0;
}
