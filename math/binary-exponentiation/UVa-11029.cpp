#include <bits/stdc++.h>
using namespace std;

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

    int T, n, k;
    cin >> T;
    while (T--) {
        cin >> n >> k;
        int low = fastPow(n, k, 1000);
        int high = pow(10, 2 + fmod(k * log10(n), 1));
        printf("%d...%03d\n", high, low);
    }

    return 0;
}
