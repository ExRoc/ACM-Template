// https://www.luogu.com.cn/problem/P2054
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

long long multLL(long long a, long long b, long long mod) {
	unsigned long long c = (unsigned long long) a * b -
						(unsigned long long)((long double) a / mod * b + 0.5) * mod;
	if (c < mod) {
		return c;
	}
	return c + mod;
}

long long fastPowLL(long long res, long long n, long long mod) {
	long long ans = 1;
	while (n != 0) {
		if ((n & 1) == 1) {
			ans = multLL(ans, res, mod);
		}
		res = multLL(res, res, mod);
		n >>= 1;
	}
	return ans % mod;
}

typedef long long LL;
LL n, m, l;
Inverse<> inverse;

int main() {
#ifdef ExRoc
    freopen("test.txt", "r", stdin);
#endif // ExRoc
    ios::sync_with_stdio(false);

    cin >> n >> m >> l;
    inverse.resetMod(n + 1);
    LL two = inverse.getInv(2);
    two = fastPowLL(two, m, n + 1);
    LL ans = multLL(l, two, n + 1);
    cout << ans << endl;

    return 0;
}
