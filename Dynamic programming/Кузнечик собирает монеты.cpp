#include <bits/stdc++.h>

using namespace std;

int main()
{
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
    int n, k;
    cin >> n >> k;
    int d[10001];
    d[0] = 0;
    int a[10001];
    vector<int> ans;
    a[0] = 0;
    a[n - 1] = 0;
    int cur;

    for (int i = 1; i < n - 1; i++) {
        cin >> a[i];
    }

    for (int i = 1; i < n; i++) {
        d[i] = d[i - 1] + a[i];
        for (int j = i - 1; j >= max(0, i - k); j--)
            if (d[j] + a[i] > d[i]) {
                d[i] = d[j] + a[i];
            }
    }
    int i = n - 1;
    while(i != 0) {
        for (int j = i - 1; j >= max(0, i - k); j--)
            if (d[j] == d[i] - a[i]) {
                cur = j;
                ans.push_back(cur + 1);
                i = cur;
                break;
            }
    }

    cout << d[n - 1] << '\n' << ans.size() << '\n';
    for (i = ans.size() - 1; i >= 0; i--) {
        cout << ans[i] << " ";
    }
    cout << n;
    return 0;
}