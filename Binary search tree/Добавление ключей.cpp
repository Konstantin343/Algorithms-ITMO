#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

vector<int> res;

struct node {
	int x;
	int y;
	node* left;
	node* right;
	int size;
	int cnt0;
	node(int newX, int newY) {
		size = 1;
		left = NULL;
		right = NULL;
		x = newX;
		y = newY;
		if (newX == 0) {
			cnt0 = 1;
		}
		else {
			cnt0 = 0;
		}
	}
};



void printTree(node* cur) {
	if (cur == NULL) {
		return;
	}
	printTree(cur->left);
	res.push_back(cur->x);
	printTree(cur->right);
}

pair<int, node*> getZero(node* cur) {
	if (cur == NULL) {
		return pair<int, node*>(-1, NULL);
	}
	int ans = 0;
	while (true) {
		if (cur->left == NULL && cur->x == 0) {
			break;
		}
		if (cur->left != NULL && cur->left->cnt0 == 0 && cur->x == 0) {
			ans += cur->left->size;
			break;
		}
		if (cur->left != NULL && cur->left->cnt0 > 0) {
			cur = cur->left;
		}
		if (cur->left == NULL && cur->x != 0) {
			cur = cur->right;
			ans++;
		}
		if (cur->left != NULL && cur->left->cnt0 == 0 && cur->x != 0) {			
			ans += (cur->left->size + 1);
			cur = cur->right;
		}
	}
	return make_pair(ans, cur);
}

void update(node* cur) {
	if (cur == NULL) {
		return;
	}
	if (cur->left != NULL && cur->right != NULL) {
		cur->size = 1 + cur->left->size + cur->right->size;
		cur->cnt0 = cur->left->cnt0 + cur->right->cnt0;
		if (cur->x == 0) { cur->cnt0++; }
	}
	else if (cur->left != NULL) {
		cur->size = 1 + cur->left->size;
		cur->cnt0 = cur->left->cnt0;
		if (cur->x == 0) { cur->cnt0++; }
	}
	else if (cur->right != NULL) {
		cur->size = 1 + cur->right->size;
		cur->cnt0 = cur->right->cnt0;
		if (cur->x == 0) { cur->cnt0++; }
	}
	else {
		cur->size = 1;
		if (cur->x == 0) { 
			cur->cnt0 = 1; 
		} else {
			cur->cnt0 = 0;
		}
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

node* replace(node* cur, node* v, int k) {
	pair<node*, node*> p = split(cur, k);
	pair<int, node*> zero = getZero(p.second);	
	pair<node*, node*> p2 = split(p.second, zero.first);
	pair<node*, node*> p3 = split(p2.second, 1);
	return merge(merge(p.first, v), merge(p2.first, p3.second));
}

int main() {
	ios_base::sync_with_stdio(false);
	node* treap = NULL;
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n + m; i++) {
		treap = insert(treap, new node(0, rand() * RAND_MAX + rand()), 0);
	}
	for (int i = 0; i < n; i++) {
		int pos;
		cin >> pos;
		treap = replace(treap, new node(i + 1, rand() * RAND_MAX + rand()), pos - 1);
	}
	printTree(treap);
	int t = res.size() - 1;
	for (int i = res.size() - 1; i >= 0; i--) {
		if (res[i] != 0) {
			t = i;
			break;
		}
	}
	cout << t + 1 << endl;
	for (int i = 0; i <= t; i++) {
		cout << res[i] << " ";
	}
	return 0;
}