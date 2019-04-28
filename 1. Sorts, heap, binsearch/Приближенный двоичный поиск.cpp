#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long a[100001];

int binSearch (int l, int r, int x) {
    if (r - l < 1)
        return r;
    else if (r - l == 1) {
        if (abs(a[l] - x) <= abs(a[r] - x))
            return l;
        else
            return r;
    } else {
        int m = (l + r) / 2;
        if (x == a[m])
            return m;
        else if (x < a[m])
            binSearch(l, m, x);
        else
            binSearch(m, r, x);
    }
}

int main()
{
    vector <long long> ans;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < m; i ++) {
        int q;
        cin >> q;
        ans.push_back(a[binSearch(0, n - 1, q)]);
    }
    for (int i = 0; i < m; i++)
        cout << ans[i] << endl;
    return 0;
}
close