#include <bits/stdc++.h>

using namespace std;

double f (double m, int v1, int v2, double brd) {
    return (sqrt(m * m + (1 - brd) * (1 - brd)) / v1 + sqrt((1 - m) * (1 - m) + brd * brd) / v2);
}

int main()
{
    int v1, v2;
    double a;
    cin >> v1 >> v2;
    cin >> a;
    double l = 0;
    double r = 1;
    while (r - l > 0.00001) {
        double m1 = (2 * l + r) / 3;
        double m2 = (2 * r + l) / 3;
        if (f(m1, v1, v2, a) > f(m2, v1, v2, a))
            l = m1;
        else r = m2;


    }
    printf("%.4f", (l + r) / 2);
    return 0;
}