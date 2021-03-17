#include <algorithm>
#include <iostream>

using namespace std;
using T = uint32_t;
using S = size_t;

T R;

struct V
{
    T matrix[2][2];

    V() = default;

    V(const T &a11, const T &a12, const T &a21, const T &a22) : matrix {{a11, a12}, {a21, a22}} {}

    T *operator[](const size_t i)
    {
        return matrix[i];
    }

    const T *operator[](const size_t i) const
    {
        return matrix[i];
    }

    V operator*(const V &other) const
    {
        V result {};
        for (size_t i = 0; i < 2; ++i) {
            for (size_t j = 0; j < 2; ++j) {
                result[i][j] = T();
                for (size_t k = 0; k < 2; ++k) {
                    result[i][j] += matrix[i][k] * other[k][j] % R;
                }
                result[i][j] %= R;
            }
        }
        return result;
    }
};

const V ID(1, 0, 0, 1);

ostream &operator<<(ostream &out, const V &v)
{
    for (size_t i = 0; i < 2; ++i) {
        out << v[i][0] << ' ' << v[i][1] << '\n';
    }
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

    [[nodiscard]] V aggregate(const S l, const S r, const S x, const S lx, const S rx) const
    {
        if (l >= rx || lx >= r) {
            return ID;
        }

        if (l <= lx && rx <= r) {
            return tree[x];
        }

        const auto m = (lx + rx) / 2;

        const auto al = aggregate(l, r, left(x), lx, m);
        const auto ar = aggregate(l, r, right(x), m, rx);
        return al * ar;
    }

    V build(const S x, const S l, const S r)
    {
        if (l + 1 == r) {
            return tree[x];
        }

        const auto m = (l + r) / 2;

        const auto al = build(left(x), l, m);
        const auto ar = build(right(x), m, r);
        return tree[x] = al * ar;
    }

public:
    explicit SegmentTree(vector<V> &a) : n(toPow2(a.size()))
    {
        tree.resize(2 * n - 1);
        move(a.begin(), a.end(), tree.begin() + n - 1);
        a.erase(a.begin(), a.end());

        build(0, 0, n);
    }

    [[nodiscard]] V aggregate(const S l, const S r) const
    {
        return aggregate(l, r, 0, 0, n);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    S n, m;
    cin >> R >> n >> m;

    vector<V> a;
    a.reserve(n);

    for (size_t i = 0; i < n; ++i) {
        T a11, a12, a21, a22;
        cin >> a11 >> a12 >> a21 >> a22;
        a.emplace_back(a11 % R, a12 % R, a21 % R, a22 % R);
    }

    SegmentTree s(a);

    for (size_t j = 0; j < m; ++j) {
        S l, r;
        cin >> l >> r;
        cout << s.aggregate(l - 1, r);
        cout << '\n';
    }

    return 0;
}
