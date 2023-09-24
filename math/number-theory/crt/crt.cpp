class CRT {
private:
    static void swap(long long &a, long long &b) {
        a ^= b ^= a ^= b;
    }

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

public:
    static long long solve(long long *r, long long *m, int n, long long &lcm) {
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
};
