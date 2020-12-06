#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    cin >> n;

    deque<size_t> d1, d2;

    for (size_t i = 0; i < n; ++i) {
        unsigned char t;
        cin >> t;

        if ('-' == t) {
            cout << d1.front() << '\n';
            d1.pop_front();
        } else {
            size_t m;
            cin >> m;

            if ('+' == t) {
                d2.push_back(m);
            } else {
                d2.push_front(m);
            }
        }

        if (d1.size() < d2.size()) {
            d1.push_back(d2.front());
            d2.pop_front();
        }
    }

    return 0;
}
