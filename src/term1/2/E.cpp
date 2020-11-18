#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    stack<int32_t> s;

    unsigned char token;
    while (cin >> token) {
        if (token >= '0') {
            s.push(token - '0');
        } else {
            const auto a = s.top();
            s.pop();
            const auto b = s.top();
            s.pop();

            if ('+' == token) {
                s.push(a + b);
            } else if ('-' == token) {
                s.push(b - a);
            } else {
                s.push(a * b);
            }
        }
    }

    cout << s.top();

    return 0;
}
