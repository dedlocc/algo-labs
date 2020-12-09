#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    constexpr uint32_t MOD = 1'000'000'000;
    const vector<vector<uint32_t>> m {
        {4, 6},     // 0
        {6, 8},     // 1
        {7, 9},     // 2
        {4, 8},     // 3
        {0, 3, 9},  // 4
        {},         // 5
        {0, 1, 7},  // 6
        {2, 6},     // 7
        {1, 3},     // 8
        {2, 4},     // 9
    };

    size_t n;
    cin >> n;

    array<uint32_t, 10> d {};
    fill(d.begin(), d.end(), 1);
    d[0] = d[8] = 0;

    for (size_t i = 1; i < n; ++i) {
        array<uint32_t, 10> t {};

        for (size_t j = 0; j < m.size(); ++j) {
            for (const auto &k : m[j]) {
                t[k] += d[j];
                t[k] %= MOD;
            }
        }

        d = t;
    }

    uint32_t sum = 0;
    for (const auto &e : d) {
        sum += e;
        sum %= MOD;
    }

    cout << sum;

    return 0;
}
