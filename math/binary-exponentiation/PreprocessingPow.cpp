template<long long BASE, long long MOD, int MAX_SIZE = 65536>
class PreprocessingPow {
private:
    int powLow[MAX_SIZE];
    int powHigh[MAX_SIZE];

    long long (PreprocessingPow::*calculate)(int);

    long long calculateByBits(int n) {
        static int dig = __builtin_ctz(MAX_SIZE);
        static int mask = MAX_SIZE - 1;
        return (long long) powLow[n & mask] * powHigh[n >> dig] % MOD;
    }

    long long calculateByBase(int n) {
        return (long long) powLow[n % MAX_SIZE] * powHigh[n / MAX_SIZE] % MOD;
    }

public:
    PreprocessingPow() {
        powLow[0] = powHigh[0] = 1;
        for (int i = 1; i < MAX_SIZE; ++i) {
            powLow[i] = powLow[i - 1] * BASE % MOD;
        }
        long long powHighBase = powLow[MAX_SIZE - 1] * BASE % MOD;
        for (int i = 1; i < MAX_SIZE; ++i) {
            powHigh[i] = powHigh[i - 1] * powHighBase % MOD;
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
