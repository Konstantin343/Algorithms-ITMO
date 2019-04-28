#include <iostream>
#include <vector>

using namespace std;

int a[100001] = {};

void add (int x, int m) {
    a[m] = x;
    int i = m;
    while (i > 0 && a[(i - 1) / 2] < a[i]) {
        swap(a[i], a[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int remove_max(int m) {
    int res = a[0];
    swap(a[0], a[m - 1]);
    a[m - 1] = 0;
    m--;
    int i = 0;
    while (2 * i + 1 < m) {
        int r = 2 * i + 1;
        if(2 * i + 2 < m && a[2 * i + 2] > a[2 * i + 1])
            r = 2 * i + 2;
        if (a[r] > a[i]) {
            swap(a[i], a[r]);
            i = r;
        } else break;
    }
    return res;
}

int main() {
    vector <int> ans;
    int j = 0;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int com, dig;
        cin >> com;
        if (com == 0) {
            cin >> dig;
            add(dig, j);
            j++;
        } else {
           ans.push_back(remove_max(j));
           j--;
        }
    }
    for (int i = 0; i < ans.size(); i++)
        cout << ans[i] << endl;
    return 0;
}
close