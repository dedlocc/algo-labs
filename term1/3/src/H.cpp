#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<vector<size_t>> v(n, vector<size_t>(n));

    for (auto &i : v) {
        for (auto &j : i) {
            cin >> j;
        }
    }

    const size_t p = 1u << n;
    vector<vector<size_t>> d(n, vector<size_t>(p, UINT32_MAX));
    vector<vector<size_t>> b(n, vector<size_t>(p, UINT32_MAX));

    for (size_t i = 0; i < n; ++i) {
        d[i][0] = 0;
    }

    for (size_t k = 1; k < p; ++k) {
        for (size_t i = 0; i < n; ++i) {
            if (k & (1u << i)) {
                continue;
            }
            for (size_t j = 0; j < n; ++j) {
                if (i != j && k & 1u << j) {
                    const auto t = v[i][j] + d[j][k - (1u << j)];
                    if (d[i][k] > t) {
                        d[i][k] = t;
                        b[i][k] = j;
                    }
                }
            }
        }
    }

    size_t w = UINT32_MAX;
    size_t q = 0;

    for (size_t i = 0; i < n; ++i) {
        const auto t = d[i][p - (1u << i) - 1];
        if (w > t) {
            w = t;
            q = i;
        }
    }

    cout << w << '\n';

    for (size_t r = p - 1; 0 != r; q = b[q][r]) {
        r -= 1u << q;
        cout << 1 + q << ' ';
    }

    return 0;
}
