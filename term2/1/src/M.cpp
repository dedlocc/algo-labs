#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

using T = int32_t;
using S = size_t;

struct V
{
    S max, add, x;
};

class SegmentTree
{
private:
    const S n;

    vector<V> tree;

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

    void query(const S l, const S r, const bool open, const S x, const S lx, const S rx)
    {
        if (lx >= r || rx <= l) {
            return;
        }

        if (lx >= l && rx <= r) {
            if (open) {
                ++tree[x].max;
                ++tree[x].add;
            } else {
                --tree[x].max;
                --tree[x].add;
            }
            return;
        }

        const auto m = (lx + rx) / 2;
        query(l, r, open, left(x), lx, m);
        query(l, r, open, right(x), m, rx);

        const auto maxChild =
            tree[left(x)].max < tree[right(x)].max ? tree[right(x)] : tree[left(x)];
        tree[x].max = maxChild.max + tree[x].add;
        tree[x].x = maxChild.x;
    }

    void build(const S x, const S l, const S r)
    {
        tree[x].x = l;

        if (l + 1 < r) {
            const auto m = (l + r) / 2;
            build(left(x), l, m);
            build(right(x), m, r);
        }
    }

public:
    explicit SegmentTree(const S size) : n(toPow2(size)), tree(2 * n - 1)
    {
        build(0, 0, n);
    }

    void query(const S l, const S r, const bool open)
    {
        query(l, r, open, 0, 0, n);
    }

    [[nodiscard]] const V &aggregate() const
    {
        return tree[0];
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    S n;
    cin >> n;

    map<T, pair<vector<pair<T, T>>, vector<pair<T, T>>>> rects;
    set<T> xs;

    for (S i = 0; i < n; ++i) {
        T x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        rects.try_emplace(y1).first->second.first.emplace_back(x1, x2);
        rects.try_emplace(y2).first->second.second.emplace_back(x1, x2);
        xs.emplace(x1);
        xs.emplace(x2);
    }

    SegmentTree a(xs.size());
    vector<T> xv;
    xv.insert(xv.end(), xs.begin(), xs.end());

    S max = 0;
    T x = 0, y = 0;

    for (const auto &[k, v] : rects) {
        for (const auto &q : v.first) {
            a.query(
                lower_bound(xv.begin(), xv.end(), q.first) - xv.begin(),
                upper_bound(xv.begin(), xv.end(), q.second) - xv.begin(),
                true
            );
        }

        const auto &root = a.aggregate();
        if (root.max > max) {
            max = root.max;
            x = xv[root.x];
            y = k;
        }

        for (const auto &q : v.second) {
            a.query(
                lower_bound(xv.begin(), xv.end(), q.first) - xv.begin(),
                upper_bound(xv.begin(), xv.end(), q.second) - xv.begin(),
                false
            );
        }
    }

    cout << max << '\n' << x << ' ' << y;
}
