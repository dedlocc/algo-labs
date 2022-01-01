#include <iostream>
#include <map>
#include <numeric>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

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

    for (size_t h = 1; classId < n && h < n; h *= 2) {
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

    size_t k;
    cin >> k;

    vector<bool> used(n);
    cnt = 0;

    for (auto e : p) {
        if (!used[classes[e]]) {
            used[classes[e]] = true;
            ++cnt;
        }
        if (cnt == k) {
            for (size_t i = 0; i < n; ++i) {
                cout << s[(i + e) % n];
            }
            return 0;
        }
    }

    cout << "IMPOSSIBLE";

    return 0;
}