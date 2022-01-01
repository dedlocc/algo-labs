#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<size_t> pref(1, -1);

    string s;
    cin >> s;

    pref.reserve(s.size());

    for (size_t i = 1; i <= s.size(); ++i) {
        size_t k = pref[i - 1];
        while (k != -1 && s[k] != s[i - 1]) {
            k = pref[k];
        }
        cout << pref.emplace_back(k + 1) << ' ';
    }

    return 0;
}