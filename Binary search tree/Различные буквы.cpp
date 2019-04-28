#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

int count(int a) {
	int res = 0;
	while (a != 0) {
		res++;
		a = a & (a - 1);
	}
	return res;
}

struct node {
	char x;
	int y;
	int letters;
	node* left;
	node* right;
	int size;
	int cnt;
	node(char newX, int newY, int newSZ) {
		letters = int(1 << (int(newX) - 97));
		cnt = newSZ;
		size = newSZ;
		left = NULL;
		right = NULL;
		x = newX;
		y = newY;
	}
};

void printTree(node *cur) {
	if (cur == NULL) {
		return;
	}
	printTree(cur->left);
	cout << cur->x << " " << cur->cnt << " size: " << cur->size << endl;
	printTree(cur->right);
}

void update(node* cur) {
	if (cur == NULL) {
		return;
	}
	if (cur->left != NULL && cur->right != NULL) {
		cur->size = cur->cnt + cur->left->size + cur->right->size;
		cur->letters = cur->left->letters | cur->right->letters | int(1 << (int(cur->x) - 97));
	}
	else if (cur->left != NULL) {
		cur->size = cur->cnt + cur->left->size;
		cur->letters = cur->left->letters | int(1 << (int(cur->x) - 97));
	}
	else if (cur->right != NULL) {
		cur->size = cur->cnt + cur->right->size;
		cur->letters = cur->right->letters | int(1 << (int(cur->x) - 97));
	}
	else {
		cur->size = cur->cnt;
		cur->letters = int(1 << (int(cur->x) - 97));
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
	}
	else {
		t2->left = merge(t1, t2->left);
		update(t2->left);
		update(t2);
		return t2;
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
	if (k > l && k < l + cur->cnt) {
		int lsize = 0;
		if (cur->left != NULL) lsize = cur->left->size;
		node* first = merge(cur->left, new node(cur->x, rand() * RAND_MAX + rand(), k - lsize));
		node* second = merge(new node(cur->x, rand() * RAND_MAX + rand(), cur->cnt - k + lsize), cur->right);
		return make_pair(first, second);
	}
	if (k > l) {
		pair<node*, node*> ans = split(cur->right, k - l - cur->cnt);
		cur->right = ans.first;
		update(cur->right);
		update(cur);
		update(ans.second);
		return make_pair(cur, ans.second);
	}
	else {
		pair<node*, node*> ans = split(cur->left, k);
		cur->left = ans.second;
		update(cur->left);
		update(cur);
		update(ans.first);
		return make_pair(ans.first, cur);
	}
}

node* insert(node* cur, node* v, int k) {
	pair<node*, node*> p = split(cur, k);
	p.first = merge(p.first, v);
	return merge(p.first, p.second);
}

node* remove(node* cur, int pos, int c) {
	pair<node*, node*> p = split(cur, pos);
	pair<node*, node*> p2 = split(p.second, c);
	return merge(p.first, p2.second);
}

node* query(node* cur, int l, int r) {
	pair<node*, node*> p = split(cur, l);
	pair<node*, node*> p2 = split(p.second, r - l + 1);
	if (p2.first == NULL) {
		cout << 0 << endl;
	}
	else {
		cout << count(p2.first->letters) << endl;
	}
	p.second = merge(p2.first, p2.second);
	return merge(p.first, p.second);
}

int main() {
	ios_base::sync_with_stdio(false);
	node* treap = NULL;
	int n;
	cin >> n;
	char s;
	for (int i = 0; i < n; i++) {
		cin >> s;
		if (s == '+') {
			int p, c;
			char l;
			cin >> p >> c >> l;
			treap = insert(treap, new node(l, rand() * RAND_MAX + rand(), c), p - 1);
		}
		if (s == '-') {
			int p, c;
			cin >> p >> c;
			treap = remove(treap, p - 1, c);
		}
		if (s == '?') {
			int l, r;
			cin >> l >> r;
			treap = query(treap, l - 1, r - 1);
		}
	}
	return 0;
}