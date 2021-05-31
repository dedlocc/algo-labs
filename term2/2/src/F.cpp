#include <iostream>
#include <random>

using namespace std;

template<class V>
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
        V value;
        P priority;
        Node *left {}, *right {};
        size_t size = 1;

        explicit Node(const V &value) : value(value), priority(randomPriority()) {}

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

    static void add(Node *&root, size_t i, Node *node)
    {
        if (nullptr == root) {
            root = node;
            return;
        }

        Node *left {}, *right {};
        split(root, left, right, i);

        root = merge(merge(left, node), right);
    }

    static void remove(Node *&root, size_t i)
    {
        Node *left {}, *right {};
        split(root, left, right, i - 1);
        Node *element {};
        split(right, element, right, 1);
        delete element;
        root = merge(left, right);
    }

    static void output(const Node *root, ostream &out)
    {
        if (nullptr == root) {
            return;
        }

        output(root->left, out);
        out << root->value << ' ';
        output(root->right, out);
    }

public:
    explicit Treap(Node *root = nullptr) : root(root) {}

    void add(const size_t i, const V &value)
    {
        add(root, i, new Node(value));
    }

    void remove(const size_t i)
    {
        remove(root, i);
    }

    void output(ostream &out) const
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

    Treap<uint32_t> treap;

    for (size_t i = 0; i < n; ++i) {
        uint32_t x;
        cin >> x;
        treap.add(i, x);
    }

    for (size_t i = 0; i < m; ++i) {
        string cmd;
        size_t index;
        cin >> cmd >> index;

        if ("del" == cmd) {
            treap.remove(index);
        } else {
            uint32_t x;
            cin >> x;
            treap.add(index, x);
        }
    }

    treap.output(cout);

    return 0;
}