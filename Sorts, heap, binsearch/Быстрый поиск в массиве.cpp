#include <iostream>
#include <vector>

using namespace std;

int a[100000];

void merge (int left, int middle, int right) {
    int res[100000];
    if(a[middle] > a[middle + 1] && (right-left) % 2 == 1)
        middle++;
    int i = left, j = middle;
    while (i < middle || j < right) {
        if (a[i] < a[j] && i != middle || j == right) {
            res[i + j - middle] = a[i];
            i++;
        } else {
            res[i + j - middle] = a[j];
            j++;
        }
    }
    for (int t = left; t < right; t++)
        a[t] = res [t];
}

void mergeSort (int b, int e) {
    if (e - b < 2) {
         return;
    } else {
        mergeSort(b, (b + e) / 2);
        mergeSort((b + e) / 2, e);
        merge(b, (b + e) / 2, e);
    }
}

int upBinSearch (int l, int r, int x) {
    if (r - l < 1)
        return r;
    else if (r - l == 1) {
        if (a[r] == x)
            return r;
        else
            return l;
    } else {
        int m = (l + r) / 2;
        if (x < a[m])
            upBinSearch(l, m, x);
        else
            upBinSearch(m, r, x);
    }
}

int lowBinSearch (int l, int r, int x) {
    if (r - l < 1)
        return r;
    else if (r - l == 1) {
        if (a[l] == x)
            return l;
        else
            return r;
    } else {
        int m = (l + r) / 2;
        if (x <= a[m])
            lowBinSearch(l, m, x);
        else
            lowBinSearch(m, r, x);
    }
}


int main()
{
    vector <int> ans;
    int n, m;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cin >> m;
    mergeSort(0, n);
    for (int i = 0; i < m; i ++) {
        int q, e;
        cin >> q >> e;
        int l = lowBinSearch(0, n - 1, q);
        int r = upBinSearch(0, n - 1, e);
        if (q < a[0])
            l = 0;
        if (e > a[n - 1])
            r = n - 1;
        if (q > a[n - 1] || e < a[0])
            ans.push_back(0);
        else
            ans.push_back(r - l + 1);
    }
    for (int i = 0; i < m; i++)
        cout << ans[i] << " ";
    return 0;
}
close