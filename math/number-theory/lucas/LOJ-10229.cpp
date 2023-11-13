// https://loj.ac/p/10229
#include <bits/stdc++.h>
using namespace std;

long long fastPow(long long res, long long n, long long mod) {
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

class ExLucas {
private:
    static void swap(long long& a, long long& b) {
        a ^= b ^= a ^= b;
    }

    static long long exgcd(long long a, long long b, long long& x, long long& y) {
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

    static long long inv(long long n, long long mod) {
        long long x, y;
        exgcd(n, mod, x, y);
        return (x % mod + mod) % mod;
    }

    static long long calc(long long n, long long x, long long mod) {
        if (n == 0) {
            return 1;
        }
        long long s = 1;
        for (long long i = 1; i <= mod; ++i) {
            if (i % x != 0) {
                s = s * i % mod;
            }
        }
        s = fastPow(s, n / mod, mod);
        for (long long i = n / mod * mod + 1; i <= n; i++) {
            if (i % x != 0) {
                s = i % mod * s % mod;
            }
        }
        return s * calc(n / x, x, mod) % mod;
    }

    static long long crt(long long* r, long long* m, int n, long long& lcm) {
        long long r0 = 0, m0 = 1;
        for (int i = 0; i < n; i++) {
            long long r1 = (r[i] % m[i] + m[i]) % m[i];
            long long m1 = m[i];
            if (m0 < m1) {
                swap(r0, r1);
                swap(m0, m1);
            }
            if (m0 % m1 == 0) {
                if (r0 % m1 != r1) {
                    lcm = 0;
                    return 0;
                }
                continue;
            }
            long long im, tmp;
            long long g = exgcd(m0, m1, im, tmp);
            long long u1 = (m1 / g);
            if ((r1 - r0) % g) {
                lcm = 0;
                return 0;
            }
            long long x = (r1 - r0) / g % u1 * im % u1;
            r0 += x * m0;
            m0 *= u1;
            if (r0 < 0) {
                r0 += m0;
            }
        }
        lcm = m0;
        return r0;
    }

    static long long multilucas(long long n, long long m, long long x, long long mod) {
        int cnt = 0;
        for (long long i = n; i != 0; i /= x) {
            cnt += i / x;
        }
        for (long long i = m; i != 0; i /= x) {
            cnt -= i / x;
        }
        for (long long i = n - m; i != 0; i /= x) {
            cnt -= i / x;
        }
        return fastPow(x, cnt, mod) % mod * calc(n, x, mod) % mod *
               inv(calc(m, x, mod), mod) % mod * inv(calc(n - m, x, mod), mod) % mod;
    }

public:
    static long long solve(long long n, long long m, long long mod) {
        int cnt = 0;
        static long long p[20], a[20];
        for (long long i = 2; i * i <= mod; i++) {
            if (mod % i == 0) {
                p[cnt] = 1;
                while (mod % i == 0) {
                    p[cnt] = p[cnt] * i;
                    mod /= i;
                }
                a[cnt] = multilucas(n, m, i, p[cnt]);
                ++cnt;
            }
        }
        if (mod > 1) {
            p[cnt] = mod;
            a[cnt] = multilucas(n, m, mod, mod);
            ++cnt;
        }
        long long lcm = 0;
        return crt(a, p, cnt, lcm);
    }
};

typedef long long LL;
const LL MOD = 999911659;
LL N, G;

int main() {
#ifdef ExRoc
    freopen("test.txt", "r", stdin);
#endif // ExRoc
    ios::sync_with_stdio(false);

    cin >> N >> G;
    LL ans = 0;
    for (LL i = 1; i * i <= N; ++i) {
        if (N % i == 0) {
            ans += ExLucas::solve(N, i, MOD - 1);
            ans %= (MOD - 1);
            if (N / i != i) {
                ans += ExLucas::solve(N, N / i, MOD - 1);
                ans %= (MOD - 1);
            }
        }
    }
    ans += (MOD - 1);
    ans = fastPow(G, ans, MOD);
    cout << ans << endl;

    return 0;
}
