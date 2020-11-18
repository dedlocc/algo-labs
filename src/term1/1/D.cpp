#include <bits/stdc++.h>

using std::cin, std::cout, std::vector;

template<typename T>
class Heap
{
    vector<T> a;

    void swap(const size_t &x, const size_t &y)
    {
        T t = a[x];
        a[x] = a[y];
        a[y] = t;
    }

public:
    void insert(const T &x)
    {
        a.emplace_back(x);
        for (size_t i = a.size() - 1; i > 0 && a[i] > a[(i - 1) / 2]; i = (i - 1) / 2) {
            swap(i, (i - 1) / 2);
        }
    }

    T extract()
    {
        T result = a[0];
        swap(0, a.size() - 1);
        a.pop_back();
        size_t i = 0, j = 0;

        while (true) {
            auto k = 2 * i + 1;
            if (k < a.size() && a[k] > a[j]) {
                j = k;
            }
            if (++k < a.size() && a[k] > a[j]) {
                j = k;
            }
            if (i == j) {
                break;
            }
            swap(i, j);
            i = j;
        }

        return result;
    }
};

int main()
{
    size_t n;
    cin >> n;

    Heap<uint32_t> heap;

    for (size_t i = 0; i < n; ++i) {
        bool action;
        cin >> action;
        if (action) {
            cout << heap.extract() << '\n';
        } else {
            uint32_t x;
            cin >> x;
            heap.insert(x);
        }
    }

    return 0;
}
