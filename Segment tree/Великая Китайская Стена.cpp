#include <iostream>
#define MAX 9223372036854775807

using namespace std;

struct ver {
    long long min, pos, flag;
};

long long ans = MAX, pos = 1;

int k, n, m;
ver a[(1 << 23) - 1]; //2100000

void push(int v) {
    if (a[v].flag) {
        if (a[2 * v + 1].min < a[v].min) {
            a[2 * v + 1].flag = a[v].flag;
            a[2 * v + 1].min = a[v].min;
        }
        if (a[2 * v + 2].min < a[v].min) {
            a[2 * v + 2].flag = a[v].flag;
            a[2 * v + 2].min = a[v].min;
        }
        a[v].flag = 0;
    }
}


void defend(int v, long long x, int tl, int tr, int l, int r) {
    if (l > tr || r < tl) {
        return;
    }
    if (l >= tl && r <= tr) {
        if (a[v].min < x) {
            a[v].min = x;
            a[v].flag = 1;
        }
        return;
    }
    if (v < k - 1) {
        push(v);
        defend(2 * v + 1, x, tl, tr, l, (l + r) / 2);
        defend(2 * v + 2, x, tl, tr, (l + r) / 2 + 1, r);
        if (a[2 * v + 1].min < a[2 * v + 2].min) {
            a[v].min = a[2 * v + 1].min;
            a[v].pos = a[2 * v + 1].pos;
        } else {
            a[v].min = a[2 * v + 2].min;
            a[v].pos = a[2 * v + 2].pos;
        }
    }
}

void get(int v, int tl, int tr, int l, int r) {
    if (l > tr || r < tl) {
        return;
    }
    if (l >= tl && r <= tr) {
        if (a[v].min < ans) {
            ans = a[v].min;
            pos = a[v].pos;
        }
        return;
    }
    if (v < k - 1) {
        push(v);
        get(2 * v + 1, tl, tr, l, (l + r) / 2);
        get(2 * v + 2, tl, tr, (l + r) / 2 + 1, r);
        if (a[2 * v + 1].min < a[2 * v + 2].min) {
            a[v].min = a[2 * v + 1].min;
            a[v].pos = a[2 * v + 1].pos;
        } else {
            a[v].min = a[2 * v + 2].min;
            a[v].pos = a[2 * v + 2].pos;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    k = 1;
    while (k < n) {
        k *= 2;
    }
    for (int i = k - 1; i < 2 * k + 1; i++) {
        if(i < n + k - 1)
            a[i].min = 0;
        else a[i].min = MAX;
        a[i].pos = i - (k - 2);
        a[i].flag = 0;
    }
    for (int i = k - 2; i >= 0; i--) {
        if (a[2 * i + 1].min < a[2 * i + 2].min) {
            a[i].min = a[2 * i + 1].min;
            a[i].pos = a[2 * i + 1].pos;
        } else {
            a[i].min = a[2 * i + 2].min;
            a[i].pos = a[2 * i + 2].pos;
        }
        a[i].flag = 0;
    }
    string s;
    for (int i = 0; i < m; i++) {
        cin >> s;
        if (s == "defend") {
            int l, r;
            long long t;
            cin >> l >> r >> t;
            defend(0, t, l, r, 1, k);
        }
        if (s == "attack") {
            int l, r;
            cin >> l >> r;
            ans = MAX;
            pos = 1;
            get(0, l, r, 1, k);
            cout << ans << " " << pos << "\n";
        }
    }
    return 0;
}