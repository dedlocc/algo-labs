#include <bits/stdc++.h>

using namespace std;

void foo(const vector<vector<size_t>> &d, const vector<vector<size_t>> &b, const string &s, const size_t &i, const size_t &j)
{
    if (0 == d[i][j]) {
        cout << s.substr(i, j - i + 1);
        return;
    }

    if (j - i + 1 == d[i][j]) {
        return;
    }

    if (s.size() == b[i][j]) {
        cout << s[i] << (foo(d, b, s, i + 1, j - 1), s[j]);
        return;
    }

    foo(d, b, s, i, b[i][j]);
    foo(d, b, s, 1 + b[i][j], j);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    vector<vector<size_t>> d(s.size(), vector<size_t>(s.size()));

    for (size_t i = 0; i < s.size(); ++i) {
        d[i][i] = 1;
    }

    vector<vector<size_t>> b(s.size(), vector<size_t>(s.size()));

    for (size_t l = 1; l < s.size(); ++l) {
        for (size_t i = 0; i < s.size() - l; ++i) {
            const auto j = i + l;
            d[i][j] = '(' == s[i] && ')' == s[j] ||
                '[' == s[i] && ']' == s[j] ||
                '{' == s[i] && '}' == s[j] ?
                d[i][j] = d[i + 1][j - 1] : UINT32_MAX;
            b[i][j] = s.size();

            for (size_t k = i; k < j; ++k) {
                const auto t = d[i][k] + d[k + 1][j];
                if (d[i][j] > t) {
                    d[i][j] = t;
                    b[i][j] = k;
                }
            }
        }
    }

    foo(d, b, s, 0, s.size() - 1);

    return 0;
}
