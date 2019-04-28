#include <iostream>
#define MAX 9223372036854775807
using namespace std;

struct ver {
    long long value;
    long long ad;
    bool flag;
    long long st;
};

int k, n;
long long res = MAX;
ver a[300000];

void push(int v) {
    if (a[v].flag == true){
        a[2 * v + 1].st = a[v].st;
        a[2 * v + 2].st = a[v].st;
        a[2 * v + 1].flag = a[v].flag;
        a[2 * v + 2].flag = a[v].flag;
        a[2 * v + 1].ad = 0;
        a[2 * v + 2].ad = 0;
    }
    a[2 * v + 1].ad += a[v].ad;
    a[2 * v + 2].ad += a[v].ad;
    a[v].ad = 0;
    a[v].st = 0;
    a[v].flag = false;
}

void update(int v, long long x, int tl, int tr, int l, int r) {
    if (l > tr || r < tl) {
        return;
    }
    if (l >= tl && r <= tr) {
        a[v].ad = 0;
        a[v].flag = true;
        a[v].st = x;
        return;
    }
    if (v <= k - 1) {
        push(v);
        update(2 * v + 1, x, tl, tr, l, (l + r) / 2);
        update(2 * v + 2, x, tl, tr, (l + r) / 2 + 1, r);
        long long v1, v2;
        a[2 * v + 1].flag == true ? v1 = a[2 * v + 1].st : v1 = a[2 * v + 1].value;
        a[2 * v + 2].flag == true ? v2 = a[2 * v + 2].st : v2 = a[2 * v + 2].value;
        v1 += a[2 * v + 1].ad;
        v2 += a[2 * v + 2].ad;
        a[v].value = min(v1, v2);
    }
}

void add(int v, long long x, int tl, int tr, int l, int r) {
    if (l > tr || r < tl) {
        return;
    }
    if (l >= tl && r <= tr) {
        a[v].ad += x;
        return;
    }
    if (v <= k - 1) {
        push(v);
        add(2 * v + 1, x, tl, tr, l, (l + r) / 2);
        add(2 * v + 2, x, tl, tr, (l + r) / 2 + 1, r);
        long long v1, v2;
        a[2 * v + 1].flag == true ? v1 = a[2 * v + 1].st : v1 = a[2 * v + 1].value;
        a[2 * v + 2].flag == true ? v2 = a[2 * v + 2].st : v2 = a[2 * v + 2].value;
        v1 += a[2 * v + 1].ad;
        v2 += a[2 * v + 2].ad;
        a[v].value = min(v1, v2);
    }
}

void get(int v, int tl, int tr, int l, int r) {
    if (l > tr || r < tl) {
        return;
    }
    if (l >= tl && r <= tr) {
        if (a[v].flag == true) {
            res = min(res, a[v].st + a[v].ad);
        } else {
            res = min(res, a[v].value + a[v].ad);
        }
        return;
    }
    if (v <= k - 1) {
        push(v);
        get(2 * v + 1, tl, tr, l, (l + r) / 2);
        get(2 * v + 2, tl, tr, (l + r) / 2 + 1, r);
        long long v1, v2;
        a[2 * v + 1].flag == true ? v1 = a[2 * v + 1].st : v1 = a[2 * v + 1].value;
        a[2 * v + 2].flag == true ? v2 = a[2 * v + 2].st : v2 = a[2 * v + 2].value;
        v1 += a[2 * v + 1].ad;
        v2 += a[2 * v + 2].ad;
        a[v].value = min(v1, v2);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin >> n;
    k = 1;
    while (k < n) {
        k *= 2;
    }
    for (int i = k - 1; i < k - 1 + n; i++) {
        cin >> a[i].value;
        a[i].ad = 0;
        a[i].st = 0;
        a[i].flag = false;
    }
    for (int i = k - 1 + n; i < 2 * k - 1; i++) {
        a[i].value = MAX;
        a[i].ad = 0;
        a[i].st = 0;
        a[i].flag = false;
    }
    for (int i = k - 2; i >= 0; i--) {
        a[i].value = min(a[2 * i + 1].value, a[2 * i + 2].value);
        a[i].ad = 0;
        a[i].st = 0;
        a[i].flag = false;
    }
    string s;
    while (cin >> s) {
        if (s == "set") {
            int i, j;
            long long x;
            cin >> i >> j >> x;
            update(0, x, i, j, 1, k);
        }
        if (s == "add") {
            int i, j;
            long long x;
            cin >> i >> j >> x;
            add(0, x, i, j, 1, k);
        }
        if (s == "min") {
            int i, j;
            cin >> i >> j;
            res = MAX;
            get(0, i, j, 1, k);
            cout << res << endl;
        }
    }
    return 0;
}