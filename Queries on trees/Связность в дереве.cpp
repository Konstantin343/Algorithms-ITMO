#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

struct node {
	int from;
	int to;
	int y;
	node* left;
	node* right;
	node* parent;
	int size;
	node(int f, int t) {
		size = 1;
		left = NULL;
		right = NULL;
		from = f;
		to = t;
		parent = NULL;
		y = rand() * RAND_MAX + rand();
	}
};

void print_tree(node* cur) {
	if (!cur) return;
	print_tree(cur->left);
	cout << "(" << cur->from << " -> " << cur->to << ") ";
	print_tree(cur->right);
}

int n, m;
vector<node*> nodes(200005);
map<pair<int, int>, node*> edges;

int size_of(node* cur) {
	if (cur) return cur->size;
	return 0;
}

node* get_root(node* cur) {
	if (cur == NULL) return NULL;
	while (cur->parent != NULL) {
		cur = cur->parent;
	}
	return cur;
}

node* get_right(node* cur) {
	if (cur == NULL) return NULL;
	while (cur->right != NULL) {
		cur = cur->right;
	}
	return cur;
}

node* get_left(node* cur) {
	if (cur == NULL) return NULL;
	while (cur->left != NULL) {
		cur = cur->left;
	}
	return cur;
}

int get_pos(node* cur) {
	if (cur == NULL) return 0;
	int ans = 1;
	if (cur->left != NULL) ans += cur->left->size;
	while (cur->parent != NULL) {
		if (cur == cur->parent->right)
			if (cur->parent->left != NULL) ans += cur->parent->left->size + 1;
			else ans += 1;
		cur = cur->parent;
	}
	return ans;
}

void update(node* cur) {
	if (cur == NULL) {
		return;
	}
	cur->size = 1 + size_of(cur->left) + size_of(cur->right);
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

void link(int f, int s) {
	node* u = nodes[f];
	node* v = nodes[s];
	pair<node*, node*> AB = split(get_root(u), get_pos(u));
	pair<node*, node*> CD = split(get_root(v), get_pos(v) );
	node* A = AB.first;
	node* B = AB.second;
	node* C = CD.first; 
	node* D = CD.second;
	edges.insert({ { f, s }, new node(f, s) });
	edges.insert({ { s, f }, new node(s, f) });
	if (nodes[f] == nullptr)
		nodes[f] = edges.at({ s, f });
	if (nodes[s] == nullptr)
		nodes[s] = edges.at({ f, s });
	A = merge(A, edges.at({ f, s }));
	A = merge(A, D);
	A = merge(A, C);
	A = merge(A, edges.at({ s, f }));
	A = merge(A, B);
	if (A) A->parent = nullptr;
}

void cut(int f, int s) {
	node* u = edges.at({ s, f });
	node* v = edges.at({ f, s });
	int pos_u = get_pos(u);
	int pos_v = get_pos(v);
	if (pos_v < pos_u) {
		swap(f, s);
		swap(pos_u, pos_v);
		swap(u, v);
	}
	pair<node*, node*> ABC = split(get_root(u), pos_u - 1);
	pair<node*, node*> BC = split(ABC.second, pos_v - pos_u);
	node* A = ABC.first;
	node* B = BC.first;
	node* C = BC.second;
	B = split(B, 1).second;
	C = split(C, 1).second; 
	edges.erase({ f, s });
	edges.erase({ s, f });
	nodes[f] = get_right(B);
	nodes[s] = get_right(A);
	if (C) nodes[s] = edges.at({ get_left(C)->to, get_left(C)->from });
	node* AC = merge(A, C);
	if (AC) AC->parent = nullptr;
	if (B) B->parent = nullptr;
}

bool connected(int f, int s) {
	return get_root(nodes[f]) && get_root(nodes[f]) == get_root(nodes[s]);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	string q = "";
	for (int i = 0; i < m; i++) {
		int f, s;
		cin >> q;
		if (q == "link") {
			cin >> f >> s;
			link(f, s);
		}
		if (q == "cut") {
			cin >> f >> s;
			cut(f, s);
		}
		if (q == "connected") {
			cin >> f >> s;
			cout << connected(f, s) << '\n';
		}
	}
	return 0;
}