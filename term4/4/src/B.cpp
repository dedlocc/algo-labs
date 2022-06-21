#include <iostream>
#include <random>

using namespace std;

using nat = int64_t;
using nat128 = __int128;

nat random(nat lo, nat hi)
{
    static mt19937 rng(random_device{}());
    uniform_int_distribution<nat> dist(lo, hi);
    return dist(rng);
}

nat128 pow(nat128 base, nat power, nat128 mod)
{
    nat128 result = 1;
    while (power != 0) {
        if (power % 2 == 1) {
            result *= base;
            result %= mod;
        }
        base *= base;
        base %= mod;
        power /= 2;
    }
    return result;
}

bool fermat(nat n, nat a)
{
    return gcd(a, n) == 1 && pow(a, n - 1, n) == 1;
}

bool millerRabin(nat n, nat a)
{
    nat mod = n--;

    size_t x = 0;
    while (n % 2 == 0) {
        n /= 2;
        ++x;
    }

    nat128 y = pow(a, n, mod);

    if (y == 1 || y == mod - 1) {
        return true;
    }

    while (x-- > 1) {
        y *= y;
        y %= mod;
        if (y == mod - 1) {
            return true;
        }
    }

    return false;
}

bool isPrime(nat n)
{
    if (n <= 1) {
        return false;
    }
    if (n <= 3) {
        return true;
    }

    for (size_t i = 0; i < 20; ++i) {
        nat a = random(1, n - 1);
        if (!fermat(n, a) || !millerRabin(n, a)) {
            return false;
        }
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    cin >> n;

    for (size_t i = 0; i < n; ++i) {
        nat x;
        cin >> x;
        cout << (isPrime(x) ? "YES" : "NO") << '\n';
    }

    return 0;
}
