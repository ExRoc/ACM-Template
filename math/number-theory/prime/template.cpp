inline long long multLL(long long a, long long b, long long mod) {
    unsigned long long c = (unsigned long long) a * b -
                           (unsigned long long)((long double) a / mod * b + 0.5) * mod;
    if (c < mod) {
        return c;
    }
    return c + mod;
}

long long fastPowLL(long long res, long long n, long long mod) {
    long long ans;
    for (ans = 1; n != 0; n >>= 1) {
        if ((n & 1) == 1) {
            ans = multLL(ans, res, mod);
        }
        res = multLL(res, res, mod);
    }
    return ans % mod;
}

bool isPrime(long long n) {
    if (n <= 1) {
        return false;
    }
    if (n % 2 == 0) {
        return false;
    }
    int t = __builtin_ctzll(n - 1);
    long long d = (n - 1) >> t;
    static vector<long long> baseInt = {2, 7, 61};
    static vector<long long> baseLL = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    vector<long long> *base;
    if (n <= INT_MAX) {
        base = &baseInt;
    } else {
        base = &baseLL;
    }
    for (long long a : *base) {
        if (n == a) {
            return true;
        }
        long long t = d;
        long long y = fastPowLL(a, t, n);
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