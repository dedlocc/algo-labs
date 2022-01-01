#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;

struct Node;

struct Node
{
    char ch;
    vector<size_t> d;
    size_t parent;
    size_t suf;
    bool visited = false;

    Node(char ch, size_t parent) : ch(ch), d('z' - 'a' + 1), parent(parent)
    {}
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<Node> nodes;
    vector<size_t> leaves;

    nodes.emplace_back('$', 0).suf = 0;
    nodes.emplace_back('$', 0).suf = 0;

    for (size_t i = 0; i < n; ++i) {
        string s;
        cin >> s;
        size_t node = 1;
        for (auto c : s) {
            c -= 'a';
            auto &p = nodes[node].d[c];
            if (!p) {
                p = nodes.size();
                nodes.emplace_back(c, node);
            }
            node = nodes[node].d[c];
        }
        leaves.push_back(node);
    }

    for (auto &c : nodes.front().d) {
        c = 1;
    }

    queue<size_t> q;
    q.push(1);

    while (!q.empty()) {
        auto cur = q.front();
        for (auto &child : nodes[cur].d) {
            if (child) {
                q.push(child);
            }
        }
        if (nodes[cur].ch != '$') {
            nodes[cur].suf = nodes[nodes[nodes[cur].parent].suf].d[nodes[cur].ch];
        }

        for (size_t c = 0; c < nodes[cur].d.size(); ++c) {
            if (!nodes[cur].d[c]) {
                nodes[cur].d[c] = nodes[nodes[cur].suf].d[c];
            }
        }
        q.pop();
    }

    string t;
    cin >> t;

    {
        size_t node = 1;
        for (auto c : t) {
            node = nodes[node].d[c - 'a'];
            for (size_t p = node; !nodes[p].visited && nodes[p].ch != '$'; p = nodes[p].suf) {
                nodes[p].visited = true;
            }
        }
    }


    for (auto &l : leaves) {
        cout << (nodes[l].visited ? "YES" : "NO") << '\n';
    }

    return 0;
}