#include <bits/stdc++.h>

using std::cin, std::cout;

double foo(double x)
{
    return x * x + sqrt(x);
}

int main()
{
    double c;
    cin >> c;

    const double e = 5e-7;
    double l = 0, r = 1e10;

    while (e < r - l) {
        const auto m = (l + r) / 2;
        if (m <= l || m >= r) {
            break;
        }
        if (foo(m) < c) {
            l = m;
        } else {
            r = m;
        }
    }

    cout << std::setprecision(16) << r;

    return 0;
}
