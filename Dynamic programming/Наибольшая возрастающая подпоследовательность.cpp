#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int a[2001], b[2001], d[2001];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        d[i] = 1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++)
            if (a[j] < a[i]) {
                if (d[j] + 1 > d[i]) {
                    d[i] = d[j] + 1;
                }
            }
    }
    int m = d[0], j = 0;
    for (int i = 0; i < n; i++) {
        if (d[i] > m) {
            m = d[i];
            j = i;
        }
    }
    vector<int> ans;
    ans.push_back(a[j]);
    for(int i = j; i >= 0; i--) {
        if (a[i] < a[j] && d[i] == d[j] - 1) {
            j = i;
            ans.push_back(a[j]);
        }
    }
    cout << m << '\n';
    for (int i = ans.size() - 1; i >= 0; i--)
        cout << ans[i] << " ";
    return 0;
}