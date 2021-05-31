#include <iostream>
#include <random>

using namespace std;

class Treap
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
        size_t value;
        P priority;
        Node *left {}, *right {};
        size_t size = 1;
        bool reversed = false;

        explicit Node(const size_t value) : value(value), priority(randomPriority()) {}

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
    };

    Node *root;

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
            right = node;
        } else {
            split(node->right, node->right, right, targetSize - leftSize - 1);
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
            a->update();
            return a;
        }

        b->left = merge(a, b->left);
        b->update();
        return b;
    }

    static void reverse(Node *&root, const size_t l, const size_t r)
    {
        Node *left, *mid, *right;
        split(root, left, right, l - 1);
        split(right, mid, right, r - l + 1);
        mid->reversed = !mid->reversed;
        root = merge(left, merge(mid, right));
    }

    static void output(Node *root, ostream &out)
    {
        if (nullptr == root) {
            return;
        }

        root->propagate();
        output(root->left, out);
        out << root->value << ' ';
        output(root->right, out);
    }

    static void clear(Node *root)
    {
        if (nullptr != root) {
            clear(root->left);
            clear(root->right);
            delete root;
        }
    }

public:
    explicit Treap(size_t n) : root(new Node(1))
    {
        for (size_t i = 2; i <= n; ++i) {
            Node *left {}, *right {};
            split(root, left, right, i);

            root = merge(merge(left, new Node(i)), right);
        }
    }

    ~Treap()
    {
        clear(root);
    }

    void reverse(const size_t l, const size_t r)
    {
        reverse(root, l, r);
    }

    void output(ostream &out)
    {
        output(root, out);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    Treap treap(n);

    for (size_t i = 0; i < m; ++i) {
        size_t l, r;
        cin >> l >> r;
        treap.reverse(l, r);
    }

    treap.output(cout);

    return 0;
}