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

template<int MAXN = 1, long long MOD = 1>
class Inverse {
private:
    int n;
    long long mod;
    int inv[MAXN + 1];

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

    long long getInvByExgcd(long long n, long long mod) {
        long long x, y;
        exgcd(n, mod, x, y);
        return x;
    }

public:
    Inverse() {
        n = 1;
        mod = MOD;
        inv[1] = 1;
    }

    void resetN(int n) {
        getInvByCache(n);
    }

    void resetMod(long long mod) {
        this->mod = mod;
        n = 1;
    }

    long long getInv(long long n) {
        if (n <= MAXN) {
            return getInvByCache(n);
        }
        return getInvByExgcd(n, mod);
    }

    long long getInv(long long n, long long mod) {
        if (mod == this->mod) {
            return getInv(n);
        }
        return getInvByExgcd(n, mod);
    }
};