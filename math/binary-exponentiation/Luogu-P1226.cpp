// https://www.luogu.com.cn/problem/P1226
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

int main() {
#ifdef ExRoc
    freopen("test.txt", "r", stdin);
#endif // ExRoc
    ios::sync_with_stdio(false);

    int a, b, p;
    cin >> a >> b >> p;
    printf("%d^%d mod %d=%d", a, b, p, fastPow(a, b, p));

    return 0;
}