#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<vector<int>> d(n, vector<int>(n, -1));
    vector<vector<size_t>> nx(n, vector<size_t>(n));

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            cin >> d[i][j];
            if (d[i][j] == 100'000) {
                d[i][j] = 1e8;
            }
            nx[i][j] = j;
        }
    }

    for (size_t i = 0; i < n; ++i) {
        if (d[i][i] < 0) {
            cout << "YES\n1\n" << i + 1;
            return 0;
        }
        d[i][i] = 0;
    }

    size_t f = n;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            for (size_t k = 0; k < n; ++k) {
                int x = d[j][i] + d[i][k];
                if (x < d[j][k]) {
                    d[j][k] = x;
                    nx[j][k] = nx[j][i];
                    if (f == n && j == k && x < 0) {
                        f = j;
                    }
                }
            }
        }
    }

    if (f != n) {
        cout << "YES\n";

        vector<bool> visited(n);
        queue<size_t> q;

        size_t j = f;
        while (!visited[j]) {
            visited[j] = true;
            q.push(j);
            j = nx[j][f];
        };

        while (q.front() != j) {
            q.pop();
        }

        cout << q.size() << '\n';

        while (!q.empty()) {
            cout << q.front() + 1 << ' ';
            q.pop();
        }

        return 0;
    } else {
        cout << "NO\n";
    }


    return 0;
}