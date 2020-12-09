#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string a, b;
    cin >> a >> b;

    const auto n = a.size(), m = b.size();
    vector<vector<size_t>> d(1 + n, vector<size_t>(1 + m));

    iota(d[0].begin(), d[0].end(), 0);

    for (size_t i = 1; i <= n; ++i) {
        d[i][0] = i;
        for (size_t j = 1; j <= m; ++j) {
            d[i][j] = min({1 + d[i - 1][j], 1 + d[i][j - 1], (a[i - 1] != b[j - 1]) + d[i - 1][j - 1]});
        }
    }

    cout << d[n][m];

    return 0;
}
