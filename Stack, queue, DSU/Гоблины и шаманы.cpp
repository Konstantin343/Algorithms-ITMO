#include <bits/stdc++.h>

using namespace std;

int main()
{
    list<int> left, right;
    int t, n = 0;
    cin >> t;
    for (int i = 0; i < t; i++) {
        char c;
        scanf("\n%c", &c);
        if (c == '+') {
            int r;
            scanf("%d", &r);
            right.push_back(r);
            if (right.size() != left.size()) {
                left.push_back(right.front());
                right.pop_front();
            }
        }
        if (c == '*') {
            int r;
            scanf("%d", &r);
            if (right.size() == left.size()) {
                left.push_back(r);
            } else {
                right.push_front(r);
            }
        }
        if (c == '-') {
            printf("%d\n", left.front());
            left.pop_front();
            if (right.size() != left.size()) {
                left.push_back(right.front());
                right.pop_front();
            }
        }
    }
    return 0;
}