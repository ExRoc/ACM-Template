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
