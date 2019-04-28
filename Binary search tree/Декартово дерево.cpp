#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

struct point{
    int a, b, i;
};

struct res {
    int l = 0, r = 0, p = 0;
};

vector<res> ans(300005);

bool cmp(point f, point s) {
    return (f.a < s.a);
}

struct node{
    int value, number, value2;
    node* left;
    node* right;
    node* parent;
    node(node* p, int v, int n, int v2) {
        number = n;
        value = v;
        parent = p;
        right = NULL;
        left = NULL;
        value2 = v2;
    }
};

node* ins(int v, node* cur, int n, int v2) {
    while (cur->value2 > v2) {
        if (cur->parent != NULL) {
            cur = cur->parent;
        } else {
            break;
        }
    }
    if (cur->value2 > v2) {
        node* tmp = cur;
        ans[n].l = cur->number;
        ans[cur->number].p = n;
        cur = new node(NULL, v, n, v2);
        cur->left = tmp;
        return cur;
    } else {
        node* tmp = cur;
        ans[n].p = cur->number;
        ans[cur->number].r = n;
        if (cur->right != NULL) {
            ans[n].l = cur->right->number;
            ans[cur->right->number].p = n;
        }
        cur->right = new node(cur, v, n, v2);
        cur->right->left = tmp->right;
        return cur->right;
    }
}

int main(){
    node* last;
    int n;
    cin >> n;
    vector<point> v(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i].a >> v[i].b;
        v[i].i = i;
    }
    sort(v.begin() + 1, v.end(), cmp);
    last = new node(NULL, v[1].a, v[1].i, v[1].b);
    for (int i = 2; i <= n; i++) {
        last = ins(v[i].a, last, v[i].i, v[i].b);
    }
    cout << "YES" << endl;
    for (int i = 1; i <= n; i++) {
        cout << ans[i].p << " " << ans[i].l << " " << ans[i].r << '\n';
    }
    return 0;
}