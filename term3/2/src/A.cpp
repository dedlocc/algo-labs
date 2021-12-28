#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<vector<int>> v(n, vector<int>(n));

    for (auto &i : v) {
        for (auto &j : i) {
            cin >> j;
        }
    }

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            for (size_t k = 0; k < n; ++k) {
                v[j][k] = min(v[j][k], v[j][i] + v[i][k]);
            }
        }
    }

    for (auto const &i : v) {
        for (auto j : i) {
            cout << j << ' ';
        }
        cout << '\n';
    }

    return 0;
}