#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    long long d[101][11];
    for (int i = 0; i <= 9; i++)
        d[1][i] = 1;
    d[1][0] = 0;
    d[1][8] = 0;
    for (int i = 2; i <= n; i++) {
        d[i][0] = d[i - 1][4] + d[i - 1][6];
        d[i][1] = d[i - 1][6] + d[i - 1][8];
        d[i][2] = d[i - 1][7] + d[i - 1][9];
        d[i][3] = d[i - 1][4] + d[i - 1][8];
        d[i][4] = d[i - 1][3] + d[i - 1][9] + d[i - 1][0];
        d[i][5] = 0;
        d[i][6] = d[i - 1][1] + d[i - 1][7] + d[i - 1][0];
        d[i][7] = d[i - 1][2] + d[i - 1][6];
        d[i][8] = d[i - 1][1] + d[i - 1][3];
        d[i][9] = d[i - 1][4] + d[i - 1][2];
        for (int j = 0; j <= 9; j++)
            d[i][j] %= 1000000000;
    }
    long long s = 0;
    for (int i = 0; i <= 9; i++) {
        s += d[n][i];
        s %= 1000000000;
    }
    cout << s;
    return 0;
}