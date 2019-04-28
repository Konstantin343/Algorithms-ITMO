#include <bits/stdc++.h>

using namespace std;

int a[10000];
int n = 0;

void push(int e) {
    a[n] = e;
    n++;
}

void del() {
    n--;
}

int main()
{
    char c;
    while (cin >> c) {
        if (c >= '0' && c <= '9')
            push(int (c - 48));
        else {
            if (c == '+') {
                int e = a[n - 1] + a[n - 2];
                del();
                del();
                push(e);
            }
            if (c == '-') {
                int e = a[n - 2] - a[n - 1];
                del();
                del();
                push(e);
            }
            if (c == '*') {
                int e = a[n - 1] * a[n - 2];
                del();
                del();
                push(e);
            }
        }
    }
    cout << a[0];
    return 0;
}
close