#include <cmath>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>

using namespace std;

struct Vertex
{
    int x, y;
    double weight;
    bool included {};
    Vertex *p {};

    Vertex(int x, int y) : x(x), y(y), weight(numeric_limits<double>::max())
    {}

    bool operator==(const Vertex &other) const
    {
        return x == other.x && y == other.y;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<Vertex> vertices;

    for (size_t i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        vertices.emplace_back(x, y);
    }

    vertices.front().weight = 0;

    double sum = 0;

    for (size_t i = 0; i < n; ++i) {
        Vertex *vPtr = nullptr;
        for (auto &v : vertices) {
            if (!v.included && (!vPtr || v.weight < vPtr->weight)) {
                vPtr = &v;
            }
        }
        auto &v = *vPtr;
        v.included = true;

        if (v.p) {
            sum += v.weight;
        }

        for (auto &u : vertices) {
            if (u != v) {
                u.weight = min(u.weight, hypot(v.x - u.x, v.y - u.y));
                u.p = &v;
            }
        }
    }

    cout << sum;

    return 0;
}