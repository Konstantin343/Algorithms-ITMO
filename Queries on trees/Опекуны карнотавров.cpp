#include <iostream>
#include <vector>

using namespace std;

int snm[200005];
vector<int> a(200005), depth(200005);

int get(int v) {
	if (snm[v] != v) {
		snm[v] = get(snm[v]);
	}
	return snm[v];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n = 200005, m;
	cin >> m;
	
	a[1] = 1;
	int d[200005][21] = {};
	
	snm[1] = 1;
	depth[1] = 0;
	d[1][0] = 1;
	int l = 0;
	for (int i = 0; (1 << i) < n; i++) {
		d[1][i + 1] = d[d[1][i]][i];
		l = i;
	}
	int t = 2;
	char c;
	for (int i = 0; i < m; i++) {
		cin >> c;
		if (c == '+') {
			int v;
			cin >> v;
			d[t][0] = a[t] = v;
			depth[t] = depth[v] + 1;
			snm[t] = t;
			for (int i = 0; (1 << i) < n; i++) {
				d[t][i + 1] = d[d[t][i]][i];
			}
			t++;
		}
		if (c == '-') {
			int v;
			cin >> v;
			int pv = a[v];
			if (v == snm[v]) {
				pv = get(pv);
				snm[v] = pv;
			}
		}
		if (c == '?') {
			int v, u, lca;
			cin >> v >> u;
			if (depth[v] < depth[u]) {
				swap(u, v);
			}
			int h = depth[v] - depth[u];
			for (int j = l; j >= 0; j--) {
				if ((1 << j) <= h) {
					h -= (1 << j);
					v = d[v][j];
				}
			}
			if (v != u) {
				for (int j = l; j >= 0; j--) {
					if (d[v][j] != d[u][j]) {
						v = d[v][j];
						u = d[u][j];
					}
				}
				lca = d[u][0];;
			}
			else {
				lca = v;
			}
			lca = get(lca);
			cout << lca << endl;
		}
	}
	return 0;
}