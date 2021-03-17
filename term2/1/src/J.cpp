#include <algorithm>
#include <iostream>

using namespace std;
using T = uint32_t;
using S = size_t;

// min & max
using V = std::tuple<T, T>;

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

    void set(const S i, const T v, const S x, const S lx, const S rx)
    {
        if (1 == rx - lx) {
            get<0>(tree[x]) = v;
            get<1>(tree[x]) = v;
            return;
        }

        const auto m = (lx + rx) / 2;

        if (i < m) {
            set(i, v, left(x), lx, m);
        } else {
            set(i, v, right(x), m, rx);
        }

        get<0>(tree[x]) = min(get<0>(tree[left(x)]), get<0>(tree[right(x)]));
        get<1>(tree[x]) = max(get<1>(tree[left(x)]), get<1>(tree[right(x)]));
    }

    [[nodiscard]] S aggregate(const S l, const S r, const T p, const S x, const S lx, const S rx)
    {
        if (l >= rx || lx >= r) {
            return 0;
        }

        if (l <= lx && rx <= r && get<0>(tree[x]) > p) {
            return 0;
        }

        if (1 == rx - lx) {
            get<0>(tree[x]) = MAX;
            get<1>(tree[x]) = 0;
            return 1;
        }

        const auto m = (lx + rx) / 2;

        const auto a1 = aggregate(l, r, p, left(x), lx, m);
        const auto a2 = aggregate(l, r, p, right(x), m, rx);

        get<0>(tree[x]) = min(get<0>(tree[left(x)]), get<0>(tree[right(x)]));
        get<1>(tree[x]) = max(get<1>(tree[left(x)]), get<1>(tree[right(x)]));

        return a1 + a2;
    }

    V &build(const S x, const S l, const S r)
    {
        if (l + 1 == r) {
            return tree[x];
        }

        const auto m = (l + r) / 2;

        const auto &[al_min, al_max] = build(left(x), l, m);
        const auto &[ar_min, ar_max] = build(right(x), m, r);

        return tree[x] = {min(al_min, ar_min), max(al_max, ar_max)};
    }

public:
    explicit SegmentTree(const S n) : n(toPow2(n))
    {
        tree.resize(2 * this->n - 1, {MAX, 0});

        build(0, 0, this->n);
    }

    void set(const S i, const T v)
    {
        set(i, v, 0, 0, n);
    }

    [[nodiscard]] S aggregate(const S l, const S r, T p)
    {
        return aggregate(l, r, p, 0, 0, n);
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
        cin >> type;

        if ('1' == type) {
            S i;
            T h;
            cin >> i >> h;
            s.set(i, h);
        } else {
            S l, r;
            T p;
            cin >> l >> r >> p;
            cout << s.aggregate(l, r, p) << '\n';
        }
    }

    return 0;
}
