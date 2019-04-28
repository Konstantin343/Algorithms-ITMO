#include <bits/stdc++.h>

using namespace std;

int a[1000001];
int n = 0;
int m[1000001];

void push(int e) {
    a[n] = e;
    if (n > 0)
        m[n] = min(e, m[n - 1]);
    else m[n] = e;
    n++;
}

void del() {
    n--;
}

int mine() {
 return m[n - 1];
}

int main()
{
    int t;
    cin >> t;
    vector<int> ans;
    for (int i = 0; i < t; i++) {
        int p;
        scanf("%d", &p);
        if (p == 1) {
            int o;
            scanf("%d", &o);
            push(o);
        }
        if (p == 2) del();
        if (p == 3) ans.push_back(mine());
    }
    for (int i = 0;i < ans.size(); i++)
        cout<<ans[i]<<endl;
    return 0;
}