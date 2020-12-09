#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    uint32_t s;
    cin >> n >> s;

    vector<uint32_t> w(n);
    for (auto &e : w) {
        cin >> e;
    }

    const size_t np = 1u << n;
    vector<pair<size_t, size_t>> d(np, {UINT32_MAX, UINT32_MAX});
    vector<size_t> b(np);
    vector<size_t> v(np);
    d[0] = {0, 0};
    b[0] = np;

    for (size_t i = 0; i < np; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (0 == (i & 1u << j)) {
                pair<size_t, size_t> p = d[i];
                if (w[j] + p.second <= s) {
                    p.second += w[j];
                } else {
                    ++p.first;
                    p.second = w[j];
                }
                const auto k = i | 1u << j;
                if (d[k] > p) {
                    d[k] = p;
                    b[k] = i;
                    v[k] = j;
                }
            }
        }
    }

    cout << 1 + d.back().first << '\n';

    stack<size_t> z;

    for (size_t i = np - 1; 0 != i; i = b[i]) {
        z.push(1 + v[i]);

        if (0 == b[i] || d[i].first != d[b[i]].first) {
            cout << z.size();
            while (!z.empty()) {
                cout << ' ' << z.top();
                z.pop();
            }
            cout << '\n';
        }
    }

    return 0;
}
