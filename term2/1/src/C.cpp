#include <algorithm>
#include <iostream>

using namespace std;

using T = int32_t;
using L = int64_t;
using S = size_t;

// Sum on segment, Max sum on segment, Max sum on prefix, Max get on suffix
using V = tuple<L, L, L, L>;

V operator+(const V &v1, const V &v2)
{
    const auto [s1, s1m, s1l, s1r] = v1;
    const auto [s2, s2m, s2l, s2r] = v2;
    return V(s1 + s2, max({s1m, s2m, s1r + s2l}), max(s1l, s2l + s1), max(s2r, s1r + s2));
}

ostream &operator<<(ostream &out, const V &v)
{
    out << max(static_cast<L>(0), get<1>(v));
    return out;
}

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
            get<0>(tree[x]) = v;
            get<1>(tree[x]) = v;
            get<2>(tree[x]) = v;
            get<3>(tree[x]) = v;
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
        transform(a.begin(), a.end(), tree.begin() + n - 1, [](auto &&e) -> V {
            return {e, e, e, e};
        });
        a.erase(a.begin(), a.end());

        build(0, 0, n);
    }

    void set(const S i, const T &v)
    {
        set(i, v, 0, 0, n);
    }

    [[nodiscard]] V aggregate() const
    {
        return tree[0];
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
    cout << s.aggregate() << '\n';

    for (size_t j = 0; j < m; ++j) {
        S i;
        T v;
        cin >> i >> v;
        s.set(i, v);
        cout << s.aggregate() << '\n';
    }

    return 0;
}
