#include <bits/stdc++.h>

using namespace std;

struct Element
{
    Element *parent = this;
    size_t rank = 0;
    uint32_t min = 0;
    uint32_t max = 0;
    size_t size = 1;

    explicit Element(const uint32_t &n) : min(n), max(n)
    {
    }

    Element(const Element &&e) noexcept : parent(this) {
        rank = e.rank;
        min = e.min;
        max = e.max;
        size = e.size;
    }

    [[nodiscard]] Element *get()
    {
        while (parent != parent->parent) {
            parent = parent->get();
        }

        return parent;
    }

    uint32_t getMin()
    {
        return get()->min;
    }

    uint32_t getMax()
    {
        return get()->max;
    }

    size_t getSize()
    {
        return get()->size;
    }

    static void unite(Element *x, Element *y)
    {
        x = x->get();
        y = y->get();

        if (x == y) {
            return;
        }

        if (x->rank > y->rank) {
            const auto t = x;
            x = y;
            y = t;
        }

        x->parent = y;
        y->min = std::min(x->min, y->min);
        y->max = std::max(x->max, y->max);
        y->size += x->size;

        if (x->rank == y->rank) {
            ++y->rank;
        }
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<Element> v;

    for (size_t i = 1; i <= n; ++i) {
        v.emplace_back(i);
    }

    string s;

    while (cin >> s) {
        size_t x;
        cin >> x;
        auto *e = &v[x - 1];
        if ("union" == s) {
            size_t y;
            cin >> y;
            Element::unite(e, &v[y - 1]);
        } else {
            cout << e->getMin() << ' ' << e->getMax() << ' ' << e->getSize() << '\n';
        }
    }

    return 0;
}
