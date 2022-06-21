#include <iostream>

using namespace std;

using nat = int64_t;

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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    nat r1, r2, a1, a2;
    cin >> r1 >> r2 >> a1 >> a2;

    nat m = a1 * a2;

    cout << (r1 * a2 % m * modInverse(a2, a1) % m + r2 * a1 % m * modInverse(a1, a2) % m) % m;

    return 0;
}
