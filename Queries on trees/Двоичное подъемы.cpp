#include <iostream>
#include <vector>

using namespace std;

int main() {
	int n, root;
	cin >> n;
	vector<int> a(n + 5);
	int d[100005][21] = {};
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		if (a[i] == 0) {
			root = i;
		}
	}
	d[root][0] = root;
	for (int v = 1; v <= n; v++) {
		d[v][0] = a[v];
	}
	for (int i = 0; (1 << i) < n; i++) {
		for (int v = 1; v <= n; v++) {
			d[v][i + 1] = d[d[v][i]][i];
		}
	}
	for (int v = 1; v <= n; v++) {
		cout << v << ": ";
		int i = 0;
		while (d[v][i] != 0) {
			cout << d[v][i] << " ";
			i++;
		}
		cout << endl;
	}
	return 0;
}