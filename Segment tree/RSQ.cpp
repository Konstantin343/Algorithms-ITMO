#include <iostream>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    int n;
    long long a[2000005] = {};
    cin >> n;
    int k = 1;
    while (k < n) {
        k *= 2;
    }
    for (int i = k - 1; i < k - 1 + n; i++)
        cin >> a[i];
    for (int i = k - 2; i >= 0; i--) {
        a[i] = a[2 * i + 1] + a[2 * i + 2];
    }
    string s;
    while (cin >> s) {
        if (s == "set") {
            long long i, v;
            cin >> i >> v;
            i += (k - 2);
            a[i] = v;
            while (i != 0) {
                i = (i - 1) / 2;
                a[i] = a[2 * i + 1] + a[2 * i + 2];
            }
        }
        if (s == "sum") {
            int l, r;
            cin >> l >> r;
            long long ans = 0;
            l += (k - 2);
            r += (k - 2);
            while (r >= l) {
                if (l % 2 == 0) {
                    ans += a[l];
                }
                l /= 2;
                if (r % 2 == 1) {
                ans += a[r];
                }
                r /= 2;
                r--;
            }
            cout << ans << endl;
        }
    }
    return 0;
}