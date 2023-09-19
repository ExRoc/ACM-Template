#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = 300 + 100;
int n;
int l[maxn];
LL c[maxn];
unordered_map<int, LL> dp[maxn];
unordered_map<int, LL>::iterator it;

int main() {
#ifdef ExRoc
    freopen("test.txt", "r", stdin);
#endif // ExRoc
    ios::sync_with_stdio(false);

    cin >> n;
    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> l[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> c[i];
        dp[i] = dp[i - 1];
        for (it = dp[i - 1].begin(); it != dp[i - 1].end(); ++it) {
            LL g = __gcd(it->first, l[i]);
            if (dp[i].find(g) == dp[i].end()) {
                dp[i][g] = it->second + c[i];
            } else {
                dp[i][g] = min(dp[i][g], it->second + c[i]);
            }
        }
    }
    if (dp[n].find(1) == dp[n].end()) {
        cout << -1 << endl;
        return 0;
    }
    cout << dp[n][1] << endl;

    return 0;
}
