#include <bits/stdc++.h>

using namespace std;

int a[100001];
int n = 0;
int k = 0;

void push(int e) {
    a[n] = e;
    n++;
}

void del() {
    n--;
}

void check() {
    int u = 1;
    for (int j = n - 1; j >= 1; j--) {
        if (a[j] == a[j - 1]) {
            u++;
        } else break;
    }
    if (u >= 3) {
        k += u;
        n -= u;
        check();
    }

}

int main()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int p;
        cin >> p;
        if (p != a[n - 1])
            check();
        push(p);

    }
    check();
    cout << k;
    return 0;
}
close