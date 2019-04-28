#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

struct str{
    long long v;
    int s;
};

int main(){
    vector<long long> a(100007);
    long long v, u;
    long long m[200007][20];
    int n, p;
    cin >> n >> p >> a[0];
    vector<str> exp(100007);
    long long tmp = 1;
    int t = 0;
    for (int i = 1; i <= n; i++) {
        if (i >= 2 * tmp) {
            tmp *= 2;
            t++;
        }
        exp[i].v = tmp;
        exp[i].s = t;
    }
    m[0][0] = a[0];
    for (int i = 1; i < n; i++) {
        a[i] = (long long)(23 * a[i - 1] + 21563) % 16714589;
        m[i][0] = a[i];
    }
    for (int j = 1; j <= t; j++) {
        for (int i = 0; i < n; i++) {
            m[i][j] = min(m[i][j - 1], m[i + (1 << (j - 1))][j - 1]);
        }
    }
    cin >> u >> v;
    long long ans = 0;
    for (int i = 0; i < p; i++) {
        int k = exp[abs(v - u) + 1].s;
        int e = exp[abs(v - u) + 1].v;
        ans = min(m[min(u, v) - 1][k], m[max(u, v) - e][k]);
        if (i != p - 1) {
            u = (((17 * u) % n + 751 + ans + 2 * (i + 1)) % n) + 1;
            v = (((13 * v) % n + 593 + ans + 5 * (i + 1)) % n) + 1;
        }
    }
    cout << u << " " << v << " " << ans;
    return 0;
}