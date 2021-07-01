#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    cin >> n;

    const size_t m = 64 - __builtin_clzll(n - 1);
    vector<vector<size_t>> d(n + 1, vector<size_t>(m));

    for (size_t i = 1; i <= n; ++i) {
        cin >> d[i][0];
    }

    for (size_t i = 1; i < m; ++i) {
        for (size_t j = 1; j <= n; ++j) {
            d[j][i] = d[d[j][i - 1]][i - 1];
        }
    }

    for (size_t i = 1; i <= n; ++i) {
        cout << i << ": ";
        for (size_t j = 0; j < m && d[i][j] != 0; ++j) {
            cout << d[i][j] << ' ';
        }
        cout << '\n';
    }

    return 0;
}
