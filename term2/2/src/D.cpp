#include <iostream>
#include <random>

using namespace std;

template<class K>
class Treap
{
private:
    using Sum = uint64_t;

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
        K key;
        P priority;
        Node *left {}, *right {};
        Sum sum;

        explicit Node(const K &key) : key(key), priority(randomPriority()), sum(key) {}

        void update()
        {
            sum = key + getSum(left) + getSum(right);
        }
    };

    Node *root;

    static Sum getSum(const Node *node)
    {
        return nullptr == node ? 0 : node->sum;
    }

    static void split(Node *node, Node *&left, Node *&right, const K &key)
    {
        if (nullptr == node) {
            left = right = nullptr;
            return;
        }

        if (key < node->key) {
            split(node->left, left, node->left, key);
            right = node;
        } else {
            split(node->right, node->right, right, key);
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

        if (a->priority < b->priority) {
            b->left = merge(a, b->left);
            b->update();
            return b;
        }

        a->right = merge(a->right, b);
        a->update();
        return a;
    }

    static void add(Node *&root, Node *node)
    {
        if (nullptr == root) {
            root = node;
            return;
        }

        if (node->priority > root->priority) {
            split(root, node->left, node->right, node->key);
            root = node;
        } else {
            add(node->key < root->key ? root->left : root->right, node);
        }
        root->update();
    }

    static bool exists(const Node *root, const K &key)
    {
        if (nullptr == root) {
            return false;
        }

        if (key == root->key) {
            return true;
        }

        return key < root->key ? exists(root->left, key) : exists(root->right, key);
    }

    static Sum sum(Node *root, const K &l, const K &r)
    {
        if (nullptr == root) {
            return 0;
        }

        Node *left {}, *right {}, *mid {};
        split(root, left, right, r);
        split(left, left, mid, l - 1);

        const auto sum = getSum(mid);
        root = merge(merge(left, mid), right);
        return sum;
    }

public:
    explicit Treap(Node *root = nullptr) : root(root) {}

    void add(const K &key)
    {
        if (!exists(root, key)) {
            add(root, new Node(key));
        }
    }

    [[nodiscard]] Sum sum(const K &l, const K &r) const
    {
        return sum(root, l, r);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    cin >> n;

    Treap<int32_t> treap;
    uint64_t y = 0;

    for (size_t i = 0; i < n; ++i) {
        unsigned char op;
        cin >> op;
        if ('+' == op) {
            int32_t x;
            cin >> x;
            treap.add((x + y) % 1'000'000'000);
            y = 0;
        } else {
            int32_t l, r;
            cin >> l >> r;
            cout << (y = treap.sum(l, r)) << '\n';
        }
    }

    return 0;
}