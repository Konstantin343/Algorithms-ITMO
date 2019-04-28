#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

struct node{
    long long x;
    int y;
    node* left;
    node* right;
    long long sum;
    node(long long newX, int newY) {
        sum = newX;
        left = NULL;
        right = NULL;
        x = newX;
        y = newY;
    }
};

void update(node* cur) {
    if (cur == NULL) {
        return;
    }
    if (cur->left != NULL && cur->right != NULL) {
        cur->sum = cur->x + cur->left->sum + cur->right->sum;
    } else if (cur->left != NULL) {
        cur->sum = cur->x + cur->left->sum;
    } else if (cur->right != NULL) {
        cur->sum = cur->x + cur->right->sum;
    } else {
        cur->sum = cur->x;
    }
}

pair<node*, node*> split(node* cur, long long k) {
    if (cur == NULL) {
        return pair<node*, node*>(NULL, NULL);
    } else if (k > cur->x) {
        pair<node*, node*> ans = split(cur->right, k);
        cur->right = ans.first;
        update(cur->right);
        return make_pair(cur, ans.second);
    } else {
        pair<node*, node*> ans = split(cur->left, k);
        cur->left = ans.second;
        update(cur->left);
        return make_pair(ans.first, cur);
    }
}

node* merge(node* t1, node* t2) {
    if (t2 == NULL) {
        return t1;
    }
    if (t1 == NULL) {
        return t2;
    }
    if (t1->y > t2->y) {
        t1->right = merge(t1->right, t2);
        update(t1->right);
        return t1;
    } else {
        t2->left = merge(t1, t2->left);
        update(t2->left);
        return t2;
    }
}

node* insert(node* cur, node* v) {
    pair<node*, node*> p = split(cur, v->x);
    update(p.first);
    update(p.second);
    p.first = merge(p.first, v);
    update(p.first);
    node* r = merge(p.first, p.second);
    update(r);
    return r;
}

node* remove(node* cur, long long x) {
    pair<node*, node*> p = split(cur, x);
    pair<node*, node*> p2 = split(p.second, x + 1);
    return merge(p.first, p2.second);
}

void printTree(node *cur) {
    if (cur == NULL) {
        return;
    }
    cout << cur->x << ", sum: " << cur->sum << endl;
    if (cur->left != NULL) {
        cout << "left of " << cur->x << ": ";
        printTree(cur->left);
    }
    if (cur->right != NULL) {
        cout << "right of " << cur->x << ": ";
        printTree(cur->right);
    }
}

pair<node*, long long> sum(node* cur, int l, int r) {
    pair<node*, node*> p = split(cur, l);
    update(p.first);
    update(p.second);
    pair<node*, node*> p2 = split(p.second, r + 1);
    update(p.first);
    update(p.second);
    update(p2.first);
    update(p2.second);
   /* printTree(p.first);
    cout << endl;
    printTree(p2.first);
    cout << endl;
    printTree(p2.second);
    cout << endl;*/
    long long ans;
    if (p2.first != NULL) {
        ans = p2.first->sum;
    } else {
        ans = 0;
    }
    node* r1 = merge(p2.first, p2.second);
    update(r1);
    node* r2 = merge(p.first, r1);
    update(r2);
    return make_pair(r2, ans);
}

node* find(node* cur, long long x) {
    if (cur == NULL) {
        return cur;
    }
    if (x == cur->x) {
        return cur;
    } else if (x > cur->x) {
        if (cur->right == NULL) {
            return cur;
        } else {
            return find(cur->right, x);
        }
    } else {
        if (cur->left == NULL) {
            return cur;
        } else {
            return find(cur->left, x);
        }
    }
}

bool exists(node* cur, long long x) {
    node* tmp = find(cur, x);
    if (tmp == NULL) {
        return false;
    }
    if (tmp->x == x) {
        return true;
    }
    return false;
}

int main(){
    ios_base::sync_with_stdio(false);
    char s;
    node* treap = NULL;
    int sz;
    cin >> sz;
    char lop;
    long long lans = 0;
    for (int j = 0; j < sz; ++j) {
        cin >> s;
        if (s == '+') {
            long long x;
            cin >> x;
            if (lop == '?') {
                x = (x + lans) % 1000000000;
            }
            if (!exists(treap, x)) {
                treap = insert(treap, new node(x, (int)(rand() * RAND_MAX + rand())));
                update(treap);
            }
            lop = '+';
        }
        if (s == '?') {
            long long l, r;
            cin >> l >> r;
            pair<node*, long long> ans = sum(treap, l, r);
            treap = ans.first;
            cout << ans.second << endl;
            lop = '?';
            lans = ans.second;
        }
    }
    return 0;
}