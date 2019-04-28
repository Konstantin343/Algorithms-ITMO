#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

struct node{
	int value;
	node* left;
	node* right;
	node* parent;
	node(node* p, int v) {
		left = NULL;
		right = NULL;
		value = v;
		parent = p;
	}
};

void printTree(node *cur) {
	cout << cur->value << endl;
	if (cur->left != NULL) {
		cout << "left of " << cur->value << ": ";
		printTree(cur->left);
	}
	if (cur->right != NULL) {
		cout << "right of " << cur->value << ": ";
		printTree(cur->right);
	}
}

node* fnd(int v, node* cur) {
	if (v == cur->value) {
		return cur;
	} else if (v > cur->value) {
		if (cur->right == NULL) {
			return cur;
		} else {
			return fnd(v, cur->right);
		}
	} else {
		if (cur->left == NULL) {
			return cur;
		} else {
			return fnd(v, cur->left);
		}
	}
}

bool exists(int v, node* cur) {
	node* tmp = fnd(v, cur);
	if (tmp->value == v) {
		return true;
	}
	return false;
}

void ins(int v, node* cur) {
	node* tmp = fnd(v, cur);
	if (v > tmp->value) {
		tmp->right = new node(tmp, v);
	} else if (v < tmp->value) {
		tmp->left = new node(tmp, v);
	}
}

void del(int v, node* cur) {
	node* tmp = fnd(v, cur);
	if (v == tmp->value) {
		node* f;
		if (tmp->left != NULL) {
			f = tmp->left;
			while (f->right != NULL) {
				f = f->right;
			}
			tmp->value = f->value;
			if (f == f->parent->left) {
				f->parent->left = f->left;
			} else {
				f->parent->right = f->left;
			}
			if (f->left != NULL) f->left->parent = f->parent;
		} else if (tmp->right != NULL) {
			f = tmp->right;
			while (f->left != NULL) {
				f = f->left;
			}
			tmp->value = f->value;
			if (f == f->parent->left) {
				f->parent->left = f->right;
			} else {
				f->parent->right = f->right;
			}
			if (f->right != NULL) f->right->parent = f->parent;
		} else {
			if (tmp->parent != NULL) {
				if (tmp == tmp->parent->left)
					tmp->parent->left = NULL;
				else tmp->parent->right = NULL;
			}
		}
	}
}

node* nxt(int v, node* cur) {
	node* tmp = fnd(v, cur);
	if (tmp->value > v) {
		return tmp;
	} else {
		if (tmp->right != NULL) {
			tmp = tmp->right;
			while (tmp->left != NULL) {
				tmp = tmp->left;
			}
		} else {
			while (tmp->parent != NULL && tmp != tmp->parent->left) {
				tmp = tmp->parent;
			}
			if (tmp->parent != NULL) {
				tmp = tmp->parent;
			}
		}
		if (tmp->value > v) {
			return tmp;
		} else {
			return NULL;
		}
	}
}

node* prv(int v, node* cur) {
	node* tmp = fnd(v, cur);
	if (tmp->value < v) {
		return tmp;
	} else {
		if (tmp->left != NULL) {
			tmp = tmp->left;
			while (tmp->right != NULL) {
				tmp = tmp->right;
			}
		} else {
			while (tmp->parent != NULL && tmp != tmp->parent->right) {
				tmp = tmp->parent;
			}
			if (tmp->parent != NULL) {
				tmp = tmp->parent;
			}
		}
		if (tmp->value < v) {
			return tmp;
		} else {
			return NULL;
		}
	}
}

int main(){
	int tree_size = 0;
	string s;
	node* tree = NULL;
	while (cin >> s) {
		if (s == "insert") {
			int v;
			cin >> v;
			if (tree_size == 0) {
				tree = new node(NULL, v);
				tree_size++;
			} else {
				if (!exists(v, tree)) tree_size++;
				ins(v, tree);
			}
		}
		if (s == "delete") {
			int v;
			cin >> v;
			if (tree_size != 0) {
				if (exists(v, tree)) {
					del(v, tree);
					tree_size--;
				}
			}
		}
		if (s == "exists") {
			int v;
			cin >> v;
			if (tree_size == 0) {
				cout << "false";
			} else {
				if (exists(v, tree)) {
					cout << "true";
				} else {
					cout << "false";
				}
			}
			cout << endl;
		}
		if (s == "next") {
			int v;
			cin >> v;
			if (tree_size == 0) {
				cout << "none";
			} else {
				if (nxt(v, tree) == NULL) {
					cout << "none";
				} else {
					cout << nxt(v, tree)->value;
				}
			}
			cout << endl;
		}
		if (s == "prev") {
			int v;
			cin >> v;
			if (tree_size == 0) {
				cout << "none";
			} else {
				if (prv(v, tree) == NULL) {
					cout << "none";
				} else {
					cout << prv(v, tree)->value ;
				}
			}
			cout << endl;
		}
	}
	return 0;
}