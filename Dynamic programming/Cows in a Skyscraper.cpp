#include <bits\stdc++.h>

using namespace std;

int n, w, c[20];
vector<pair<int, int> > d;
int u = 0;

int main() {
    freopen("skyscraper.in", "rt", stdin);
    freopen("skyscraper.out", "wt", stdout);
    cin >> n >> w;
    for (int i = 0; i < n; i++)
        cin >> c[i];
    for (int i = 0; i < (1 << n); i++) {
        int sum = 0;
        for (int j = 0; j < n; j++)
            if (int(i & (1 << j)) != 0)
                sum += c[j];
    d.push_back(make_pair(sum, i));
    }
    sort(d.begin(), d.end());
    int k = 0;
    vector<int> ans[20];
    int cur = 0;
    for (int i = (1 << n) - 1; i >= 1; i--) {

        if (d[i].first <= w && int(cur & d[i].second) == 0) {
            cur |= d[i].second;
            for (int j = 0; j < n; j++)
                if (int(d[i].second & (1 << j)) != 0)
                    ans[k].push_back(j + 1);
            k++;
        }
    }

    cout << k << '\n';
    for (int i = 0; i < k; i++) {
        cout << ans[i].size() << " ";
        for (int j = 0; j < ans[i].size(); j++)
            cout << ans[i][j] << " ";
        cout << '\n';
    }
    return 0;
}