#include <bits/stdc++.h>

using namespace std;

bool foo(const uint32_t &i, const uint32_t &j, const size_t &m)
{
    if (i & j) {
        return false;
    }

    auto x = (1u << m) - 1 - (i | j);

    if (0 != x % 3) {
        return false;
    }

    x /= 3;

    return !(x & x << 1u);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<uint32_t> a(n);
    for (auto &i : a) {
        for (size_t j = 0; j < m; ++j) {
            char t;
            cin >> t;
            if ('X' == t) {
                i |= (1u << j);
            }
        }
    }

    const auto pm = 1u << m;
    vector<vector<uint64_t>> d(n, vector<uint64_t>(pm));
    d[0][0] = 1;

    for (size_t k = 1; k < n; ++k) {
        for (uint32_t i = 0; i < pm; ++i) {
            if (!(i & a[k])) {
                for (uint32_t j = 0; j < pm; ++j) {
                    if (!(j & a[k - 1]) && foo(j | a[k - 1], i, m)) {
                        d[k][i] += d[k - 1][j];
                    }
                }
            }
        }
    }

    uint64_t result = 0;
    for (uint32_t i = 0; i < pm; ++i) {
        if (!(i & a.back()) && foo(i | a.back(), 0, m)) {
            result += d.back()[i];
        }
    }

    cout << result;

    return 0;
}
