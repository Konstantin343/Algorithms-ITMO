#include <bits/stdc++.h>

using namespace std;

int a[300000], mi[300000], ma[300000], co[300000];
int n;

void un(int e1, int e2) {
    while(e1 != a[e1])
        e1 = a[e1];
    while(e2 != a[e2])
        e2 = a[e2];
    if (co[e2] < co[e1])
        swap(e1, e2);
    if (e1 != e2)
        co[e2] += co[e1];
    ma[e2] = max(ma[e1], ma[e2]);
    mi[e2] = min(mi[e1], mi[e2]);
    a[e1] = e2;
}

int get(int e) {
    if(a[e] != e)
        e = get(a[e]);
    return e;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++) {
        a[i] = i;
        mi[i] = i;
        ma[i] = i;
        co[i] = 1;
    }
    vector< vector<int> > ans;
    string s;
    while(cin >> s) {
        if (s[0] == 'u') {
            int e1, e2;
            cin >> e1 >> e2;
            un(e1, e2);
        }
        if (s[0] == 'g') {
            int e;
            cin >> e;
            cout << mi[get(e)] << " " << ma[get(e)] << " " << co[get(e)] << endl;
        }
    }

    return 0;
}