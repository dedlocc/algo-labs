#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s, t;
    cin >> t >> s;
    string u = t + '$' + s;

    vector<size_t> z(u.size());
    size_t l = 0;

    for (size_t i = 1; i < u.size(); ++i) {
        size_t r = l + z[l];
        if (i > 1) {
            z[i] = r > i ? min(r - i, z[i - l]) : 0;
        }
        while (u[z[i]] == u[i + z[i]]) {
            ++z[i];
        }

        if (i + z[i] > r) {
            l = i;
        }
    }

    vector<size_t> pos;

    for (size_t i = t.size() + 1; i <= u.size(); ++i) {
        if (z[i] == t.size()) {
            pos.push_back(i - t.size());
        }
    }

    cout << pos.size() << '\n';
    for (auto p : pos) {
        cout << p << ' ';
    }

    return 0;
}