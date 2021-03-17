#include <algorithm>
#include <iostream>

using namespace std;
using T = uint32_t;
using S = size_t;

using V = tuple<T, T>;

const auto MAX = numeric_limits<T>::max();

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

    void set(const S l, const S r, const T &v, const S x, const S lx, const S rx)
    {
        if (lx >= r || rx <= l) {
            return;
        }

        if (lx >= l && rx <= r) {
            get<0>(tree[x]) = v;
            get<1>(tree[x]) = v;
            return;
        }

        if (get<1>(tree[x]) != MAX) {
            get<0>(tree[left(x)]) = get<1>(tree[left(x)]) = get<1>(tree[x]);
            get<0>(tree[right(x)]) = get<1>(tree[right(x)]) = get<1>(tree[x]);
            get<1>(tree[x]) = MAX;
        }

        const auto m = (lx + rx) / 2;
        set(l, r, v, left(x), lx, m);
        set(l, r, v, right(x), m, rx);

        get<0>(tree[x]) = min(get<0>(tree[left(x)]), get<0>(tree[right(x)]));
    }

    [[nodiscard]] T aggregate(const S l, const S r, const S x, const S lx, const S rx) const
    {
        if (l >= rx || lx >= r) {
            return numeric_limits<T>::max();
        }

        if (get<1>(tree[x]) != MAX) {
            return get<1>(tree[x]);
        }

        if (l <= lx && rx <= r) {
            return get<0>(tree[x]);
        }

        const auto m = (lx + rx) / 2;

        const auto a1 = aggregate(l, r, left(x), lx, m);
        const auto a2 = aggregate(l, r, right(x), m, rx);
        return min(a1, a2);
    }

    V build(const S x, const S l, const S r)
    {
        if (l + 1 == r) {
            return tree[x];
        }

        const auto m = (l + r) / 2;

        return tree[x] = {min(get<0>(build(left(x), l, m)), get<0>(build(right(x), m, r))), MAX};
    }

public:
    explicit SegmentTree(const S n) : n(toPow2(n))
    {
        tree.resize(2 * this->n - 1, {T(), MAX});

        build(0, 0, this->n);
    }

    void set(const S l, const S r, const T &v)
    {
        set(l, r, v, 0, 0, n);
    }

    [[nodiscard]] T aggregate(const S l, const S r) const
    {
        return aggregate(l, r, 0, 0, n);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    S n, m;
    cin >> n >> m;

    SegmentTree s(n);

    for (size_t j = 0; j < m; ++j) {
        unsigned char type;
        S l, r;
        cin >> type >> l >> r;

        if ('1' == type) {
            T v;
            cin >> v;
            s.set(l, r, v);
        } else {
            cout << s.aggregate(l, r) << '\n';
        }
    }

    return 0;
}
