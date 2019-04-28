#include <iostream>

using namespace std;

int main()
{
    int a[200000], i = 0, d[101] = {};
    while(1) {
        a[i] = -1;
        cin >> a[i];
        if (a[i] == -1)
            break;
        d[a[i]]++;
    }
    for (int j = 0; j <= 100; j++)
        for (int k = 0; k < d[j]; k++)
            cout << j << " ";
    return 0;
}