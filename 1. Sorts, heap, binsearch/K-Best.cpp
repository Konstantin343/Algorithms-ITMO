#include <bits/stdc++.h>

using namespace std;

double w[100001];
double v[100001];

int check (double x, int cnt, int e, int o) {
    double s = 0;
    vector< pair<double, int> > a;
    for (int i = 0; i < cnt; i++) {
        a.push_back(make_pair(v[i] - x * w[i], i));
    }
    sort(a.begin(), a.end());
    for (int i = cnt - 1; i >= cnt - e; i--) {
        s += a[i].first;
        if (o == 1)
            cout << a[i].second + 1<<endl;
    }
    if (s >= 0)
        return 1;
    else return 0;
}

int main()
{
    freopen("kbest.in", "rt", stdin);
    freopen("kbest.out", "wt", stdout);
    int k, n;
    cin >> n >> k;
    double maxA = 0;
    double minA = 1e7;
    for (int i = 0; i < n; i++) {
            cin >> v[i] >> w[i];
            maxA = max(maxA, v[i] / w[i]);
            minA = min(minA, v[i] / w[i]);
    }
    double r = maxA;
    double l = minA;
    while (r - l > 0.00000001) {
        double m = (r + l) / 2;
        if (check(m, n, k, 0) == 0)
            r = m;
        else
            l = m;
    }
    check(l,n,k,1);
    return 0;
}