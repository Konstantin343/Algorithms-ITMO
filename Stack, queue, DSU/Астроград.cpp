#include <bits/stdc++.h>

using namespace std;

int a[1000001];
int b = 0;
int e = 0;

int main()
{
    int t;
    cin >> t;
    vector<int> ans;
    for (int i = 0; i < t; i++) {
        int c;
        cin >> c;
        if (c == 1) {
            int man;
            cin >> man;
            a[e] = man;
            e++;
        }
        if (c == 2)
            b++;
        if (c == 3)
            e--;
        if (c == 4) {
            int num;
            cin >> num;
            for (int j = b; j <= e; j++)
                if (a[j] == num) {
                    ans.push_back(j - b);
                    break;
                }
        }
        if (c == 5)
            ans.push_back(a[b]);
    }
    for (int i = 0; i < ans.size(); i++)
        cout<<ans[i] <<endl;
    return 0;
}