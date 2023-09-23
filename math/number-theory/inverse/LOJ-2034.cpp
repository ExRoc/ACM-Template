// https://loj.ac/p/2034
#include <bits/stdc++.h>
using namespace std;

template<int MAXN = 1, long long MOD = 1>
class Inverse {
private:
    int n;
    long long mod;
    int inv[MAXN + 1];

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

    int getInvByCache(int n) {
        if (n <= this->n) {
            return inv[n];
        }
        for (int i = this->n + 1; i <= n; ++i) {
            inv[i] = (mod - mod / i) * inv[mod % i] % mod;
        }
        this->n = n;
        return inv[n];
    }

public:
    Inverse() {
        n = 1;
        mod = MOD;
        inv[1] = 1;
    }

    Inverse(int n) {
        Inverse();
        preprocessFirst(n);
    }

    void preprocessFirst(int n) {
        for (int i = this->n + 1; i <= n; ++i) {
            inv[i] = (mod - mod / i) * inv[mod % i] % mod;
        }
        this->n = n;
    }

    void resetMod(long long mod) {
        this->mod = mod;
        n = 1;
    }

    long long getInv(long long n) {
        if (n <= MAXN) {
            if (n > this->n) {
                preprocessFirst(n);
            }
            return inv[n];
        }
        return any(n, mod);
    }

    static long long any(long long n, long long mod) {
        long long x, y;
        exgcd(n, mod, x, y);
        return (x % mod + mod) % mod;
    }
};

typedef long long LL;
const LL MOD = 1e9 + 7;
const int maxn = 1000000 + 100;
int T, n, m;
Inverse<maxn, MOD> inverse;
LL pro[maxn], invpro[maxn], d[maxn];

int main() {
#ifdef ExRoc
    freopen("test.txt", "r", stdin);
#endif // ExRoc
    ios::sync_with_stdio(false);

    d[0] = 1;
    d[1] = 0;
    pro[0] = 1;
    pro[1] = 1;
    invpro[0] = 1;
    invpro[1] = 1;
    for (int i = 2; i < maxn; ++i) {
        d[i] = (i - 1) * (d[i - 1] + d[i - 2]) % MOD;
        pro[i] = pro[i - 1] * i % MOD;
        invpro[i] = invpro[i - 1] * inverse.getInv(i) % MOD;
    }
    cin >> T;
    while (T--) {
        cin >> n >> m;
        if (m > n) {
            cout << 0 << endl;
            continue;
        }
        LL ans = pro[n] * invpro[m] % MOD * invpro[n - m] % MOD * d[n - m] % MOD;
        cout << ans << endl;
    }

    return 0;
}
