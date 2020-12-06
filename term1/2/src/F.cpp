#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    cin >> n;

    stack<size_t> a;
    vector<size_t> b;
    stringstream s;

    for (size_t i = 0; i < n; ++i) {
        size_t t;
        cin >> t;

        while (!a.empty() && a.top() < t) {
            s << "pop\n";
            b.push_back(a.top());
            a.pop();
        }

        s << "push\n";
        a.push(t);
    }

    while (!a.empty()) {
        s << "pop\n";
        b.push_back(a.top());
        a.pop();
    }

    cout << (is_sorted(b.begin(), b.end()) ? s.str() : "impossible");

    return 0;
}
