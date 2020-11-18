#include <bits/stdc++.h>

using std::cin, std::cout, std::vector;

int main()
{
    size_t n, k;
    cin >> n >> k;

    uint64_t sum = 0;
    vector<uint32_t> a(n);

    for (auto &e : a) {
        cin >> e;
        sum += e;
    }

    uint64_t l = 0, r = sum - k + 1;

    while (1 < r - l) {
        const auto m = (l + r) / 2;
        size_t counter = 1;
        uint64_t localSum = 0;
        for (const auto &e : a) {
            if (localSum + e > m) {
                localSum = e;
                ++counter;
                if (e > m) {
                    break;
                }
            } else {
                localSum += e;
            }
        }

        if (counter > k || localSum > m) {
            l = m;
        } else {
            r = m;
        }
    }

    cout << r;

    return 0;
}
