#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 9223372036854775807

using namespace std;

int k, n, m;
long long a[300000];
struct req{
    long long min;
    int l, r;
};

vector<req> r;

bool cmp(req f, req s) {
    if (f.min < s.min) return true;
    return false;
}

long long get(int v, int tl, int tr, int l, int r) {
    if (l > tr || r < tl) {
        return MAX;
    }
    if (l >= tl && r <= tr) {
        return a[v];
    }
    if (v < k - 1) {
        return min(get(2 * v + 1, tl, tr, l, (l + r) / 2), get(2 * v + 2, tl, tr, (l + r) / 2 + 1, r));
    }
    return MAX;
}

void push(int v) {
    if (v >= k - 1) {
        return;
    }
    if (a[v] != MAX) {
        if (a[2 * v + 1] == MAX || a[2 * v + 1] < a[v]) {
            a[2 * v + 1] = a[v];
        }
        if (a[2 * v + 2] == MAX || a[2 * v + 2] < a[v]) {
            a[2 * v + 2] = a[v];
        }
    }
    push(2 * v + 1);
    push(2 * v + 2);
}

void update(int v, long long x, int tl, int tr, int l, int r) {
    if (l > tr || r < tl) {
        return;
    }
    if (l >= tl && r <= tr) {
        a[v] = x;
        return;
    }
    if (v < k - 1) {
        update(2 * v + 1, x, tl, tr, l, (l + r) / 2);
        update(2 * v + 2, x, tl, tr, (l + r) / 2 + 1, r);
    }
}

int main(){
    freopen("rmq.in", "rt", stdin);
    freopen("rmq.out", "wt", stdout);
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    k = 1;
    while (k < n) {
        k *= 2;
    }
    for (int i = 0; i < 2 * k - 1; i++) {
        a[i] = MAX;
    }
    for (int i = 0; i < m; i++) {
        req t;
        cin >> t.l >> t.r >> t.min;
        r.push_back(t);
    }
    sort(r.begin(), r.end(), cmp);
    for (int i = 0; i < m; i++) {
        update(0, r[i].min, r[i].l, r[i].r, 1, k);
    }
    push(0);
    for (int i = k - 2; i >= 0; i--) {
        a[i] = min(a[2 * i + 1], a[2 * i + 2]);
    }
    for (int i = 0; i < m; i++) {
        long long t = get(0, r[i].l, r[i].r, 1, k);
        if (t != r[i].min) {
            cout << "inconsistent";
            return 0;
        }
    }
    cout << "consistent" << endl;
    for (int i = k - 1; i < n + k - 1; i++) {
        if (a[i] == MAX) {
            cout << 228 << " ";
        } else cout << a[i] << " ";
    }
    return 0;
}