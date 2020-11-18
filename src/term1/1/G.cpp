#include <bits/stdc++.h>

using std::cin, std::cout;

int main()
{
    size_t n;
    uint16_t x, y;
    cin >> n >> x >> y;

    uint64_t l = 0, r = --n * std::max(x, y);

    while (1 < r - l) {
        const auto m = (l + r) / 2;
        if (m / x + m / y < n) {
            l = m;
        } else {
            r = m;
        }
    }

    cout << std::min(x, y) + r;

    return 0;
}
