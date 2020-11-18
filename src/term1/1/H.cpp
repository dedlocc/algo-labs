#include <bits/stdc++.h>

using std::cin, std::cout;

int main()
{
    uint32_t w, h;
    size_t n;
    cin >> w >> h >> n;

    uint64_t l = 0, r = ceil(sqrt(n)) * std::max(w, h);

    while (1 < r - l) {
        const auto m = (l + r) / 2;
        if ((m / w) * (m / h) < n) {
            l = m;
        } else {
            r = m;
        }
    }

    cout << r;

    return 0;
}
