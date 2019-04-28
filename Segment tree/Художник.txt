#include <iostream>
#define MAX 9223372036854775807
using namespace std;

struct ver {
    int cnt, sum, left, right, flag;
};

int k, n;
ver a[(1 << 21) - 1];

void push(int v) {
    if (a[v].flag) {
        a[2 * v + 1].cnt = a[v].cnt;
        a[2 * v + 2].cnt = a[v].cnt;
        a[2 * v + 1].left = a[v].left;
        a[2 * v + 2].left = a[v].left;
        a[2 * v + 1].right = a[v].right;
        a[2 * v + 2].right = a[v].right;
        a[2 * v + 1].sum = a[v].sum / 2;
        a[2 * v + 2].sum = a[v].sum / 2;
        a[2 * v + 1].flag = a[v].flag;
        a[2 * v + 2].flag = a[v].flag;
        a[v].flag = 0;
    }
}

void black(int v, int tl, int tr, int l, int r) {
    if (l > tr || r < tl) {
        return;
    }
    if (l >= tl && r <= tr) {
        a[v].flag = 1;
        a[v].right = 1;
        a[v].left = 1;
        a[v].cnt = 1;
        a[v].sum = (r - l + 1);
        return;
    }
    if (v <= (1 << 20) - 1) {
        push(v);
        black(2 * v + 1, tl, tr, l, (l + r) / 2);
        black(2 * v + 2, tl, tr, (l + r) / 2 + 1, r);
        a[v].cnt = a[2 * v + 1].cnt + a[2 * v + 2].cnt;
        if (a[2 * v + 2].left & a[2 * v + 1].right) {
            a[v].cnt--;
        }
        a[v].sum = a[2 * v + 1].sum + a[2 * v + 2].sum;
        a[v].right = a[2 * v + 2].right;
        a[v].left = a[2 * v + 1].left;
    }
}

void white(int v, int tl, int tr, int l, int r) {
    if (l > tr || r < tl) {
        return;
    }
    if (l >= tl && r <= tr) {
        a[v].flag = 1;
        a[v].right = 0;
        a[v].left = 0;
        a[v].cnt = 0;
        a[v].sum = 0;
        return;
    }
    if (v <= (1 << 20) - 1) {
        push(v);
        white(2 * v + 1, tl, tr, l, (l + r) / 2);
        white(2 * v + 2, tl, tr, (l + r) / 2 + 1, r);
        a[v].cnt = a[2 * v + 1].cnt + a[2 * v + 2].cnt;
        if (a[2 * v + 2].left & a[2 * v + 1].right) {
            a[v].cnt--;
        }
        a[v].sum = a[2 * v + 1].sum + a[2 * v + 2].sum;
        a[v].right = a[2 * v + 2].right;
        a[v].left = a[2 * v + 1].left;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < (1 << 21) - 1; i++) {
        a[i].cnt = 0;
        a[i].sum = 0;
        a[i].left = 0;
        a[i].right = 0;
        a[i].flag = 0;
    }
    string s;
    for (int i = 0; i < n; i++) {
        cin >> s;
        if (s == "W") {
            int x, l;
            cin >> x >> l;
            x += 500001;
            white(0, x, x + l - 1, 1, (1 << 20));
            cout << a[0].cnt << " " << a[0].sum << endl;
        }
        if (s == "B") {
            int x, l;
            cin >> x >> l;
            x += 500001;
            black(0, x, x + l - 1, 1, (1 << 20));
            cout << a[0].cnt << " " << a[0].sum << endl;
        }
    }
    return 0;
}
