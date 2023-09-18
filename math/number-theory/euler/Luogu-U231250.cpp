#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

long long getEuler(long long n) {
    long long ans = n;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            ans = ans / i * (i - 1);
            while (n % i == 0) {
                n /= i;
            }
        }
    }
    if (n > 1) {
        ans = ans / n * (n - 1);
    }
    return ans;
}

int main() {
#ifdef ExRoc
    freopen("test.txt", "r", stdin);
#endif // ExRoc
    ios::sync_with_stdio(false);

    LL n;
    cin >> n;
    cout << getEuler(n) << endl;

    return 0;
}
