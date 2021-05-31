#include <iostream>
#include <optional>

using namespace std;

template<class K>
class BinarySearchTree
{
private:
    struct Node
    {
        K key;
        Node *left {}, *right {};

        explicit Node(const K &key) : key(key) {}
    };

    Node *root;

    static void add(Node *&root, const K &key)
    {
        if (nullptr == root) {
            root = new Node(key);
        }

        if (key < root->key) {
            add(root->left, key);
        } else if (key > root->key) {
            add(root->right, key);
        }
    }

    static void remove(Node *&root, const K &key)
    {
        if (nullptr == root) {
            return;
        }

        if (key < root->key) {
            remove(root->left, key);
        } else if (key > root->key) {
            remove(root->right, key);
        } else if (nullptr == root->right) {
            const auto temp = root->left;
            delete root;
            root = temp;
        } else {
            Node **min = &root->right;
            while (nullptr != (*min)->left) {
                min = &(*min)->left;
            }
            root->key = (*min)->key;
            const auto temp = (*min)->right;
            delete *min;
            *min = temp;
        }
    }

    static bool contains(const Node *root, const K &key)
    {
        if (nullptr == root) {
            return false;
        }

        if (key == root->key) {
            return true;
        }

        return key < root->key ? contains(root->left, key) : contains(root->right, key);
    }

    static optional<const K> next(const Node *root, const K &key)
    {
        if (nullptr == root) {
            return nullopt;
        }

        if (key == root->key) {
            return next(root->right, key);
        }

        return key < root->key ? next(root->left, key).value_or(root->key) : next(root->right, key);
    }

    static optional<const K> prev(const Node *root, const K &key)
    {
        if (nullptr == root) {
            return nullopt;
        }

        if (root->key == key) {
            return prev(root->left, key);
        }

        return key < root->key ? prev(root->left, key) : prev(root->right, key).value_or(root->key);
    }

public:
    explicit BinarySearchTree(Node *root = nullptr) : root(root) {}

    void add(const K &key)
    {
        add(root, key);
    }

    void remove(const K &key)
    {
        remove(root, key);
    }

    [[nodiscard]] bool exists(const K &key) const
    {
        return contains(root, key);
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

    BinarySearchTree<decltype(x)> tree;

    while (cin >> op >> x) {
        if ("insert" == op) {
            tree.add(x);
        } else if ("delete" == op) {
            tree.remove(x);
        } else if ("exists" == op) {
            cout << boolalpha << tree.exists(x) << '\n';
        } else if ("next" == op) {
            const auto next = tree.next(x);
            if (next.has_value()) {
                cout << next.value();
            } else {
                cout << "none";
            }
            cout << '\n';
        } else if ("prev" == op) {
            const auto prev = tree.prev(x);
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