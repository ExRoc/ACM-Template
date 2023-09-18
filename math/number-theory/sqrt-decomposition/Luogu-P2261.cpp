#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
LL n, k;

int main() {
#ifdef ExRoc
    freopen("test.txt", "r", stdin);
#endif // ExRoc
    ios::sync_with_stdio(false);

    cin >> n >> k;
    LL ans = n * k;
    LL l = 1;
    LL r;
    LL mn = min(n, k);
    while (l <= mn) {
        r = min(k / (k / l), n);
        ans -= k / l * (l + r) * (r - l + 1) / 2;
        l = r + 1;
    }
    cout << ans << endl;

    return 0;
}