#include <iostream>
#include <random>

using namespace std;

template<class K>
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
        K key;
        P priority;
        Node *left {}, *right {};
        size_t size = 1;

        explicit Node(const K &key) : key(key), priority(randomPriority()) {}

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

        if (a->priority > b->priority) {
            a->right = merge(a->right, b);
            a->update();
            return a;
        }

        b->left = merge(a, b->left);
        b->update();
        return b;
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
            root->update();
        } else {
            add(node->key < root->key ? root->left : root->right, node);
            ++root->size;
        }
    }

    static void remove(Node *&root, const K &key)
    {
        if (nullptr == root) {
            return;
        }

        if (key == root->key) {
            const auto &r = merge(root->left, root->right);
            delete root;
            root = r;
        } else {
            remove(key < root->key ? root->left : root->right, key);
            root->update();
        }
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

    static const K &kth(const Node *root, const K &k)
    {
        if (k == 1 + getSize(root->right)) {
            return root->key;
        }

        if (nullptr == root->right || k > root->right->size) {
            return kth(root->left, k - 1 - getSize(root->right));
        }

        return kth(root->right, k);
    }

public:
    explicit Treap(Node *root = nullptr) : root(root) {}

    void add(const K &key)
    {
        if (!exists(root, key)) {
            add(root, new Node(key));
        }
    }

    void remove(const K &key)
    {
        remove(root, key);
    }

    [[nodiscard]] const K &kth(const K &k) const
    {
        return kth(root, k);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    cin >> n;

    Treap<int32_t> treap;

    for (size_t i = 0; i < n; ++i) {
        int32_t c, k;
        cin >> c >> k;
        if (1 == c) {
            treap.add(k);
        } else if (-1 == c) {
            treap.remove(k);
        } else {
            cout << treap.kth(k) << '\n';
        }
    }

    return 0;
}