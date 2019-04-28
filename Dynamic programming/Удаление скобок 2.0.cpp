#include <bits/stdc++.h>

using namespace std;

int main() {
    string s;
    cin >> s;
    int d[201][201] = {};
    string a[201][201];
    for (int x = 1; x < s.length(); x++) {
        for (int l = 0; l < s.length() - x; l++) {
            int r = l + x;
            for (int i = l; i <= r; i++) {
                if (d[l][i] + d[i + 1][r] > d[l][r]) {
                    d[l][r] = d[l][i] + d[i + 1][r];
                    a[l][r] = a[l][i] + a[i + 1][r];
                }
            }
            if (s[l] == '(' && s[r] == ')' || s[l] == '[' && s[r] == ']' || s[l] == '{' && s[r] == '}') {
                if (d[l + 1][r - 1] + 2 > d[l][r]) {
                    d[l][r] = d[l + 1][r - 1] + 2;
                    a[l][r] = s[l] + a[l + 1][r - 1] + s[r];
                }
            }
        }
    }
    cout << a[0][s.length() - 1];
    return 0;
}