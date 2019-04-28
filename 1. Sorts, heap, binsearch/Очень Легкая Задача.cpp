#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int check (int x, int s1, int s2, int len) {
    if (x / s1 + x / s2 < len)
        return 0;
    else
        return 1;
}

int main()
{
    long long i = 0;
    int n, x, y;
    cin >> n >> x >> y;
    n--;
    int l = 0;
    int r = n * max(x, y);
    while (r - l > 1) {
        int m = (r + l) / 2;
            if (check(m, x, y, n) == 1)
                r = m;
            else l = m;
    }
    if (check (l, x, y, n) == 1)
        cout << l + min(x, y);
    else
        cout << r + min(x, y);
    return 0;
}
close