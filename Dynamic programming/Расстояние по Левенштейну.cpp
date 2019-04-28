#include <bits/stdc++.h>

using namespace std;

int main() {
    string s, t;
    cin >> s;
    cin >> t;
    int d[1001][1001];
    d[0][0] = 0;
    for (int i = 0; i <= s.length(); i++) {
        for (int j = 0; j <= t.length(); j++) {
            if (i > 0 && j > 0) {
                d[i][j] = min(d[i - 1][j - 1], min(d[i - 1][j], d[i][j - 1]));
                    if (s[i - 1] != t[j - 1]) d[i][j]++;
                    else d[i][j] = d[i - 1][j - 1];
            } else if (i > 0) {
                d[i][j] = d[i - 1][j] + 1;
            } else if (j > 0) {
                d[i][j] = d[i][j - 1] + 1;
            }
        }
    }
    cout << d[s.length()][t.length()];
    return 0;
}