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
    p.first = merge(p.first, v);
    return merge(p.first, p.second);
}

node* remove(node* cur, int x) {
    pair<node*, node*> p = split(cur, x);
    pair<node*, node*> p2 = split(p.second, x + 1);
    return merge(p.first, p2.second);
}

void printTree(node *cur) {
    cout << cur->x << ", size: " << cur->size << endl;
    if (cur->left != NULL) {
        cout << "left of " << cur->x << ": ";
        printTree(cur->left);
    }
    if (cur->right != NULL) {
        cout << "right of " << cur->x << ": ";
        printTree(cur->right);
    }
}

int kmax(node* cur, int k) {
    if (cur->right != NULL && k == cur->right->size + 1) {
        return cur->x;
    }
    if (cur->right == NULL && k == 1) {
        return cur->x;
    }
    if (cur->right != NULL && k <= cur->right->size) {
        return kmax(cur->right, k);
    }
    if (cur->right != NULL && k > cur->right->size) {
        return kmax(cur->left, k - cur->right->size - 1);
    }
    if (cur->right == NULL && k > 0) {
        return kmax(cur->left, k - 1);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    int s;
    node* treap = NULL;
    int sz;
    cin >> sz;
    for (int j = 0; j < sz; ++j) {
        cin >> s;
        if (s == 1) {
            int x;
            cin >> x;
            treap = insert(treap, new node(x, (int)(rand() * RAND_MAX + rand())));
            update(treap);
        }
        if (s == -1) {
            int x;
            cin >> x;
            treap = remove(treap, x);
            update(treap);
        }
        if (s == 0) {
            int k;
            cin >> k;
            cout << kmax(treap, k) << endl;
        }
    }
    return 0;
}