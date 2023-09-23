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
