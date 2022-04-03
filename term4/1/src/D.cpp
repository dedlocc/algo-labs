#include <iostream>
#include <utility>
#include <vector>
#include <cmath>
#include <charconv>

using namespace std;

struct Kuhn
{
    explicit Kuhn(size_t n) : edges(n), matching(n, NO_MATCHING), visited(n)
    {}

    void addEdge(size_t u, size_t v)
    {
        edges[u].push_back(v);
    }

    size_t run()
    {
        for (size_t u = 0; u < edges.size() / 2; ++u) {
            fill(visited.begin(), visited.end(), false);
            dfs(u);
        }

        return std::count_if(matching.begin(), matching.end(), [](size_t v) {
            return v != NO_MATCHING;
        });
    }

private:
    bool dfs(size_t u)
    {
        if (exchange(visited[u], true)) {
            return false;
        }

        for (auto v : edges[u]) {
            if (matching[v] == NO_MATCHING || dfs(matching[v])) {
                matching[v] = u;
                return true;
            }
        }
        return false;
    }

private:
    vector<vector<size_t>> edges;
    vector<size_t> matching;
    vector<unsigned char> visited;

    static constexpr size_t NO_MATCHING = -1;
};

struct UFO
{
    int time;
    int x, y;

    friend istream &operator>>(istream &in, UFO &ufo)
    {
        string time;
        cin >> time;

        from_chars(time.data(), time.data() + 2, ufo.x);
        from_chars(time.data() + 3, time.data() + 5, ufo.y);

        ufo.time = ufo.x * 60 + ufo.y;

        cin >> ufo.x >> ufo.y;

        return in;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, v;
    cin >> n >> v;

    Kuhn kuhn(n * 2);

    vector<UFO> ufos;

    for (size_t i = 0; i < n; ++i) {
        cin >> ufos.emplace_back();
    }

    sort(ufos.begin(), ufos.end(), [](auto &a, auto &b) { return a.time < b.time; });

    for (size_t i = 0; i < n; ++i) {
        const auto &[t1, x1, y1] = ufos[i];
        for (size_t j = 0; j < i; ++j) {
            const auto &[t2, x2, y2] = ufos[j];
            if (hypot(x2 - x1, y2 - y1) * 60 <= v * (t1 - t2)) {
                kuhn.addEdge(i, n + j);
            }
        }
    }

    cout << n - kuhn.run();

    return 0;
}