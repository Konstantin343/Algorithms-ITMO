#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

struct part {
	int min;
	int parent;
};

int main() {
    freopen("minonpath.in", "rt", stdin);
    freopen("minonpath.out", "wt", stdout);
	int n, m;
	cin >> n;
	vector<int> a(n + 5), depth(n + 5), w(n + 5);
	a[1] = 1;
	part d[200005][21] = {};
	depth[1] = 0;
	for (int i = 2; i <= n; i++) {
		cin >> a[i] >> w[i];
		depth[i] = depth[a[i]] + 1;
	}
	cin >> m;
	d[1][0].parent = 1;
	d[1][0].parent = 0;
	for (int v = 1; v <= n; v++) {
		d[v][0].parent = a[v];
		d[v][0].min = w[v];
	}
	int t = 0;
	for (int i = 0; (1 << i) < n; i++) {
		for (int v = 1; v <= n; v++) {
			d[v][i + 1].parent = d[d[v][i].parent][i].parent;
			d[v][i + 1].min = min(d[d[v][i].parent][i].min, d[v][i].min);
		}
		t = i;
	}
	for (int i = 0; i < m; i++) {
		int v, u, ans = 1e6 + 7;
		cin >> v >> u;
		if (depth[v] < depth[u]) swap(u, v);
		int h = depth[v] - depth[u];
		for (int j = t; j >= 0; j--) {
			if ((1 << j) <= h) {
				h -= (1 << j);
				ans = min(ans, d[v][j].min);
				v = d[v][j].parent;
			}
		}
		if (v != u) {
			for (int j = t; j >= 0; j--) {
				if (d[v][j].parent != d[u][j].parent) {
					ans = min(ans, d[v][j].min);
					ans = min(ans, d[u][j].min);
					v = d[v][j].parent;
					u = d[u][j].parent;
				}
			}
			ans = min(d[v][0].min, ans);
			ans = min(d[u][0].min, ans);
			cout << ans << endl;
		} else {
			cout << ans << endl;
		}
	}
	return 0;
}