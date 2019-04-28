
 #include <bits/stdc++.h>

using namespace std;

int check (double x, double res) {
    if (x * x + pow(x, 1.0 / 2) < res)
        return 0;
    else
        return 1;
}

int main()
{
    long double c;
    cin >> c;
    double l = 0;
    double r = c;
    while (r - l > 0.0000001) {
        double m = (r + l) / 2;
            if (check(m, c) == 1)
                r = m;
            else l = m;
    }
    if (check (l, c) == 1)
        printf("%.6f", l);
    else
        printf("%.6f", r);;
    return 0;
}