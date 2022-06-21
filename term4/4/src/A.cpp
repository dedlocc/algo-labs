#include <cmath>
#include <iostream>

using namespace std;

using nat = int32_t;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    nat n;
    cin >> n;

    nat max = static_cast<nat>(sqrt(n));
    for (nat p = 2; p <= max && n > 1; ++p) {
        while (n % p == 0) {
            n /= p;
            std::cout << p << ' ';
        }
    }

    if (n > 1) {
        std::cout << n;
    }

    return 0;
}
