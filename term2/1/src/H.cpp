#include <algorithm>
#include <iostream>

using namespace std;
using T = uint64_t;
using S = size_t;

using V = tuple<T, T, T>;

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
            get<0>(tree[x]) = v * (rx - lx);
            get<1>(tree[x]) = v;
            get<2>(tree[x]) = T();
            return;
        }

        propagateSet(x, lx, rx);
        propagateAdd(x, lx, rx);

        const auto m = (lx + rx) / 2;
        set(l, r, v, left(x), lx, m);
        set(l, r, v, right(x), m, rx);

        get<0>(tree[x]) = get<0>(tree[left(x)]) + get<0>(tree[right(x)]);
    }

    void add(const S l, const S r, const T &v, const S x, const S lx, const S rx)
    {
        if (lx >= r || rx <= l) {
            return;
        }

        if (lx >= l && rx <= r) {
            get<0>(tree[x]) += v * (rx - lx);
            if (get<1>(tree[x]) == MAX) {
                get<2>(tree[x]) += v;
            } else {
                get<1>(tree[x]) += v;
            }
            return;
        }

        propagateSet(x, lx, rx);
        propagateAdd(x, lx, rx);

        const auto m = (lx + rx) / 2;
        add(l, r, v, left(x), lx, m);
        add(l, r, v, right(x), m, rx);

        get<0>(tree[x]) = get<0>(tree[left(x)]) + get<0>(tree[right(x)]);
    }

    void propagateSet(const S x, const S l, const S r)
    {
        if (get<1>(tree[x]) != MAX) {
            get<0>(tree[left(x)]) = get<0>(tree[right(x)]) = get<1>(tree[x]) * ((r - l) / 2);
            get<1>(tree[left(x)]) = get<1>(tree[right(x)]) = get<1>(tree[x]);
            get<2>(tree[left(x)]) = get<2>(tree[right(x)]) = T();
            get<1>(tree[x]) = MAX;
        }
    }

    void propagateAdd(const S x, const S l, const S r)
    {
        if (get<2>(tree[x]) != T()) {
            get<0>(tree[left(x)]) += get<2>(tree[x]) * ((r - l) / 2);
            if (get<1>(tree[left(x)]) == MAX) {
                get<2>(tree[left(x)]) += get<2>(tree[x]);
            } else {
                get<1>(tree[left(x)]) += get<2>(tree[x]);
            }

            get<0>(tree[right(x)]) += get<2>(tree[x]) * ((r - l) / 2);
            if (get<1>(tree[right(x)]) == MAX) {
                get<2>(tree[right(x)]) += get<2>(tree[x]);
            } else {
                get<1>(tree[right(x)]) += get<2>(tree[x]);
            }

            get<2>(tree[x]) = T();
        }
    }

    [[nodiscard]] T aggregate(const S l, const S r, const S x, const S lx, const S rx)
    {
        if (l >= rx || lx >= r) {
            return T();
        }

        if (l <= lx && rx <= r) {
            return get<0>(tree[x]);
        }

        propagateSet(x, lx, rx);
        propagateAdd(x, lx, rx);

        const auto m = (lx + rx) / 2;

        return aggregate(l, r, left(x), lx, m) + aggregate(l, r, right(x), m, rx);
    }

public:
    explicit SegmentTree(vector<T> &a) : n(toPow2(a.size()))
    {
        tree.resize(2 * n - 1);
    }

    void set(const S l, const S r, const T &v)
    {
        set(l, r, v, 0, 0, n);
    }

    void add(const S l, const S r, const T &v)
    {
        add(l, r, v, 0, 0, n);
    }

    [[nodiscard]] T aggregate(const S l, const S r)
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

    vector<T> a(n);
    SegmentTree s(a);

    for (size_t j = 0; j < m; ++j) {
        unsigned char type;
        S l, r;
        cin >> type >> l >> r;

        if ('3' == type) {
            cout << s.aggregate(l, r) << '\n';
        } else {
            T v;
            cin >> v;
            if ('1' == type) {
                s.set(l, r, v);
            } else {
                s.add(l, r, v);
            }
        }
    }

    return 0;
}
