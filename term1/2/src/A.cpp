#include <bits/stdc++.h>

using namespace std;

template<typename T>
class Stack
{
private:
    stack<T> mins;
public:
    void push(const int &v)
    {
        mins.push(mins.empty() || v < mins.top() ? v : mins.top());
    }

    void pop()
    {
        mins.pop();
    }

    T min()
    {
        return mins.top();
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Stack<int32_t> stack;
    size_t n;
    cin >> n;

    for (size_t i = 0; i < n; ++i) {
        unsigned char o;
        cin >> o;
        switch(o) { // NOLINT(hicpp-multiway-paths-covered)
            case '1':
                int32_t x;
                cin >> x;
                stack.push(x);
                break;
            case '2':
                stack.pop();
                break;
            case '3':
                cout << stack.min() << '\n';
                break;
        }
    }

    return 0;
}
