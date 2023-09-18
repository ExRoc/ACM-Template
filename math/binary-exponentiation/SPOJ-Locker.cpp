#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MOD = 1e9 + 7;
int T;
LL n;

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

int main() {
#ifdef ExRoc
    freopen("test.txt", "r", stdin);
#endif // ExRoc
    ios::sync_with_stdio(false);

    cin >> T;
    while (T--) {
        cin >> n;
        if (n < 3) {
            cout << n << endl;
            continue;
        }
        if (n % 3 == 0 || n % 3 == 1) {
            cout << fastPow(3, n / 3 - 1, MOD) * (n % 3 + 3) % MOD << endl;
        } else {
            cout << fastPow(3, n / 3, MOD) * 2 % MOD << endl;
        }
    }

    return 0;
}
