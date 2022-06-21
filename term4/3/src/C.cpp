#include <algorithm>
#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int r1, s1, p1, r2, s2, p2;
    cin >> r1 >> s1 >> p1 >> r2 >> s2 >> p2;

    cout << max(0, max({r1 + s2, s1 + p2, p1 + r2}) - (r1 + s1 + p1));

    return 0;
}
