#include <iostream>

using namespace std;

int main()
{
	int n, x, y, m, z, t;
	long long s = 0;
	long long a[10000005], b[20000005];
	cin >> n >> x >> y >> a[0];
	cin >> m >> z >> t >> b[0];
	for (size_t i = 1; i < n; i++) {
		a[i] = (x * a[i - 1] + y) % (1 << 16);
	}
	for (size_t i = 1; i < 2 * m; i++) {
		b[i] = (z * b[i - 1] + t) % (1 << 30);
	}
	for (size_t i = 0; i < 2 * m; i++) {
		b[i] %= n;
		if (b[i] < 0) b[i] = 0;
	}
	for (size_t i = 1; i < n; i++) {
		a[i] += a[i - 1];
	}
	for (size_t i = 0; i < m; i++) {
		if (min(b[2 * i], b[2 * i + 1]) > 0)
			s += (a[max(b[2 * i + 1], b[ 2 * i])] - a[min(b[2 * i + 1], b[2 * i]) - 1]);
		else
			s += a[max(b[2 * i + 1], b[2 * i])];
	}
	cout << s;
	return 0;
}