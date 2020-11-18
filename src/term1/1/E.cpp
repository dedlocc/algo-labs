#include <bits/stdc++.h>

using std::cin, std::cout, std::vector;

template<typename T>
typename vector<T>::iterator leftBound(vector<T> &a, const T &val)
{
    auto l = a.begin() - 1;
    auto r = a.end();

    while (r - l > 1) {
        const auto m = l + (r - l) / 2;
        if (*m < val) {
            l = m;
        } else {
            r = m;
        }
    }

    return r;
}

template<typename T>
typename vector<T>::iterator rightBound(vector<T> &a, const T &val)
{
    auto l = a.begin() - 1;
    auto r = a.end();

    while (r - l > 1) {
        const auto m = l + (r - l) / 2;
        if (*m <= val) {
            l = m;
        } else {
            r = m;
        }
    }

    return l;
}

int main()
{
    size_t n;
    cin >> n;

    vector<int32_t> a(n);

    for (auto &e : a) {
        cin >> e;
    }

    std::sort(a.begin(), a.end());

    size_t k;
    cin >> k;

    while (0 < k--) {
        int32_t l, r;
        cin >> l >> r;

        const auto left = leftBound(a, l);
        const auto right = rightBound(a, r);

        cout << (left == a.end() || right < a.begin() ? 0 : right - left + 1) << ' ';
    }


    return 0;
}
