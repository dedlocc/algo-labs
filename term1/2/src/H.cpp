#include <bits/stdc++.h>

using namespace std;

struct Element
{
    Element *parent = this;
    size_t rank = 0;
    int32_t weight = 0;

    Element() = default;

    [[nodiscard]] Element *get() const
    {
        Element *p = parent;
        while (p != p->parent) {
            p = p->get();
        }

        return p;
    }

    [[nodiscard]] uint32_t getWeight() const
    {
        if (this == parent) {
            return weight;
        }

        return weight + parent->getWeight();
    }

    void addWeight(const uint32_t &d) const
    {
        get()->weight += d;
    }

    static void unite(Element *x, Element *y)
    {
        x = x->get();
        y = y->get();

        if (x == y) {
            return;
        }

        if(x->rank > y->rank) {
            const auto t = x;
            x = y;
            y = t;
        }

        x->parent = y;
        x->weight -= y->weight;

        if (x->rank == y->rank) {
            ++y->rank;
        }
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<Element> a(n);

    for (size_t i = 0; i < m; ++i) {
        string action;
        size_t x;
        cin >> action >> x;

        if ("join" == action) {
            size_t y;
            cin >> y;
            Element::unite(&a[x - 1], &a[y - 1]);
        } else if ("add" == action) {
            uint32_t v;
            cin >> v;
            a[x - 1].addWeight(v);
        } else {
            cout << a[x - 1].getWeight() << '\n';
        }
    }

    return 0;
}
