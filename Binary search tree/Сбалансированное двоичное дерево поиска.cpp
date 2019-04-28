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
    node(int newX, int newY) {
        left = NULL;
        right = NULL;
        x = newX;
        y = newY;
    }
};

pair<node*, node*> split(node* cur, int k) {
    if (cur == NULL) {
        return pair<node*, node*>(NULL, NULL);
    } else if (k > cur->x) {
        pair<node*, node*> ans = split(cur->right, k);
        cur->right = ans.first;
        return make_pair(cur, ans.second);
    } else {
        pair<node*, node*> ans = split(cur->left, k);
        cur->left = ans.second;
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
        return t1;
    } else {
        t2->left = merge(t1, t2->left);
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
    cout << cur->x << endl;
    if (cur->left != NULL) {
        cout << "left of " << cur->x << ": ";
        printTree(cur->left);
    }
    if (cur->right != NULL) {
        cout << "right of " << cur->x << ": ";
        printTree(cur->right);
    }
}

node* find(node* cur, int x) {
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

bool exists(node* cur, int x) {
    node* tmp = find(cur, x);
    if (tmp == NULL) {
        return false;
    }
    if (tmp->x == x) {
        return true;
    }
    return false;
}

pair<node*, node*> next(node* cur, int x) {
    pair<node*, node*> p = split(cur, x + 1);
    node* tmp = p.second;
    if (tmp == NULL) {
        return  pair<node*, node*>(merge(p.first, p.second), NULL);
    }
    while (tmp->left != NULL) {
        tmp = tmp->left;
    }
    return make_pair(merge(p.first, p.second), tmp);
}

pair<node*, node*> prev(node* cur, int x) {
    pair<node*, node*> p = split(cur, x);
    node* tmp = p.first;
    if (tmp == NULL) {
        return pair<node*, node*>(merge(p.first, p.second), NULL);
    }
    while (tmp->right != NULL) {
        tmp = tmp->right;
    }
    return make_pair(merge(p.first, p.second), tmp);
}

int main(){
    string s;
    node* treap = NULL;
    while (cin >> s) {
        if (s == "insert") {
            int x;
            cin >> x;
            treap = insert(treap, new node(x, rand() * RAND_MAX + rand()));
        }
        if (s == "delete") {
            int x;
            cin >> x;
            treap = remove(treap, x);
        }
        if (s == "exists") {
            int x;
            cin >> x;
            if (exists(treap, x)) {
                cout << "true" << endl;
            } else {
                cout << "false" << endl;
            }
        }
        if (s == "next") {
            int x;
            cin >> x;
            pair<node*, node*> p = next(treap, x);
            treap = p.first;
            if (p.second != NULL) {
                cout << p.second->x << endl;
            } else {
                cout << "none" << endl;
            }
        }
        if (s == "prev") {
            int x;
            cin >> x;
            pair<node*, node*> p = prev(treap, x);
            treap = p.first;
            if (p.second != NULL) {
                cout << p.second->x << endl;
            } else {
                cout << "none" << endl;
            }
        }
    }
    return 0;
}