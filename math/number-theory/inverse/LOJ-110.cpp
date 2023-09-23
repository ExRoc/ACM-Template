// https://loj.ac/p/110
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

const int maxn = 3000000 + 100;
int n, p;
Inverse<maxn> inverse;

int main() {
#ifdef ExRoc
    freopen("test.txt", "r", stdin);
#endif // ExRoc
    ios::sync_with_stdio(false);

    cin >> n >> p;
    inverse.resetMod(p);
    for (int i = 1; i <= n; ++i) {
        cout << inverse.getInv(i) << endl;
    }

    return 0;
}
