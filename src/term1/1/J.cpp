#include <bits/stdc++.h>

using std::cin, std::cout;

double f(const double &x, const double &a, const uint32_t &v1, const uint32_t &v2)
{
    double t = x * x + a * a + 1;
    return sqrt(t - 2 * a) / v1 + sqrt(t - 2 * x) / v2;
}

int main()
{
    uint32_t v1, v2;
    double a;
    cin >> v1 >> v2 >> a;

    const double e = 5e-8;
    double l = 0, r = 1;

    while (e < r - l) {
        const auto m1 = (2 * l + r) / 3, m2 = (l + 2 * r) / 3;
        const auto f1 = f(m1, a, v1, v2), f2 = f(m2, a, v1, v2);
        if (f1 >= f2) {
            l = m1;
        }
        if (f1 <= f2) {
            r = m2;
        }
    }

    cout << r;

    return 0;
}
