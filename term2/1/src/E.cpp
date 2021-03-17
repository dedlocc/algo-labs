#include <algorithm>
#include <iostream>

using namespace std;

using T = int32_t;
using S = size_t;
using V = T;

class SegmentTree
{
private:
    vector<V> tree;
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

    void set(const S i, const T &v, const S x, const S lx, const S rx)
    {
        if (1 == rx - lx) {
            tree[x] = v;
        } else {
            const auto m = (lx + rx) / 2;
            if (i < m) {
                set(i, v, left(x), lx, m);
            } else {
                set(i, v, right(x), m, rx);
            }
            tree[x] = max(tree[left(x)], tree[right(x)]);
        }
    }

    [[nodiscard]] V aggregate(const S l, const T k, const S x, const S lx, const S rx) const
    {
        if (tree[x] < k || rx <= l) {
            return -1;
        }

        if (1 == rx - lx) {
            return lx;
        }

        const auto m = (lx + rx) / 2;

        const auto r = aggregate(l, k, left(x), lx, m);
        if (-1 != r) {
            return r;
        }

        return aggregate(l, k, right(x), m, rx);
    }

    V build(const S x, const S l, const S r)
    {
        if (l + 1 == r) {
            return tree[x];
        }

        const auto m = (l + r) / 2;

        return tree[x] = max(build(left(x), l, m), build(right(x), m, r));
    }

public:
    explicit SegmentTree(vector<T> &a) : n(toPow2(a.size()))
    {
        tree.resize(2 * n - 1);
        move(a.begin(), a.end(), tree.begin() + n - 1);
        a.erase(a.begin(), a.end());

        build(0, 0, n);
    }

    void set(const S i, const T &v)
    {
        set(i, v, 0, 0, n);
    }

    [[nodiscard]] V aggregate(const S l, const T k) const
    {
        return aggregate(l, k, 0, 0, n);
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
        cin >> type;

        if ('1' == type) {
            size_t i;
            T v;
            cin >> i >> v;
            s.set(i, v);
        } else {
            size_t x, l;
            cin >> x >> l;
            cout << s.aggregate(l, x) << '\n';
        }
    }

    return 0;
}
