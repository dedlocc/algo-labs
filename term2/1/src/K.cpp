#include <algorithm>
#include <iostream>

using namespace std;

using S = size_t;

const auto LENGTH = 500'000;

enum Op
{
    ZERO,
    ONE,
    NONE,
};

struct V
{
    Op value = NONE;
    S ones = 0;
    S segments = 0;
    bool leftmost = false;
    bool rightmost = false;
};

class SegmentTree
{
private:
    vector<V> tree;

    const static S n = 1 << 20;

    static S left(const S x)
    {
        return (x << 1) + 1;
    }

    static S right(const S x)
    {
        return (x << 1) + 2;
    }

    static void set(V &node, const Op &v, const S length)
    {
        node.value = v;
        node.ones = v * length;
        node.segments = v;
        node.leftmost = v;
        node.rightmost = v;
    }

    void set(const S l, const S r, const Op &v, const S x, const S lx, const S rx)
    {
        if (lx >= r || rx <= l) {
            return;
        }

        if (lx >= l && rx <= r) {
            set(tree[x], v, rx - lx);
            return;
        }

        if (tree[x].value != NONE) {
            set(tree[left(x)], tree[x].value, (rx - lx) / 2);
            set(tree[right(x)], tree[x].value, (rx - lx) / 2);
        }

        const auto m = (lx + rx) / 2;
        set(l, r, v, left(x), lx, m);
        set(l, r, v, right(x), m, rx);

        const auto &tl = tree[left(x)];
        const auto &tr = tree[right(x)];

        tree[x].value = NONE;
        tree[x].ones = tl.ones + tr.ones;
        tree[x].segments = tl.segments + tr.segments - (tl.rightmost && tr.leftmost);
        tree[x].leftmost = tl.leftmost;
        tree[x].rightmost = tr.rightmost;
    }

public:
    explicit SegmentTree() : tree(2 * n - 1) {}

    void set(const S l, const S r, const Op &v)
    {
        return set(l, r, v, 0, 0, n);
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

    S n;
    cin >> n;

    SegmentTree s;

    for (size_t j = 0; j < n; ++j) {
        unsigned char color;
        S x, l;
        cin >> color >> x >> l;

        s.set(LENGTH + x, LENGTH + x + l, 'B' == color ? ONE : ZERO);

        const auto v = s.aggregate();

        cout << v.segments << ' ' << v.ones << '\n';
    }

    return 0;
}
