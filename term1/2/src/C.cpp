#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    cin >> n;

    deque<uint32_t> d;

    size_t m[100000];

    size_t removals = 0;

    for (size_t i = 0; i < n; ++i) {
        unsigned char t;
        cin >> t;
        switch (t) { // NOLINT(hicpp-multiway-paths-covered)
            case '1':
                uint32_t id;
                cin >> id;
                m[id] = d.size() + removals;
                d.push_back(id);
                break;
            case '2':
                d.pop_front();
                ++removals;
                break;
            case '3':
                d.pop_back();
                break;
            case '4':
                uint32_t q;
                cin >> q;
                cout << m[q] - removals << '\n';
                break;
            case '5':
                cout << d.front() << '\n';
                break;
        }
    }
    return 0;
}
