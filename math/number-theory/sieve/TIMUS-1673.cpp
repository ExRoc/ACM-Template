// https://acm.timus.ru/problem.aspx?space=1&num=1673
#include <bits/stdc++.h>
using namespace std;

class Prime {
private:
	static long long fastPow(long long res, long long n, long long mod) {
		long long ans = 1;
        while (n != 0) {
            if ((n & 1) == 1) {
				ans = ans * res % mod;
            }
			res = res * res % mod;
            n >>= 1;
        }
		return ans % mod;
	}

	static long long multLL(long long a, long long b, long long mod) {
		unsigned long long c = (unsigned long long) a * b -
							(unsigned long long)((long double) a / mod * b + 0.5) * mod;
		if (c < mod) {
			return c;
		}
		return c + mod;
	}

	static long long fastPowLL(long long res, long long n, long long mod) {
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

public:
    static bool isPrime(int n) {
        if (n <= 1) {
            return false;
        }
        if (n > 2 && n % 2 == 0) {
            return false;
        }
        int d = (n - 1) >> __builtin_ctz(n - 1);
        static int base[] = {2, 7, 61};
        for (int i = 0; i < 3; ++i) {
            if (n == base[i]) {
                return true;
            }
            int t = d;
            long long y = fastPow(base[i], t, n);
            while (t != n - 1 && y != 1 && y != n - 1) {
                y = y * y % n;
                t <<= 1;
            }
            if (y != n - 1 && t % 2 == 0) {
                return false;
            }
        }
        return true;
    }

    static bool isPrimeLL(long long n) {
        if (n < (1LL << 31)) {
            return isPrime(n);
        }
        if (n % 2 == 0) {
            return false;
        }
        long long d = (n - 1) >> __builtin_ctzll(n - 1);
        static long long base[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
        for (int i = 0; i < 7; ++i) {
            if (n == base[i]) {
                return true;
            }
            long long t = d;
            long long y = fastPowLL(base[i], t, n);
            while (t != n - 1 && y != 1 && y != n - 1) {
                y = multLL(y, y, n);
                t <<= 1;
            }
            if (y != n - 1 && t % 2 == 0) {
                return false;
            }
        }
        return true;
    }
};

typedef long long LL;
const int maxn = 200000 + 100;
const LL INF = (1LL << 63) - 1;
LL ans, k;
int cnt, cntTmp;
LL fac[maxn], facTmp[maxn];

void dfs2(int depth, LL k, LL tmp) {
    if (depth == cntTmp) {
        if (k == 1) {
            ans = min(ans, tmp);
        }
        return;
    }
    dfs2(depth + 1, k, tmp);
    while (k % facTmp[depth] == 0) {
        k /= facTmp[depth];
        tmp *= facTmp[depth];
        dfs2(depth + 1, k, tmp);
    }
}

void dfs(int depth, LL k, LL tmp) {
    if (depth == cnt) {
        if (k == 1) {
            ans = min(ans, tmp);
        } else {
            dfs2(0, k, tmp);
        }
        return ;
    }
    dfs(depth + 1, k, tmp);
    if (k % fac[depth] == 0) {
        facTmp[cntTmp++] = fac[depth] + 1;
        dfs(depth + 1, k / fac[depth], tmp * (fac[depth] + 1));
        --cntTmp;
    }
}

int main() {
#ifdef ExRoc
    freopen("test.txt", "r", stdin);
#endif // ExRoc
    ios::sync_with_stdio(false);

    cin >> k;
    for (LL i = 1; i * i <= k; ++i) {
        if (k % i == 0) {
            if (Prime::isPrime(i + 1)) {
                fac[cnt++] = i;
            }
            if (k / i != i) {
                if (Prime::isPrime(k / i + 1)) {
                    fac[cnt++] = k / i;
                }
            }
        }
    }
    ans = INF;
    dfs(0, k, 1);
    if (ans == INF) {
        cout << 0 << endl;
        return 0;
    }
    cout << ans << endl;

    return 0;
}