#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<uint64_t> h(1, 0);
    vector<uint64_t> k(1, 1);

    {
        char c;
        while (cin.get(c) && c != '\n') {
            h.push_back(h.back() * 257 + c);
            k.push_back(k.back() * 257);
        }
    }

    auto subHash = [&](size_t l, size_t r) {
        return h[r] - h[l - 1] * k[r - l + 1];
    };

    size_t m;
    cin >> m;

    for (size_t i = 0; i < m; ++i) {
        size_t a, b, c, d;
        cin >> a >> b >> c >> d;
        cout << (subHash(a, b) == subHash(c, d) ? "Yes" : "No") << '\n';
    }

    return 0;
}