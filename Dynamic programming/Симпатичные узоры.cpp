#include <bits\stdc++.h>

using namespace std;

int n, m;

bool good(int x, int y) {
    for (int i = 0; i < n - 1; i++) {
        if (int(x & (1 << i)) != 0 && int(y & (1 << i)) != 0)
            if (int(x & (1 << (i + 1))) != 0 && int(y & (1 << (i + 1))) != 0)
                return false;
        if (int(x & (1 << i)) == 0 && int(y & (1 << i)) == 0)
            if (int(x & (1 << (i + 1))) == 0 && int(y & (1 << (i + 1))) == 0)
                return false;
    }
    return true;
}

int main() {
    freopen("nice.in", "rt", stdin);
    freopen("nice.out", "wt", stdout);
    cin >> n >> m;
    if (n > m) swap(n, m);
    int d[2][1 << 15] = {};
    for (int i = 0; i <= (1 << n) - 1; i++)
        d[1][i] = 1;
    for (int i = 2; i <= m; i++) {
        for (int x = 0; x <= (1 << n) - 1; x++) {
            for (int y = 0; y <= (1 << n) - 1; y++) {
                if (x == 0)
                    d[i % 2][y] = 0;
                if (good(x, y))
                    d[i % 2][y] += d[(i - 1) % 2][x];
            }
        }
    }
    int s = 0;
    for (int i = 0; i <= (1 << n) - 1; i++)
       s += d[m % 2][i];
    cout << s;
    return 0;
}