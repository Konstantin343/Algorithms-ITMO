#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct node{
    int max_pref;
    int sum;
    int flag;
    node *l, *r;
    node() {
        flag = 0;
        sum = 0;
        max_pref = 0;
        l = NULL;
        r = NULL;
    }
};

void push(node *v) {
    if (v->l == NULL) {
        v->l = new node();
    }
    if (v->r == NULL) {
        v->r = new node();
    }
    if (v->flag == 1) {
        v->l->sum = v->sum / 2;
        v->l->flag = 1;
        v->l->max_pref = max(0, v->l->sum);
        v->r->sum = v->sum / 2;
        v->r->flag = 1;
        v->r->max_pref = max(0, v->r->sum);
        v->flag = 0;
    }
}

void update(node *v, int x, int tl, int tr, int l, int r) {
    if (l > tr || r < tl) {
        return;
    }
    if (l >= tl && r <= tr) {
        v->flag = 1;
        v->sum = x * (r - l + 1);
        v->max_pref = max(0, x * (r - l + 1));
        return;
    }
    if (r - l > 0) {
        push(v);
        update(v->l, x, tl, tr, l, (l + r) / 2);
        update(v->r, x, tl, tr, (l + r) / 2 + 1, r);
        v->sum = v->l->sum + v->r->sum;
        v->max_pref = max(v->l->max_pref, v->l->sum + v->r->max_pref);
    }
}

int get(node *v, int h, int l, int r) {
    if (r - l == 0) {
        return v->max_pref <= h ? r : r - 1;
    }
    push(v);
    v->sum = v->l->sum + v->r->sum;
    v->max_pref = max(v->l->max_pref, v->l->sum + v->r->max_pref);
    if (v->l->max_pref <= h) {
        return get(v->r, h - (v->l->sum), (l + r) / 2 + 1, r);
    } else {
        return get(v->l, h, l, (l + r) / 2);
    }
}

int main(){
    vector<int> ans;
    int n;
    node *tree = new node();
    cin >> n;
    string s = "";
    ios_base::sync_with_stdio(false);
    int i = 0;
    while (s != "E") {
        i++;
        cin >> s;
        if (s == "I") {
            int l, r, x;
            cin >> l >> r >> x;
            update(tree, x, l, r, 1, (1 << 30));
        }
        if (s == "Q") {
            int h;
            cin >> h;
            cout << min(n, get(tree, h, 1, (1 << 30))) << endl;
        }
    }
    return 0;
}