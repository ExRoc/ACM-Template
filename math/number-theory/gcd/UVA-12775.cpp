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

LL solve(LL a, LL b, LL c, LL g, LL x, LL y) {
    if (c % g != 0) {
        return 0;
    }
    a /= g;
    b /= g;
    c /= g;
    x *= c;
    x = (x % b + b) % b;
    y = (c - a * x) / b;
    if (y < 0) {
        return 0;
    }
    LL l = x;
    y = (y % a + a) % a;
    x = (c - b * y) / a;
    return  (x - l) / b + 1;
}

int main() {
#ifdef ExRoc
    freopen("test.txt", "r", stdin);
#endif // ExRoc
    ios::sync_with_stdio(false);

    int T;
    LL a, b, c, p;
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        cin >> a >> b >> c >> p;
        LL x, y;
        LL g = exgcd(a, b, x, y);

        LL ans = 0;
        LL top = p / c;
        for (int i = 0; i <= top; ++i) {
            ans += solve(a, b, p - c * i, g, x, y);
        }
        cout << "Case " << cas << ": " << ans << endl;
    }

    return 0;
}
