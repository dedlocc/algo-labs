#include <algorithm>
#include <iostream>

using namespace std;

using T = bool;
using S = size_t;
using V = S;

class SegmentTree
{
private:
    vector<S> tree;
    const S n;

    static S toPow2(S n)
    {
        n--;
        n |= n >> 1;
        n |= n >> 2;
        n |= n >> 4;
        n |= n >> 8;
        n |= n >> 16;
        return ++n;
    }

    static S left(const S x)
    {
        return (x << 1) + 1;
    }

    static S right(const S x)
    {
        return (x << 1) + 2;
    }

    void invert(const S i, const S x, const S lx, const S rx)
    {
        if (1 == rx - lx) {
            tree[x] = !tree[x];
        } else {
            const auto m = (lx + rx) / 2;
            if (i < m) {
                invert(i, left(x), lx, m);
            } else {
                invert(i, right(x), m, rx);
            }
            tree[x] = tree[left(x)] + tree[right(x)];
        }
    }

    [[nodiscard]] V aggregate(const S k, const S x, const S lx, const S rx) const
    {
        if (1 == rx - lx) {
            return 1 + x - n;
        }

        const auto m = (lx + rx) / 2;
        const auto tl = tree[left(x)];

        return k < tl ? aggregate(k, left(x), lx, m) : aggregate(k - tl, right(x), m, rx);
    }

    V build(const S x, const S l, const S r)
    {
        if (l + 1 == r) {
            return tree[x];
        }

        const auto m = (l + r) / 2;

        return tree[x] = build(left(x), l, m) + build(right(x), m, r);
    }

public:
    explicit SegmentTree(vector<T> &a) : n(toPow2(a.size()))
    {
        tree.resize(2 * n - 1);
        move(a.begin(), a.end(), tree.begin() + n - 1);
        a.erase(a.begin(), a.end());

        build(0, 0, n);
    }

    void invert(const S i)
    {
        invert(i, 0, 0, n);
    }

    [[nodiscard]] V findOne(const S k) const
    {
        return aggregate(k, 0, 0, n);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    S n, m;
    cin >> n >> m;

    vector<T> a;
    a.reserve(n);

    for (size_t j = 0; j < n; ++j) {
        T v;
        cin >> v;
        a.emplace_back(v);
    }

    SegmentTree s(a);

    for (size_t j = 0; j < m; ++j) {
        unsigned char type;
        S i;
        cin >> type >> i;

        if ('1' == type) {
            s.invert(i);
        } else {
            cout << s.findOne(i) << '\n';
        }
    }

    return 0;
}
