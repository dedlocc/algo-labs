#include <algorithm>
#include <iostream>

using S = int64_t; // Trust me I'm an engineer
using T = int64_t;

struct V
{
    T sum;
    T wSum;
    T add;

    V() = default;
    V(const T &sum, const T &wSum, const T &add) : sum(sum), wSum(wSum), add(add) {}
};

using namespace std;

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

    void add(const S l, const S r, const T d, const S x, const S lx, const S rx)
    {
        if (lx >= r || rx <= l) {
            return;
        }

        if (lx >= l && rx <= r) {
            tree[x].sum += (rx - lx) * d;
            tree[x].wSum += (rx - lx) * (lx + rx + 1) / 2 * d;
            tree[x].add += d;
            return;
        }

        const auto m = (lx + rx) / 2;
        add(l, r, d, left(x), lx, m);
        add(l, r, d, right(x), m, rx);

        tree[x].sum = tree[left(x)].sum + tree[right(x)].sum + (rx - lx) * tree[x].add;
        tree[x].wSum =
            tree[left(x)].wSum + tree[right(x)].wSum + (rx - lx) * (lx + rx + 1) / 2 * tree[x].add;
    }

    [[nodiscard]] T wSum(const S l, const S r, const S x, const S lx, const S rx) const
    {
        if (l >= rx || lx >= r) {
            return T();
        }

        if (l <= lx && rx <= r) {
            return tree[x].wSum;
        }

        const auto m = (lx + rx) / 2;

        const auto lz = max(l, lx);
        const auto rz = min(r, rx);

        return wSum(l, r, left(x), lx, m) + wSum(l, r, right(x), m, rx)
             + (rz - lz) * (lz + rz + 1) / 2 * tree[x].add;
    }

    [[nodiscard]] T sum(const S l, const S r, const S x, const S lx, const S rx) const
    {
        if (l >= rx || lx >= r) {
            return T();
        }

        if (l <= lx && rx <= r) {
            return tree[x].sum;
        }

        const auto m = (lx + rx) / 2;

        const auto lz = max(l, lx);
        const auto rz = min(r, rx);

        return sum(l, r, left(x), lx, m) + sum(l, r, right(x), m, rx) + (rz - lz) * tree[x].add;
    }

    void build(const S x, const S l, const S r)
    {
        if (l + 1 == r) {
            return;
        }

        const auto m = (l + r) / 2;
        build(left(x), l, m);
        build(right(x), m, r);

        tree[x].sum = tree[left(x)].sum + tree[right(x)].sum;
        tree[x].wSum = tree[left(x)].wSum + tree[right(x)].wSum;
    }

public:
    explicit SegmentTree(vector<V> &a) : n(toPow2(a.size()))
    {
        tree.resize(2 * n - 1);
        move(a.begin(), a.end(), tree.begin() + n - 1);
        a.erase(a.begin(), a.end());

        build(0, 0, n);
    }

    void add(const S l, const S r, const T d)
    {
        add(l, r, d, 0, 0, n);
    }

    [[nodiscard]] T aggregate(const S l, const S r) const
    {
        return wSum(l, r, 0, 0, n) - l * sum(l, r, 0, 0, n);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    S n, m;
    cin >> n >> m;

    vector<V> a;
    a.reserve(n);

    for (size_t j = 1; j <= n; ++j) {
        T v;
        cin >> v;
        a.emplace_back(v, (T) j * v, T());
    }

    SegmentTree s(a);

    for (size_t j = 0; j < m; ++j) {
        unsigned char type;
        S l, r;
        cin >> type >> l >> r;

        if ('1' == type) {
            T v;
            cin >> v;
            s.add(l - 1, r, v);
        } else {
            cout << s.aggregate(l - 1, r) << '\n';
        }
    }

    return 0;
}
