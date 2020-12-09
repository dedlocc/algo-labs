#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<int32_t>> d(n, vector<int32_t>(m));

    vector<vector<bool>> b(n, vector<bool>(m));

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            cin >> d[i][j];
            if (0 != i || 0 != j) {
                int32_t t = 0 == i ? INT32_MIN : d[i - 1][j];
                if (0 != j && t < d[i][j - 1]) {
                    t = d[i][j - 1];
                    b[i][j] = true;
                }
                d[i][j] += t;
            }
        }
    }

    size_t i = n - 1, j = m - 1;
    cout << d[i][j] << '\n';

    stack<char> s;

    while (0 != i || 0 != j) {
        if (b[i][j]) {
            s.push('R');
            --j;
        } else {
            s.push('D');
            --i;
        }
    }

    while (!s.empty()) {
        cout << s.top();
        s.pop();
    }

    return 0;
}
