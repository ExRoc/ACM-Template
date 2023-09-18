#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long gcd = exgcd(b, a % b, x, y);
    long long t = x;
    x = y;
    y = t - (a / b) * y;
    return gcd;
}

int main() {
#ifdef ExRoc
    freopen("test.txt", "r", stdin);
#endif // ExRoc
    ios::sync_with_stdio(false);

    LL a, b, x, y;
    while (cin >> a >> b) {
        LL g = exgcd(a, b, x, y);
        LL minX = (x % b + b) % b;
        LL maxY = (g - a * minX) / b;
        LL minY = (y % a + a) % a;
        LL maxX = (g - b * minY) / a;
        if (abs(minX) + abs(maxY) <= abs(maxX) + abs(minY)) {
            cout << minX << " " << maxY << " " << g << endl;
        } else {
            cout << maxX << " " << minY << " " << g << endl;
        }
    }

    return 0;
}
