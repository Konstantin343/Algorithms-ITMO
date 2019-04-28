#include <iostream>
#include <stack>
#define MAX 9223372036854775807

using namespace std;

struct ver {
    int ff, fs, sf, ss;
};

stack<ver> dr;
ver ans;
int k, n, r, m;
ver a[1000000];

ver mul(ver t1, ver t2) {
    ver res;
    res.ff = (t1.ff * t2.ff + t1.fs * t2.sf) % r;
    res.fs = (t1.ff * t2.fs + t1.fs * t2.ss) % r;
    res.sf = (t1.sf * t2.ff + t1.ss * t2.sf) % r;
    res.ss = (t1.sf * t2.fs + t1.ss * t2.ss) % r;
    return res;
}

int main(){
    freopen("crypto.in", "rt", stdin);
    freopen("crypto.out", "wt", stdout);
    ios_base::sync_with_stdio(false);
    cin >> r >> n >> m;
    k = 1;
    while (k < n) {
        k *= 2;
    }
    for (int i = k - 1; i < k - 1 + n; i++) {
        cin >> a[i].ff >> a[i].fs >> a[i].sf >> a[i].ss;
    }
    for (int i = k - 1 + n; i < 2 * k - 1; i++) {
        a[i].ff = 1;
        a[i].fs = 0;
        a[i].sf = 0;
        a[i].ss = 1;
    }
    for (int i = k - 2; i >= 0; i--) {
        a[i] = mul(a[2 * i + 1], a[2 * i + 2]);
    }
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        ans.ff = 1;
        ans.ss = 1;
        ans.fs = 0;
        ans.sf = 0;
        l += (k - 2);
        r += (k - 2);
        while (r >= l) {
            if (l % 2 == 0) {
                ans = mul(ans, a[l]);
            }
            l /= 2;
            if (r % 2 == 1) {
                dr.push(a[r]);
            }
            r /= 2;
            r--;
        }
        while(dr.size() != 0) {
            ans = mul(ans, dr.top());
            dr.pop();
        }
        cout << ans.ff << " " << ans.fs << endl << ans.sf << " " << ans.ss << "\n\n";
    }
    return 0;
}