#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 9223372036854775807

using namespace std;

struct node{
    int value;
    int add;
    int y;
};

struct line{
    vector<pair<int, int> > open;
    vector<pair<int, int> > close;
};

line field[400006];
int n;
node tree[2 << 20];

void push(int v) {
    tree[2 * v + 1].add += tree[v].add;
    tree[2 * v + 2].add += tree[v].add;
    tree[v].add = 0;
}

void update(int v, int x, int tl, int tr, int l, int r) {
    if (l > tr || r < tl) {
        return;
    }
    if (l >= tl && r <= tr) {
        tree[v].add += x;
        return;
    }
    if (v < (2 << 18) - 1) {
        push(v);
        update(2 * v + 1, x, tl, tr, l, (l + r) / 2);
        update(2 * v + 2, x, tl, tr, (l + r) / 2 + 1, r);
        if (tree[2 * v + 1].value + tree[2 * v + 1].add > tree[2 * v + 2].value + tree[2 * v + 2].add) {
            tree[v].value = tree[2 * v + 1].value + tree[2 * v + 1].add;
            tree[v].y = tree[2 * v + 1].y;
        } else {
            tree[v].value = tree[2 * v + 2].value + tree[2 * v + 2].add;
            tree[v].y = tree[2 * v + 2].y;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin >> n;
    for (int i = (2 << 18) - 1; i < (2 << 19) - 1; i++) {
        tree[i].y = i - (2 << 18) + 2;
    }
    for (int i = (2 << 18) - 2; i >= 0; i--) {
        tree[i].y = tree[2 * i + 1].y;
    }
    for (int i = 0; i < n; i++) {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1 += 200001;
        x2 += 200001;
        y1 += 200001;
        y2 += 200001;
        field[x1].open.push_back(make_pair(y1, y2));
        field[x2 + 1].close.push_back(make_pair(y1, y2));
    }
    int ans = 0;
    int x = 0, y = 0;
    for (int i = 1; i <= 400005; i++) {
        for (int j = 0; j < field[i].open.size(); j++) {
            update(0, 1, field[i].open[j].first, field[i].open[j].second, 1, (2 << 18));
        }
        for (int j = 0; j < field[i].close.size(); j++) {
            update(0, -1, field[i].close[j].first, field[i].close[j].second, 1, (2 << 18));
        }
        /*+for (int k = 0; k < 15; k++) {
            cout << tree[k].value << " " << tree[k].add << " " << tree[k].x << " " << tree[k].y << endl;
        }
        cout << "-----------" << endl;*/
        if (tree[0].value + tree[0].add > ans) {
            ans = tree[0].value + tree[0].add;
            x = i - 200001;
            y = tree[0].y - 200001;
        }
    }
    cout << ans << '\n' << x << " " << y;
    return 0;
}