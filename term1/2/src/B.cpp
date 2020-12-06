#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<uint8_t> v(n);

    for (auto &i : v) {
        cin >> i;
    }

    int l = 1;
    int r = 2;

    while (r < n) {
        while (v[l] == v[r]) {
            const auto dif = r - l;
            // Fix r, move l
            while (0 <= --l && v[l] == v[r]);
            // Fix l, move r
            while (n > ++r && v[l + 1] == v[r]);
            if (dif + 2 == r - l) {
                ++l;
                --r;
                break;
            }
        }

        if (++l < r++) {
            break;
        }
    }

    cout << r - l - 1;

    return 0;
}
