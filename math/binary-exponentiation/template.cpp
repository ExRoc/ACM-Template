long long fastPow(long long res, long long n, long long mod) {
	long long ans;
	for (ans = 1; n != 0; n >>= 1) {
		if ((n & 1) == 1) {
			ans = ans * res % mod;
		}
		res = res * res % mod;
	}
	return ans % mod;
}

template<long long a, long long mod = (long long)(1e9 + 7), int MAX_SIZE = 65536>
class PreprocessingPow {
private:
    int powLow[MAX_SIZE];
    int powHigh[MAX_SIZE];

    long long (PreprocessingPow::*calculate)(int);

    long long calculateByBits(int n) {
        static int dig = __builtin_ctz(MAX_SIZE);
        static int mask = MAX_SIZE - 1;
        return 1LL * powLow[n & mask] * powHigh[n >> dig] % mod;
    }

    long long calculateByBase(int n) {
        return 1LL * powLow[n % MAX_SIZE] * powHigh[n / MAX_SIZE] % mod;
    }

public:
    PreprocessingPow() {
        powLow[0] = powHigh[0] = 1;
        for (int i = 1; i < MAX_SIZE; ++i) {
            powLow[i] = powLow[i - 1] * a % mod;
        }
        long long powHighBase = powLow[MAX_SIZE - 1] * a % mod;
        for (int i = 1; i < MAX_SIZE; ++i) {
            powHigh[i] = powHigh[i - 1] * powHighBase % mod;
        }

        if (__builtin_popcount(MAX_SIZE) == 1) {
            calculate = calculateByBits;
        } else {
            calculate = calculateByBase;
        }
    }

    long long pow(int n) {
        return (this->*calculate)(n);
    }
};

long long mult(long long a, long long b, long long mod) {
    unsigned long long c = (unsigned long long) a * b -
                           (unsigned long long)((long double) a / mod * b + 0.5) * mod;
    if (c < mod) {
        return c;
    }
    return c + mod;
}