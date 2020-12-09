#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    cin >> n;

    if (0 == n) {
        cout << "0 0 0";
        return 0;
    }

    vector<int32_t> v(n);
    for (auto &e : v) {
        cin >> e;
    }

    vector<vector<size_t>> d(n, vector<size_t>(1 + n, INT32_MAX));

    d[0][100 < v[0]] = v[0];

    for (size_t i = 1; i < n; ++i) {
        d[i][0] = min(d[i - 1][0] + v[i], d[i - 1][1]);
        for (size_t j = 1; j < n; ++j) {
            d[i][j] = min(d[i - 1][j + 1], d[i - 1][j - (100 < v[i])] + v[i]);
        }
    }

    size_t m = 0;

    for (size_t i = 1; i <= n; ++i) {
        if (d[n - 1][m] >= d[n - 1][i]) {
            m = i;
        }
    }

    cout << d[n - 1][m] << '\n' << m << ' ';

    stack<size_t> s;

    for (size_t i = n - 1; 0 < i; --i) {
        if (0 == v[i]) {
            continue;
        }
        if (m < n && d[i][m] == d[i - 1][m + 1]) {
            s.push(i);
            ++m;
        } else {
            for (size_t j = m - 1; j <= min(n, m + 1); ++j) {
                if (d[i][m] == d[i - 1][j] + v[i]) {
                    m = j;
                    break;
                }
            }
        }
    }

    cout << s.size();
    while (!s.empty()) {
        cout << '\n' << 1 + s.top();
        s.pop();
    }

    return 0;
}
