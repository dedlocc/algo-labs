#include <bits/stdc++.h>

using std::cin, std::cout;

int main()
{
    size_t n;
    cin >> n;

    uint32_t a[101] {};

    for (size_t i = 0; i < n; ++i) {
        uint16_t t;
        cin >> t;
        ++a[t];
    }

    for (uint16_t i = 0; i <= 100; ++i) {
        for (uint32_t j = 0; j < a[i]; ++j) {
            cout << i << ' ';
        }
    }

    return 0;
}
