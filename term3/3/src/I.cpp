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
    vector<size_t> backSuf;
    bool accepted = false;
    size_t leftmost = -1;
    size_t rightmost = 0;

    Node(char ch, size_t parent) : ch(ch), d('z' - 'a' + 1), parent(parent)
    {}
};

void dfs(vector<Node> &nodes, size_t u)
{
    for (auto bs : nodes[u].backSuf) {
        dfs(nodes, bs);
        nodes[u].leftmost = min(nodes[u].leftmost, nodes[bs].leftmost);
        nodes[u].rightmost = max(nodes[u].rightmost, nodes[bs].rightmost);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<Node> nodes;
    vector<pair<size_t, size_t>> leaves;

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
        nodes[node].accepted = true;
        leaves.emplace_back(node, s.size());
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
            nodes[nodes[cur].suf].backSuf.push_back(cur);
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
        size_t pos = 0;
        for (auto c : t) {
            node = nodes[node].d[c - 'a'];
            nodes[node].leftmost = min(nodes[node].leftmost, pos);
            nodes[node].rightmost = max(nodes[node].rightmost, pos);
            ++pos;
        }
    }

    dfs(nodes, 1);

    for (auto [l, size] : leaves) {
        if (!nodes[l].rightmost) {
            cout << "-1 -1";
        } else {
            cout << nodes[l].leftmost + 1 - size << ' ' << nodes[l].rightmost + 1 - size;
        }
        cout << '\n';
    }

    return 0;
}