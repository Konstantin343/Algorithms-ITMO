#include <iostream>

using namespace std;

int a[100000];

void merge (int left, int middle, int right) {
    int res[100000];
    if(a[middle] > a[middle + 1] && (right-left) % 2==1)
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
        mergeSort(b, (b + e)/2);
        mergeSort((b + e)/2 , e);
        merge(b,(b+e)/2,e);

    }

}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    mergeSort(0, n);
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    return 0;
}