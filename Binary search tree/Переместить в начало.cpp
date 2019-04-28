#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

struct node{
    int x;
    int y;
    node* left;
    node* right;
    int size;
    node(int newX, int newY) {
        size = 1;
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
        cur->size = 1 + cur->left->size + cur->right->size;
    } else if (cur->left != NULL) {
        cur->size = 1 + cur->left->size;
    } else if (cur->right != NULL) {
        cur->size = 1 + cur->right->size;
    } else {
        cur->size = 1;
    }
}

pair<node*, node*> split(node* cur, int k) {
    if (cur == NULL) {
        return pair<node*, node*>(NULL, NULL);
    }
    int l = 0;
    if (cur->left != NULL) {
        l = cur->left->size;
    }
    if (k > l) {
        pair<node*, node*> ans = split(cur->right, k - l - 1);
        cur->right = ans.first;
        update(cur->right);
        update(cur);
        update(ans.second);
        return make_pair(cur, ans.second);
    } else {
        pair<node*, node*> ans = split(cur->left, k);
        cur->left = ans.second;
        update(cur->left);
        update(cur);
        update(ans.first);
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
        update(t1);
        return t1;
    } else {
        t2->left = merge(t1, t2->left);
        update(t2->left);
        update(t2);
        return t2;
    }
}

node* insert(node* cur, node* v, int k) {
    pair<node*, node*> p = split(cur, k);
    p.first = merge(p.first, v);
    return merge(p.first, p.second);
}

node* remove(node* cur, int x) {
    pair<node*, node*> p = split(cur, x);
    pair<node*, node*> p2 = split(p.second, x + 1);
    return merge(p.first, p2.second);
}

void printTree(node *cur) {
    if (cur == NULL) {
        return;
    }
    printTree(cur->left);
    cout << cur->x << " ";
    printTree(cur->right);
}

node* replace(node* cur, int l, int r) {
    pair<node*, node*> p = split(cur, l);
    pair<node*, node*> p2 = split(p.second, r - l + 1);
    node* p3 = merge(p2.first, p.first);
    return merge(p3, p2.second);
}

int main(){
    ios_base::sync_with_stdio(false);
    node* treap = NULL;
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        treap = insert(treap, new node(i, rand() * RAND_MAX + rand()), i);
    }
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        treap = replace(treap, l - 1, r - 1);
    }
    printTree(treap);
    return 0;
}