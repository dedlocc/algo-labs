#include <iostream>
#include <unordered_set>
#include <vector>
#include <optional>

using namespace std;

struct Solution
{
    Solution() : k(1, 1)
    {
        input();
        input();
    }

    string lcs()
    {
        size_t l = 0, r = minLength + 1;

        size_t pos;
        while (l + 1 < r) {
            size_t m = (l + r) / 2;

            unordered_set<uint64_t> hh;
            for (size_t i = 0; i <= s[0].size() - m; ++i) {
               hh.insert(subHash(0, i, i + m));
            }

            optional<size_t> p;
            for (size_t i = 0; i <= s[1].size() - m; ++i) {
                if (hh.contains(subHash(1, i, i + m))) {
                    p = i;
                    break;
                }
            }

            if (p) {
                l = m;
                pos = p.value();
            } else {
                r = m;
            }
        }

        unordered_set<uint64_t> hh;
        for (size_t i = 0; i <= s[0].size() - l; ++i) {
            hh.insert(subHash(0, i, i + l));
        }

        string minString = "~";
        for (size_t i = pos; i <= s[1].size() - l; ++i) {
            if (hh.contains(subHash(1, i, i + l))) {
                if (string str = s[1].substr(i, l); str < minString) {
                    minString = str;
                }
            }
        }

        return minString;
    }

private:
    void input()
    {
        auto &hh = h.emplace_back(1, 0);
        auto &ss = s.emplace_back();
        cin >> ss;

        size_t i = 0;
        for (auto c : ss) {
            hh.push_back(hh.back() * 257 + c);
            if (++i == k.size()) {
                k.push_back(k.back() * 257);
            }
        }

        minLength = min(minLength, i);
    }

    uint64_t subHash(size_t i, size_t l, size_t r)
    {
        return h[i][r] - h[i][l] * k[r - l];
    };

    vector<uint64_t> k;
    vector<string> s;
    vector<vector<uint64_t>> h;
    size_t minLength = -1;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << Solution().lcs();

    return 0;
}