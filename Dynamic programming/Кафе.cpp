#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    int a[200];
    cin >> n;
    int m[200][200] = {};
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            m[i][j] = 1e9;
    if (a[1] <= 100) {
        m[1][0] = a[1];
        m[1][1] = 1e9;
    } else {
        m[1][0] = m[1][1] = a[1];
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            if (a[i] <= 100)
                m[i][j] = min(m[i - 1][j] + a[i], m[i - 1][j + 1]);
            else {
                if (j > 0)
                    m[i][j] = min(m[i - 1][j - 1] + a[i], m[i - 1][j + 1]);
                else m[i][j] = m[i - 1][j + 1];
            }
        }
    }
    int k1 = 0;
    for (int i = 0; i <= n; i++) {
        if (m[n][i] <= m[n][0] && m[n][i] > 0) {
            m[n][0] = m[n][i];
            k1 = i;
        }
    }
    if (n == 0) cout << 0 << '\n';
    else cout << m[n][0] << '\n';
    cout << k1 << " ";
    vector<int> ans;
    int i = n;
    int j = k1;
    while(i > 1) {
        if (a[i] <= 100) {
            if (m[i - 1][j] + a[i] > m[i - 1][j + 1]) {
                j++;
                ans.push_back(i);
            }
        } else {
            if (j > 0) {
                if (m[i - 1][j - 1] + a[i] <= m[i - 1][j + 1])
                    j--;
                else {
                    j++;
                    ans.push_back(i);
                }
            } else {
                j++;
                ans.push_back(i);
            }
        }
        i--;
    }
    cout << ans.size() << '\n';
    for(int u = ans.size() - 1; u >= 0; u--)
        cout << ans[u] << '\n';
    return 0;
}