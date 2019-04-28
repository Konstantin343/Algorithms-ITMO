#include <iostream>

using namespace std;

struct ver {
    int cnt0;
    int cnt1;
};

int k, n, m;
ver a[1000000];

int main(){
    freopen("parking.in", "rt", stdin);
    freopen("parking.out", "wt", stdout);
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    k = 1;
    while (k < n) {
        k *= 2;
    }
    for (int i = k - 1; i < 2 * k - 1; i++) {
        a[i].cnt1 = 0;
        a[i].cnt0 = 1;
    }
    for (int i = k - 2; i >= 0; i--) {
        a[i].cnt1 = 0;
        a[i].cnt0 = a[2 * i + 1].cnt0 + a[2 * i + 2].cnt0;
    }
    string s;
    for(int i = 0; i < m; i++) {
        cin >> s;
        if (s == "exit") {
            int p;
            cin >> p;
            p += k - 2;
            a[p].cnt0 = 1;
            a[p].cnt1 = 0;
            while (p != 0) {
                p = (p - 1) / 2;
                a[p].cnt0 = a[2 * p + 1].cnt0 + a[2 * p + 2].cnt0;
                a[p].cnt1 = a[2 * p + 1].cnt1 + a[2 * p + 2].cnt1;
            }
        }
        if (s == "enter") {
            int p;
            cin >> p;
            if (a[p + k - 2].cnt0 == 1) {
                cout << p << endl;
                p += k - 2;
                a[p].cnt0 = 0;
                a[p].cnt1 = 1;
                while (p != 0) {
                    p = (p - 1) / 2;
                    a[p].cnt0 = a[2 * p + 1].cnt0 + a[2 * p + 2].cnt0;
                    a[p].cnt1 = a[2 * p + 1].cnt1 + a[2 * p + 2].cnt1;
                }
            } else {
                int rgcnt0 = 0;
                int rgcnt1 = 0;
                int ltcnt0 = 0;
                int ltcnt1 = 0;
                int l = p + k - 1;
                int r = n + k - 2;
                while (r >= l) {
                    if (l % 2 == 0) {
                        rgcnt0 += a[l].cnt0;
                        rgcnt1 += a[l].cnt1;
                    }
                    l /= 2;
                    if (r % 2 == 1) {
                        rgcnt0 += a[r].cnt0;
                        rgcnt1 += a[r].cnt1;
                    }
                    r /= 2;
                    r--;
                }
                ltcnt0 = a[0].cnt0 - rgcnt0 - (k - n);
                ltcnt1 = a[0].cnt1 - rgcnt1 - 1;
                int t = 1;
                if (rgcnt0 > 0) {
                    t += ltcnt0;
                }
                int v = 0;
                while (v < k - 1) {
                    if (a[2 * v + 1].cnt0 >= t) {
                        v = 2 * v + 1;
                    } else {
                        t -= a[2 * v + 1].cnt0;
                        v = 2 * v + 2;
                    }
                }
                p = v;
                a[p].cnt0 = 0;
                a[p].cnt1 = 1;
                while (p != 0) {
                    p = (p - 1) / 2;
                    a[p].cnt0 = a[2 * p + 1].cnt0 + a[2 * p + 2].cnt0;
                    a[p].cnt1 = a[2 * p + 1].cnt1 + a[2 * p + 2].cnt1;
                }
                cout << v - k + 2 << endl;
            }
        }
    }
    return 0;
}