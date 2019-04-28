#include <bits/stdc++.h>

using namespace std;

int a[300000], ex[300000] = {}, co[300000];
int n;

int get(int e) {
    int sum = 0;
    while (e != a[e]) {
        sum += ex[e];
        e = a[e];
    }
    return sum + ex[e];
}

void add(int e, int xp) {
    while (e != a[e])
        e = a[e];
    ex[e] += xp;
}

void join(int e1, int e2) {
    while (e1 != a[e1])
        e1 = a[e1];
    while (e2 != a[e2])
        e2 = a[e2];
    if (co[e2] < co[e1])
        swap(e1, e2);
    if(e1 != e2) {
    ex[e1] -= ex[e2];
    a[e1] = e2;
    co[e2] = max(co[e1] + 1, co[e2]);
    co[e1] = 0;
    }
}

int main()
{
    int m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        a[i] = i;
        co[i] = 1;
    }
    char s[100];
    for (int j = 0; j < m; j++) {
        scanf("%s", s);
        if (s[0] == 'j') {
            int e1, e2;
            scanf("%d %d", &e1, &e2);
            join(e1, e2);
        }
        if (s[0] == 'g') {
            int e;
            scanf("%d", &e);
            printf("%d\n", get(e));
        }
        if (s[0] == 'a') {
            int e, xp;
            scanf("%d %d", &e, &xp);
            add(e, xp);
        }
    }
    return 0;
}