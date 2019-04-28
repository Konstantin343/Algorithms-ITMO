#include <bits/stdc++.h>

using namespace std;

int main()
{
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
    int n, k;
    cin >> n >> k;
    int d[1001][1001];
    int a[1001][1001];
    vector<char> ans;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            cin >> a[i][j];
        }
    }
    d[0][0] = a[0][0];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            if (i > 0 && j > 0)
                d[i][j] = max(d[i - 1][j], d[i][j - 1]) + a[i][j];
            else if (i > 0)
                d[i][j] = d[i - 1][j] + a[i][j];
            else if (j > 0)
                d[i][j] = d[i][j - 1] + a[i][j];
        }
    }
    int i = n - 1;
    int j = k - 1;
    while(i != 0 || j != 0) {
            if (i > 0 && j > 0) {
                if (d[i - 1][j] > d[i][j - 1]) {
                    ans.push_back('D');
                    i--;
                }
                else {
                    ans.push_back('R');
                    j--;
                }
            } else if (i > 0) {
                ans.push_back('D');
                i--;
            } else if (j > 0) {
                ans.push_back('R');
                j--;
            }
    }
    cout << d[n - 1][k - 1] << '\n';
    for (int i = ans.size() - 1; i >= 0; i--)
        cout << ans[i];
    return 0;
}