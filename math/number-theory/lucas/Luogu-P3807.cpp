// https://www.luogu.com.cn/problem/P3807
#include <bits/stdc++.h>
using namespace std;

const int maxn = 200000 + 100;
long long MOD;

long long fac[maxn], invFac[maxn];

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

long long inv(long long n) {
    long long x, y;
    exgcd(n, MOD, x, y);
    return (x % MOD + MOD) % MOD;
}

long long C(int n, int m) {
    if (n < m) {
        return 0;
    }
    fac[0] = 1;
    for (int i = 1; i <= n; ++i) {
        fac[i] = (1LL * fac[i - 1] * i) % MOD;
    }
    invFac[n] = inv(fac[n]);
    for (int i = n - 1; i >= 0; --i) {
        invFac[i] = (1LL * invFac[i + 1] * (i + 1)) % MOD;
    }
    return fac[n] * invFac[m] % MOD * invFac[n - m] % MOD;
}

long long lucas(long long n, long long m) {
    if (m == 0) {
        return 1;
    }
    return C(n % MOD, m % MOD) * lucas(n / MOD, m / MOD) % MOD;
}

int T, n, m;

int main() {
    #ifdef ExRoc
    freopen("test.txt", "r", stdin);
    #endif // ExRoc
    ios::sync_with_stdio(false);

    cin >> T;
    while (T--) {
        cin >> n >> m >> MOD;
        cout << lucas(n + m, m) << endl;
    }
    

    return 0;
}
