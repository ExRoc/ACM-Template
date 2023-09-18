#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
int T;
LL n;

int main() {
#ifdef ExRoc
    freopen("test.txt", "r", stdin);
#endif // ExRoc
    ios::sync_with_stdio(false);

    cin >> T;
    while (T--) {
        LL ans = 0;
        LL l = 1;
        LL r;
        cin >> n;
        while (l <= n) {
            r = n / (n / l);
            ans += (r - l + 1) * (n / l);
            l = r + 1;
        }
        cout << ans << endl;
    }

    return 0;
}
