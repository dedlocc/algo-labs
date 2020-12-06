#include <bits/stdc++.h>

using std::cin, std::cout, std::vector;

uint64_t counter = 0;

template<typename T>
vector<T> merge(const vector<T> &a, const vector<T> &b)
{
    const auto n = a.size(), m = b.size();
    size_t i = 0, j = 0, k = 0;

    vector<T> c(n + m);

    while (i < n || j < m) {
        c[k++] = j == m || i < n && a[i] < b[j] ? a[i++] : (counter += n - i, b[j++]);
    }

    return c;
}

template<typename T>
vector<T> sort(const vector<T> &a)
{
    const auto n = a.size();
    if (n <= 1) {
        return a;
    }
    const auto al = sort(vector<T>(a.begin(), a.begin() + n / 2));
    const auto ar = sort(vector<T>(a.begin() + n / 2, a.end()));

    return merge(al, ar);
}

int main()
{
    size_t n;
    cin >> n;

    auto a = vector<uint32_t>(n);

    for (auto &e : a) {
        cin >> e;
    }

    sort(a);

    cout << counter;

    return 0;
}