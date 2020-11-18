#include <bits/stdc++.h>

using std::cin, std::cout, std::vector;

template<typename T>
T search(vector<T> &a, const T &val)
{
    auto l = a.begin() - 1;
    auto r = a.end();

    while (r - l > 1) {
        const auto m = l + (r - l) / 2;
        if (*m <= val) {
            l = m;
        } else {
            r = m;
        }
    }

    if (l < a.begin() || r != a.end() && val - *l > *r - val) {
        return *r;
    }

    return *l;
}

int main()
{
    size_t n, k;
    cin >> n >> k;

    vector<int32_t> a(n);

    for (auto &e : a) {
        cin >> e;
    }

    while (0 < k--) {
        int32_t b;
        cin >> b;
        cout << search(a, b) << '\n';
    }

    return 0;
}
