#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MOD = 1e7 + 7;
int n, k;

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
