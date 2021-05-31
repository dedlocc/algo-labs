#include <iostream>
#include <optional>
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

        explicit Node(const K &key) : key(key), priority(randomPriority()) {}
    };

    Node *root;

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
            return a;
        }

        b->left = merge(a, b->left);
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
        } else {
            add(node->key < root->key ? root->left : root->right, node);
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

    static optional<const K> next(const Node *root, const K &key)
    {
        if (nullptr == root) {
            return nullopt;
        }

        return key < root->key ? next(root->left, key).value_or(root->key) : next(root->right, key);
    }

    static optional<const K> prev(const Node *root, const K &key)
    {
        if (nullptr == root) {
            return nullopt;
        }

        return key > root->key ? prev(root->right, key).value_or(root->key) : prev(root->left, key);
    }

public:
    explicit Treap(Node *root = nullptr) : root(root) {}

    void add(const K &key)
    {
        if (!exists(key)) {
            add(root, new Node(key));
        }
    }

    void remove(const K &key)
    {
        remove(root, key);
    }

    [[nodiscard]] bool exists(const K &key) const
    {
        return exists(root, key);
    }

    [[nodiscard]] optional<const K> next(const K &key) const
    {
        return next(root, key);
    }

    [[nodiscard]] optional<const K> prev(const K &key) const
    {
        return prev(root, key);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string op;
    int32_t x;

    Treap<decltype(x)> treap;

    while (cin >> op >> x) {
        if ("insert" == op) {
            treap.add(x);
        } else if ("delete" == op) {
            treap.remove(x);
        } else if ("exists" == op) {
            cout << boolalpha << treap.exists(x) << '\n';
        } else if ("next" == op) {
            const auto next = treap.next(x);
            if (next.has_value()) {
                cout << next.value();
            } else {
                cout << "none";
            }
            cout << '\n';
        } else if ("prev" == op) {
            const auto prev = treap.prev(x);
            if (prev.has_value()) {
                cout << prev.value();
            } else {
                cout << "none";
            }
            cout << '\n';
        }
    }

    return 0;
}