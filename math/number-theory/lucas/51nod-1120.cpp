// https://www.51nod.com/Challenge/Problem.html#problemId=1120
#include <bits/stdc++.h>
using namespace std;

template<long long MOD>
class Lucas {
private:
    int fac[MOD], invFac[MOD];

    static long long exgcd(long long a, long long b, long long &x, long long &y) {
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

    static long long inv(long long n) {
        long long x, y;
        exgcd(n, MOD, x, y);
        return (x % MOD + MOD) % MOD;
    }

    long long C(long long n, long long m) {
        if (n < m) {
            return 0;
        }
        return fac[n] * invFac[m] % MOD * invFac[n - m] % MOD;
    }

public:
    Lucas() {
        fac[0] = 1;
        for (int i = 1; i < MOD; ++i) {
            fac[i] = (1LL * fac[i - 1] * i) % MOD;
        }
        invFac[MOD - 1] = inv(fac[MOD - 1]);
        for (int i = MOD - 2; i >= 0; --i) {
            invFac[i] = (1LL * invFac[i + 1] * (i + 1)) % MOD;
        }
    }

    long long solve(long long n, long long m) {
        if (m == 0) {
            return 1;
        }
        return C(n % MOD, m % MOD) * solve(n / MOD, m / MOD) % MOD;
    }
};

typedef long long LL;
const int MOD = 10007;
Lucas<MOD> l;
int n;
LL ans;

int main() {
#ifdef ExRoc
    freopen("test.txt", "r", stdin);
#endif // ExRoc
    ios::sync_with_stdio(false);

    cin >> n;
    --n;
    cout << (l.solve(2 * n, n) - l.solve(2 * n, n - 1) + MOD) % MOD * 2 % MOD << endl;

    return 0;
}
