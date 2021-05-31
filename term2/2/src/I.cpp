#include <iostream>
#include <random>

using namespace std;

class RoadMap
{
private:
    class Node
    {
    private:
        using P = uint32_t;

        static P randomPriority()
        {
            static mt19937 rnd(random_device {}());
            static uniform_int_distribution<P> dist;
            return dist(rnd);
        }

    public:
        P priority = randomPriority();
        Node *left {}, *right {}, *parent {};
        size_t size = 1;
        bool reversed = false;
        bool isCycle = false;

        void propagate()
        {
            if (reversed) {
                reversed = false;
                if (nullptr != left) {
                    left->reversed = !left->reversed;
                }
                if (nullptr != right) {
                    right->reversed = !right->reversed;
                }
                swap(left, right);
            }
        }

        void update()
        {
            size = 1 + getSize(left) + getSize(right);
        }

        size_t getIndex(const Node *prev = nullptr)
        {
            size_t index = 0;

            if (nullptr != parent) {
                index += parent->getIndex(this);
            }

            propagate();

            if (nullptr == prev || prev != left) {
                index += 1 + getSize(left);
            }

            return index;
        }

        Node *findRoot()
        {
            Node *root = this;

            while (nullptr != root->parent) {
                root = root->parent;
            }

            return root;
        }
    };

    static size_t getSize(const Node *node)
    {
        return nullptr == node ? 0 : node->size;
    }

    static void split(Node *node, Node *&left, Node *&right, const size_t targetSize)
    {
        if (nullptr == node) {
            left = right = nullptr;
            return;
        }

        node->propagate();

        const auto leftSize = getSize(node->left);

        if (targetSize <= leftSize) {
            split(node->left, left, node->left, targetSize);
            if (nullptr != node->left) {
                node->left->parent = node;
            }
            if (nullptr != left) {
                left->parent = nullptr;
            }
            right = node;
        } else {
            split(node->right, node->right, right, targetSize - leftSize - 1);
            if (nullptr != node->right) {
                node->right->parent = node;
            }
            if (nullptr != right) {
                right->parent = nullptr;
            }
            left = node;
        }

        node->update();
    }

    static Node *merge(Node *a, Node *b)
    {
        if (nullptr == a) {
            b->propagate();
            return b;
        }

        if (nullptr == b) {
            a->propagate();
            return a;
        }

        a->propagate();
        b->propagate();

        if (a->priority > b->priority) {
            a->right = merge(a->right, b);
            a->right->parent = a;
            a->update();
            return a;
        }

        b->left = merge(a, b->left);
        b->left->parent = b;
        b->update();
        return b;
    }

    static void add(Node &x, Node &y)
    {
        auto xr = x.findRoot(), yr = y.findRoot();

        if (xr == yr) {
            xr->isCycle = true;
            return;
        }

        auto xIsRight = x.getIndex() == xr->size;
        auto yIsLeft = y.getIndex() == 1;

        if (xIsRight && !yIsLeft) {
            yr->reversed = !yr->reversed;
        } else if (!xIsRight && yIsLeft) {
            xr->reversed = !xr->reversed;
        } else if (!xIsRight) {
            swap(xr, yr);
        }

        merge(xr, yr);
    }

    static void remove(Node &x, Node &y)
    {
        const auto root = x.findRoot();
        const auto isCycle = root->isCycle;
        root->isCycle = false;
        const auto xi = x.getIndex(), yi = y.getIndex();

        if (isCycle && 1 == min(xi, yi) && root->size == max(xi, yi)) {
            return;
        }

        Node *left, *right;
        split(root, left, right, min(xi, yi));

        if (isCycle) {
            merge(right, left);
        }
    }

    static int32_t query(Node &x, Node &y)
    {
        if (&x == &y) {
            return 0;
        }

        auto xr = x.findRoot(), yr = y.findRoot();

        if (xr != yr) {
            return -1;
        }

        const auto xi = x.getIndex(), yi = y.getIndex();
        const auto d = max(xi, yi) - min(xi, yi);
        return static_cast<int32_t>(xr->isCycle ? min(d, xr->size - d) : d) - 1;
    }

    vector<Node> cities;

public:
    explicit RoadMap(size_t n) : cities(n)
    {
    }

    void add(const size_t x, const size_t y)
    {
        add(cities[x - 1], cities[y - 1]);
    }

    void remove(const size_t x, const size_t y)
    {
        remove(cities[x - 1], cities[y - 1]);
    }

    int32_t query(const size_t x, const size_t y)
    {
        return query(cities[x - 1], cities[y - 1]);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m, q;
    cin >> n >> m >> q;

    RoadMap roads(n);

    for (size_t i = 0; i < m; ++i) {
        size_t x, y;
        cin >> x >> y;
        roads.add(x, y);
    }

    for (size_t i = 0; i < q; ++i) {
        unsigned char c;
        size_t x, y;
        cin >> c >> x >> y;

        if ('+' == c) {
            roads.add(x, y);
        } else if ('-' == c) {
            roads.remove(x, y);
        } else {
            cout << roads.query(x, y) << '\n';
        }
    }

    return 0;
}