#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, k;
    cin >> n >> k;

    deque<pair<int32_t, size_t>> q;
    vector<size_t> w(n, n);

    q.emplace_back(0, 0);

    size_t i = 1;
    for (; i < n; ++i) {
        if (i > k) {
            q.pop_front();
        }
        pair<int32_t, size_t> m = q.front();
        for (auto &e : q) {
            if (e.first > m.first) {
                m = e;
            }
        }
        int32_t c;
        if (i == n - 1) {
            c = 0;
        } else {
            cin >> c;
        }
        q.emplace_back(c + m.first, i);
        w[i] = m.second;
    }

    stack<size_t> s;
    --i;

    do {
        s.push(i);
        i = w[i];
    } while (i < n);

    cout << q.back().first << '\n' << s.size() - 1 << '\n';

    while (!s.empty()) {
        cout << 1 + s.top() << ' ';
        s.pop();
    }

    return 0;
}
