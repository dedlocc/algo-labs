#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    vector<size_t> z(s.size());
    size_t l = 0;

    for (size_t i = 1; i < s.size(); ++i) {
        size_t r = l + z[l];
        if (i > 1) {
            z[i] = r > i ? min(r - i, z[i - l]) : 0;
        }
        while (s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        cout << z[i] << ' ';

        if (i + z[i] > r) {
            l = i;
        }
    }

    return 0;
}