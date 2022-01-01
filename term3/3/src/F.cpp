#include <iostream>
#include <set>
#include <vector>
#include <optional>

using namespace std;

struct Solution
{
    explicit Solution(size_t n) : k(1, 1)
    {
        for (size_t i = 0; i < n; ++i) {
            input();
        }
    }

    string lcs()
    {
        size_t l = 0, r = minLength + 1;

        size_t pos;
        while (l + 1 < r) {
            size_t m = (l + r) / 2;

            set<uint64_t> hh;
            for (size_t i = 0; i <= s[0].size() - m; ++i) {
                hh.insert(subHash(0, i, i + m));
            }

            for (size_t j = 2; j < s.size(); ++j) {
                set<uint64_t> hh2;
                for (size_t i = 0; i <= s[j].size() - m; ++i) {
                    hh2.insert(subHash(j, i, i + m));
                }
                auto it1 = hh.begin(), it2 = hh2.begin();
                while (it1 != hh.end() && it2 != hh2.end()) {
                    if (*it1 < *it2) {
                        it1 = hh.erase(it1);
                    } else if (*it2++ == *it1) {
                        ++it1;
                    }
                }
                hh.erase(it1, hh.end());
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

        return s[1].substr(pos, l);
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

    size_t k;
    cin >> k;

    cout << Solution(k).lcs();

    return 0;
}