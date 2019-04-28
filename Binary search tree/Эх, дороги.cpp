#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

struct node {
	int x;
	int y;
	bool cycle;
	node* left;
	node* right;
	node* parent;
	int size;
	node(int newX) {
		size = 1;
		left = NULL;
		right = NULL;
		parent = NULL;
		x = newX;
		y = rand() * RAND_MAX + rand();
		cycle = false;
	}
};

node* getParent(node* cur) {
	if (cur == NULL) return NULL;
	while (cur->parent != NULL) {
		cur = cur->parent;
	}
	return cur;
}

int getPos(node* cur) {
	if (cur == NULL) return 0;
	int ans = 0;
	if (cur->left != NULL) ans += cur->left->size;
	while (cur->parent != NULL) {
		if (cur == cur->parent->right) 
			if (cur->parent->left != NULL) ans += cur->parent->left->size + 1;
			else ans += 1;
		cur = cur->parent;
	}
	return ans;
}

void reverse(node* cur) {
	if (cur == NULL) return;
	swap(cur->left, cur->right);
	reverse(cur->left);
	reverse(cur->right);
}

void update(node* cur) {
	if (cur == NULL) {
		return;
	}
	if (cur->left != NULL && cur->right != NULL) {
		cur->size = 1 + cur->left->size + cur->right->size;
	}
	else if (cur->left != NULL) {
		cur->size = 1 + cur->left->size;
	}
	else if (cur->right != NULL) {
		cur->size = 1 + cur->right->size;
	}
	else {
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
		if (cur->right != NULL)
			cur->right->parent = cur;
		update(cur->right);
		update(cur);
		update(ans.second);
		return make_pair(cur, ans.second);
	}
	else {
		pair<node*, node*> ans = split(cur->left, k);
		cur->left = ans.second;
		if (cur->left != NULL)
			cur->left->parent = cur;
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
		if (t1->right != NULL)
			t1->right->parent = t1;
		update(t1->right);
		update(t1);
		return t1;
	}
	else {
		t2->left = merge(t1, t2->left);
		if (t2->left != NULL)
			t2->left->parent = t2;
		update(t2->left);
		update(t2);
		return t2;
	}
}

void add(node* v, node* u) {
	node* pv = getParent(v);
	node* pu = getParent(u);
	if (pv == pu) {
		pv->cycle = true;
		return;
	} 
	if (getPos(v) == 0) reverse(pv);
	if (getPos(u) == pu->size - 1) reverse(pu);
	merge(pv, pu);
}

void remove(node* v, node* u) {
	node* pv = getParent(v);
	if (pv->cycle == true) {
		pv->cycle = false;
		if (abs(getPos(v) - getPos(u)) == pv->size - 1) return;
		pair<node*, node*> p = split(pv, max(getPos(v), getPos(u)));
		reverse(p.first);
		reverse(p.second);
		merge(p.first, p.second);
		return;
	}
	pair<node*, node*> p = split(pv, max(getPos(v), getPos(u)));
	p.first->parent = NULL;
	p.second->parent = NULL;
}

int query(node* v, node* u) {
	node* pv = getParent(v);
	node* pu = getParent(u);
	if (pv != pu) {
		return -1;
	}
	if (pv->cycle == true) {
		return min(abs(getPos(v) - getPos(u)), min(getPos(u), getPos(v)) + (pv->size - max(getPos(u), getPos(v)))) - 1;
	}
	return abs(getPos(v) - getPos(u)) - 1;
}

int main() {
	ios_base::sync_with_stdio(false);
	node* treap = NULL;
	int n, m, q;
	cin >> n >> m >> q;
	vector<node*> nodes(n + 5);
	for (int i = 1; i <= n; i++) {
		nodes[i] = new node(i);
	}
	for (int i = 0; i < m; i++) {
		int t, p;
		cin >> t >> p;
		add(nodes[t], nodes[p]);
	}
	char cmd;
	int t, p;
	for (int i = 0; i < q; i++) {
		cin >> cmd >> t >> p;
		if (cmd == '+') {
			add(nodes[t], nodes[p]);
		}
		if (cmd == '-') {
			remove(nodes[t], nodes[p]);
		}
		if (cmd == '?') {
			if (t == p) cout << 0 << endl;
			else cout << query(nodes[t], nodes[p]) << endl;
		}
	}
	return 0;
}