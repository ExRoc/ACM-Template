// https://www.spoj.com/problems/ZSUM/
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

typedef long long LL;
const int MOD = 1e7 + 7;
int n, k;

int fp(int a, int b) {
    return fastPow(a, b, MOD);
}

int main() {
#ifdef ExRoc
    freopen("test.txt", "r", stdin);
#endif // ExRoc
    ios::sync_with_stdio(false);

    while (cin >> n >> k, n != 0 || k != 0) {
        cout << (fp(n, k) + 2 * fp(n - 1, k) + fp(n, n) + 2 * fp(n - 1, n - 1)) % MOD << endl;
    }

    return 0;
}
