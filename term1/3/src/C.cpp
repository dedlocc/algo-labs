#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<int32_t> v(n);
    for (auto &e : v) {
        cin >> e;
    }

    vector<size_t> d(n);
    vector<size_t> p(n, n);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (v[j] < v[i] && d[i] < d[j]) {
                d[i] = d[j];
                p[i] = j;
            }
        }
        ++d[i];
    }

    const auto m = max_element(d.begin(), d.end());
    cout << *m << '\n';

    stack<int32_t> s;
    for (auto r = m - d.begin(); r < n; r = p[r]) {
        s.push(v[r]);
    }

    while (!s.empty()) {
        cout << s.top() << ' ';
        s.pop();
    }

    return 0;
}
