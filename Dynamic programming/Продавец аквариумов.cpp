#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    int a[14][14];
    int d[1 << 13][14] = {};
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
    for (int i = 0; i < (1 << n); i++)
        for (int j = 0; j < n; j++)
            if (i == (1 << j)) d[i][j] = 0;
            else d[i][j] = 1e9;
    d[1][0] = 0;
    for (int m = 2; m < (1 << n); m++) {
        for (int i = 0; i < n; i++) {
            if (int(m & (1 << i)) != 0) {
                int m2 = m - (1 << i);
                for (int j = 0; j < n; j++) {
                    if (j != i && (int(m & (1 << j)) != 0)) {
                        d[m][i] = min(d[m][i], d[m2][j] + a[j][i]);
                    }
                }

            }
        }
    }
    int ans = 1e9, start = 0;
    for (int i = 0; i < n; i++) {
        if (d[(1 << n) - 1][i] < ans) {
            ans = d[(1 << n) - 1][i];
            start = i;
        }
    }
    cout << ans << '\n';
    int k = 0, m = (1 << n) - 1;
    vector<int> p;
    while(k < n - 1) {
        for (int j = 0; j < n; j++) {
            int m2 = m - (1 << start);
            if (d[m][start] == a[start][j] + d[m2][j]) {
                p.push_back(start + 1);
                start = j;
                m = m2;
                k++;
                break;
            }
        }
    }
    for (int u = 0; u < p.size(); u++)
        cout << p[u] << " ";
    cout << start + 1;
    return 0;
}