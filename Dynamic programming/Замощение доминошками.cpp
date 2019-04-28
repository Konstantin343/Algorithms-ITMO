#include <bits\stdc++.h>

using namespace std;

int n, m;
char a[20][20] = {};

bool good(int x, int y, int u) {
    x |= (1 << n);
    y |= (1 << n);
    int i = 0;
    while (i < n) {
        if (int(x & (1 << i)) != 0 && int(y & (1 << i)) != 0 && a[i][u] != 'X') return false;
        if (int(x & (1 << i)) == 0 && (int(y & (1 << i)) == 0 || a[i][u] == 'X')){
            if (int(x & (1 << (i + 1))) != 0 || (int(y & (1 << (i + 1))) != 0 && a[i + 1][u] != 'X'))
                return false;
                i++;
        }
        i++;
    }
    return true;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++)
            if (i < n && j < m)
                cin >> a[i][j];
            else a[i][j] = '.';
    }
    long long d[15][1 << 13] = {};
    int p = 0;
    for (int i = 0; i < n; i++)
        if (a[i][0] == 'X') p |= (1 << i);
    d[0][p] = 1;
    for (int i = 1; i <= m; i++) {
        int o = p;
        p = 0;
        for (int j = 0; j < n; j++)
            if (a[j][i] == 'X') p |= (1 << j);
        for (int x = 0; x <= (1 << n) - 1; x++) {
            for (int y = 0; y <= (1 << n) - 1; y++) {
                if (int(y & p) == p && int(x & o) == o && int((x & y) | p) == p)
                    if(good(x, y, i))
                    d[i][y] += d[i - 1][x];
            }
        }
    }
    cout << d[m][0];
    return 0;
}