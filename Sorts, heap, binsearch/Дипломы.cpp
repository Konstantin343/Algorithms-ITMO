#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int check (long long x, long long a, long long b, int cnt) {
    if ((x / a) * (x / b) < cnt)
        return 0;
    else
        return 1;
}

int main()
{
    long long n, w, h;
    cin >> w >> h >> n;
    long long l = 0;
    long long r = n * max(w, h);
    while (r - l > 1) {
        long long m = (r + l) / 2;
            if (check(m, w, h, n) == 1)
                r = m;
            else l = m;
    }
    if (check (l, w, h, n) == 1)
        cout << l;
    else
        cout << r;
    return 0;
}