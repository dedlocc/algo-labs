#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    s += '$';

    size_t const n = s.size();

    map<char, vector<size_t>> m;
    for (size_t i = 0; i < n; ++i) {
        m[s[i]].push_back(i);
    }

    vector<size_t> classes(n), p(n);
    size_t cnt = 0, classId = 0;

    for (auto &[_, v] : m) {
        for (auto i : v) {
            classes[i] = classId;
            p[cnt++] = i;
        }
        ++classId;
    }

    for (size_t h = 1; classId < n; h *= 2) {
        vector<vector<size_t>> np(classId);
        vector<size_t> oldClasses = classes;

        for (size_t i = 0; i < n; ++i) {
            size_t k = (p[i] - h + n) % n;
            np[oldClasses[k]].push_back(k);
        }

        cnt = 0;

        for (size_t i = 0, oldClassId = exchange(classId, 0); i < oldClassId; ++i) {
            for (size_t j = 0; j < np[i].size(); ++j) {
                if (j == 0 || oldClasses[(np[i][j] + h) % n] != oldClasses[(np[i][j - 1] + h) % n]) {
                    ++classId;
                }
                classes[np[i][j]] = classId - 1;
                p[cnt++] = np[i][j];
            }
        }
    }

    size_t cur = 0;
    vector<size_t> lcp(n - 1);
    for (size_t i = 0; i < n; ++i) {
        if (classes[i] + 1 == n) {
            continue;
        }
        for (size_t j = p[classes[i] + 1]; max(i, j) + cur < n && s[i + cur] == s[j + cur]; ++cur);
        if ((lcp[classes[i]] = cur)) {
            --cur;
        }
    }

    for (size_t i = 1; i < p.size(); ++i) {
        cout << p[i] + 1 << ' ';
    }
    cout << '\n';
    for (size_t i = 1; i < lcp.size(); ++i) {
        cout << lcp[i] << ' ';
    }


    return 0;
}