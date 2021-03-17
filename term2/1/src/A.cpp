#include <algorithm>
#include <iostream>

using namespace std;

class SegmentTree
{
private:
    using S = size_t;
    using T = uint32_t;
    using L = uint64_t;

    vector<L> tree;

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
            tree[x] = tree[left(x)] + tree[right(x)];
        }
    }

    [[nodiscard]] L sum(const S l, const S r, const S x, const S lx, const S rx) const
    {
        if (l >= rx || lx >= r) {
            return T();
        }

        if (l <= lx && rx <= r) {
            return tree[x];
        }

        const auto m = (lx + rx) / 2;

        return sum(l, r, left(x), lx, m) + sum(l, r, right(x), m, rx);
    }

    L build(const S x, const S l, const S r)
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

    void set(const S i, const T &v)
    {
        set(i, v, 0, 0, n);
    }

    [[nodiscard]] L sum(const S l, const S r) const
    {
        return sum(l, r, 0, 0, n);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    using T = uint32_t;

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
            size_t l, r;
            cin >> l >> r;
            cout << s.sum(l, r) << '\n';
        }
    }

    return 0;
}
