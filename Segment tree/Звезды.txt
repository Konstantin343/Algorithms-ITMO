#include <iostream>

using namespace std;

int n, k;
int a[256][256][256] = {};

int main(){
    ios_base::sync_with_stdio(false);
    cin >> n;
    k = 1;
    while (k < n) {
        k *= 2;
    }
    int req = 0;
    while (req != 3) {
        cin >> req;
        if (req == 1) {
            int x, y, z, p;
            cin >> x >> y >> z >> p;
            x += k - 1;
            y += k - 1;
            z += k - 1;
            int vx = x;
            int vy = y;
            int vz = z;
            while (vx != 0) {
                vy = y;
                while (vy != 0) {
                    vz = z;
                    while (vz != 0) {
                        a[vx][vy][vz] += p;
                        vz = (vz - 1) / 2;
                    }
                    a[vx][vy][vz] += p;
                    vy = (vy - 1) / 2;
                }
                vz = z;
                while (vz != 0) {
                    a[vx][vy][vz] += p;
                    vz = (vz - 1) / 2;
                }
                a[vx][vy][vz] += p;
                vx = (vx - 1) / 2;
            }
            vy = y;
            while (vy != 0) {
                vz = z;
                while (vz != 0) {
                    a[vx][vy][vz] += p;
                    vz = (vz - 1) / 2;
                }
                a[vx][vy][vz] += p;
                vy = (vy - 1) / 2;
            }
            vz = z;
            while (vz != 0) {
                a[vx][vy][vz] += p;
                vz = (vz - 1) / 2;
            }
            a[vx][vy][vz] += p;
        }
        if (req == 2) {
            int x1, x2, y1, y2, z1, z2;
            cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            x1 += k - 1;
            y1 += k - 1;
            z1 += k - 1;
            x2 += k - 1;
            y2 += k - 1;
            z2 += k - 1;
            int l1 = x1, l2 = y1, l3 = z1, r1 = x2, r2 = y2, r3 = z2;
            long long ans = 0;
            while (r1 >= l1) {
                if (l1 % 2 == 0) {
                    l2 = y1;
                    r2 = y2;
                    while (r2 >= l2) {
                        if (l2 % 2 == 0) {
                            l3 = z1;
                            r3 = z2;
                            while (r3 >= l3) {
                                if (l3 % 2 == 0) {
                                    ans += a[l1][l2][l3];
                                }
                                l3 /= 2;
                                if (r3 % 2 == 1) {
                                    ans += a[l1][l2][r3];
                                }
                                r3 /= 2;
                                r3--;
                            }
                        }
                        l2 /= 2;
                        if (r2 % 2 == 1) {
                            l3 = z1;
                            r3 = z2;
                            while (r3 >= l3) {
                                if (l3 % 2 == 0) {
                                    ans += a[l1][r2][l3];
                                }
                                l3 /= 2;
                                if (r3 % 2 == 1) {
                                    ans += a[l1][r2][r3];
                                }
                                r3 /= 2;
                                r3--;
                            }
                        }
                        r2 /= 2;
                        r2--;
                    }
                }
                l1 /= 2;
                if (r1 % 2 == 1) {
                    l2 = y1;
                    r2 = y2;
                    while (r2 >= l2) {
                        if (l2 % 2 == 0) {
                            l3 = z1;
                            r3 = z2;
                            while (r3 >= l3) {
                                if (l3 % 2 == 0) {
                                    ans += a[r1][l2][l3];
                                }
                                l3 /= 2;
                                if (r3 % 2 == 1) {
                                    ans += a[r1][l2][r3];
                                }
                                r3 /= 2;
                                r3--;
                            }
                        }
                        l2 /= 2;
                        if (r2 % 2 == 1) {
                            l3 = z1;
                            r3 = z2;
                            while (r3 >= l3) {
                                if (l3 % 2 == 0) {
                                    ans += a[r1][r2][l3];
                                }
                                l3 /= 2;
                                if (r3 % 2 == 1) {
                                    ans += a[r1][r2][r3];
                                }
                                r3 /= 2;
                                r3--;
                            }
                        }
                        r2 /= 2;
                        r2--;
                    }
                }
                r1 /= 2;
                r1--;
            }
            cout << ans << endl;

        }
    }
    return 0;
}