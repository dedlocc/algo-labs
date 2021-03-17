#include <algorithm>
#include <iostream>

using namespace std;

using T = uint32_t;
using S = size_t;

struct Point
{
    S x, y, z;
};

istream &operator>>(istream &in, Point &p)
{
    return in >> p.x >> p.y >> p.z;
}

class FenwickTree
{
    S n;
    vector<vector<vector<T>>> tree;

    T get(const Point &p)
    {
        T result = 0;
        for (auto x = p.x; x < n; x &= x + 1, --x) {
            for (auto y = p.y; y < n; y &= y + 1, --y) {
                for (auto z = p.z; z < n; z &= z + 1, --z) {
                    result += tree[x][y][z];
                }
            }
        }
        return result;
    }

public:
    explicit FenwickTree(const S n) : n(n), tree(n, vector<vector<T>>(n, vector<T>(n))) {}

    T sum(const Point &p1, const Point &p2)
    {
        return get(p2) - get({p1.x - 1, p2.y, p2.z}) - get({p2.x, p1.y - 1, p2.z})
             - get({p2.x, p2.y, p1.z - 1}) + get({p2.x, p1.y - 1, p1.z - 1})
             + get({p1.x - 1, p2.y, p1.z - 1}) + get({p1.x - 1, p1.y - 1, p2.z})
             - get({p1.x - 1, p1.y - 1, p1.z - 1});
    }

    void add(const Point &p, const int32_t k)
    {
        for (auto x = p.x; x < n; x |= x + 1) {
            for (auto y = p.y; y < n; y |= y + 1) {
                for (auto z = p.z; z < n; z |= z + 1) {
                    tree[x][y][z] += k;
                }
            }
        }
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    S n;
    cin >> n;

    FenwickTree tree(n);

    unsigned char m;
    while (cin >> m, '3' != m) {
        Point p1;
        cin >> p1;
        if ('1' == m) {
            int32_t k;
            cin >> k;
            tree.add(p1, k);
        } else {
            Point p2;
            cin >> p2;
            cout << tree.sum(p1, p2) << '\n';
        }
    }

    return 0;
}
