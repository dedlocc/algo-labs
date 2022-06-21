#include <iostream>
#include <numeric>

using namespace std;

using nat = int32_t;
using nat64 = int64_t;

struct EEA
{
    nat gcd;
    nat x, y;

    static EEA run(nat a, nat b)
    {
        if (a == 0) {
            return {b, 0, 1};
        }
        EEA eea = run(b % a, a);
        return {eea.gcd, eea.y - (b / a) * eea.x, eea.x};
    }
};

nat modInverse(nat n, nat mod)
{
    EEA eea = EEA::run(n, mod);
    return (eea.x % mod + mod) % mod;
}

nat pow(nat64 base, nat power, nat mod)
{
    nat64 result = 1;
    while (power != 0) {
        if (power % 2 == 1) {
            result *= base;
            result %= mod;
        }
        base *= base;
        base %= mod;
        power /= 2;
    }
    return static_cast<nat>(result);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    nat n, e, c;
    cin >> n >> e >> c;

    nat p = 2;
    while (n % p) {
        ++p;
    }
    nat q = n / p;

    nat phi = lcm(p - 1, q - 1);
    nat d = modInverse(e, phi);

    cout << pow(c, d, n);

    return 0;
}
