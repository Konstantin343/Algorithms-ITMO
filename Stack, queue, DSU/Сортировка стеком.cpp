#include <bits/stdc++.h>

using namespace std;

int main()
{
    stack<int> s;
    vector<string> ans;
    int used[1000001] = {};
    int n;
    int cur = 1;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        s.push(a);
        used[a] = 1;
        ans.push_back("push");
        if (s.size() > 0 && s.top() == cur) {
            while(s.size() > 0 && s.top() == cur) {
                s.pop();
                ans.push_back("pop");
                cur++;

            }
            if (used[cur] == 1) {
                cout << "impossible";
                return 0;
            }
        }
    }
    for (int i = 0; i < ans.size(); i++)
        cout << ans[i] << endl;
    return 0;
}