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
        P priority = randomPriority();
        Node *left {}, *right {};
        size_t size = 1;
        bool hasZero = 0 == value;

        explicit Node(const size_t value = 0) : value(value) {}

        void update()
        {
            size = 1 + getSize(left) + getSize(right);
            hasZero = 0 == value || Treap::hasZero(left) || Treap::hasZero(right);
        }
    };

    Node *root;

    static size_t getSize(const Node *node)
    {
        return nullptr == node ? 0 : node->size;
    }

    static bool hasZero(const Node *node)
    {
        return nullptr != node && node->hasZero;
    }

    static void split(Node *node, Node *&left, Node *&right, const size_t targetSize)
    {
        if (nullptr == node) {
            left = right = nullptr;
            return;
        }

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
            return b;
        }

        if (nullptr == b) {
            return a;
        }

        if (a->priority > b->priority) {
            a->right = merge(a->right, b);
            a->update();
            return a;
        }

        b->left = merge(a, b->left);
        b->update();
        return b;
    }

    static void removeFirstZero(Node *&root)
    {
        if (hasZero(root->left)) {
            removeFirstZero(root->left);
            root->update();
        } else if (0 == root->value) {
            auto *ptr = root;
            root = merge(root->left, root->right);
            delete ptr;
        } else if (hasZero(root->right)) {
            removeFirstZero(root->right);
            root->update();
        }
    }

    static void insert(Node *&root, const size_t l, const size_t k)
    {
        Node *before, *after;
        split(root, before, after, l - 1);

        removeFirstZero(after);

        root = merge(before, merge(new Node(k), after));
    }

    static void output(Node *root, ostream &out)
    {
        if (nullptr == root) {
            return;
        }

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
    explicit Treap(size_t n) : root(new Node())
    {
        for (size_t i = 1; i < n; ++i) {
            Node *left {}, *right {};
            split(root, left, right, i);

            root = merge(merge(left, new Node()), right);
        }
    }

    ~Treap()
    {
        clear(root);
    }

    void insert(const size_t l, const size_t k)
    {
        insert(root, l, k);
    }

    void output(ostream &out)
    {
        out << getSize(root) << '\n';
        output(root, out);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;
    m = 0;

    vector<size_t> l(n);

    for (auto &i : l) {
        cin >> i;
        if (i > m) {
            m = i;
        }
    }

    Treap treap(m);

    for (size_t i = 0; i < n; ++i) {
        treap.insert(l[i], 1 + i);
    }

    treap.output(cout);

    return 0;
}