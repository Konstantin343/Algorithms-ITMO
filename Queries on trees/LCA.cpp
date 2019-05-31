#include <iostream>
#include <vector>

using namespace std;

int main() {
	int n, m;
	cin >> n;
	vector<int> a(n + 5), depth(n + 5);
	a[1] = 1;
	int d[200005][21] = {};
	depth[1] = 0;
	for (int i = 2; i <= n; i++) {
		cin >> a[i];
		depth[i] = depth[a[i]] + 1;
	}
	cin >> m;
	d[1][0] = 1;
	for (int v = 1; v <= n; v++) {
		d[v][0] = a[v];
	}
	int t = 0;
	for (int i = 0; (1 << i) < n; i++) {
		for (int v = 1; v <= n; v++) {
			d[v][i + 1] = d[d[v][i]][i];
		}
		t = i;
	}
	for (int i = 0; i < m; i++) {
		int v, u;
		cin >> v >> u;
		if (depth[v] < depth[u]) swap(u, v);
		int h = depth[v] - depth[u];
		for (int j = t; j >= 0; j--) {
			if ((1 << j) <= h) {
				h -= (1 << j);
				v = d[v][j];
			}
		}
		if (v != u) {
			for (int j = t; j >= 0; j--) {
				if (d[v][j] != d[u][j]) {
					v = d[v][j];
					u = d[u][j];
				}
			}
			cout << d[u][0] << endl;
		} else {
			cout << v << endl;
		}
	}
	return 0;
}