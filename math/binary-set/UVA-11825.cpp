// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2925
#include <bits/stdc++.h>
using namespace std;

int lowbit(int x) {
    return x & -x;
}

int nextSameHammingWeightNumber(int x) {
    int t = x + lowbit(x);
    return t | (((lowbit(t) / lowbit(x)) >> 1) - 1);
}

int nextSubMask(int subMask, int mask) {
    return (subMask - 1) & mask;
}

typedef long long LL;
const int maxn = 16;
int n, l, x, cas;
int bits[1 << maxn], dp[1 << maxn];

int main() {
    #ifdef ExRoc
    freopen("test.txt", "r", stdin);
    #endif // ExRoc
    ios::sync_with_stdio(false);

    while (cin >> n, n != 0) {
        for (int i = 0; i < n; ++i) {
            cin >> l;
            bits[1 << i] = (1 << i);
            for (int j = 0; j < l; ++j) {
                cin >> x;
                bits[1 << i] |= (1 << x);
            }
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = (1 << i) - 1; j < (1 << n); j = nextSameHammingWeightNumber(j)) {
                bits[j] = bits[j ^ lowbit(j)] | bits[lowbit(j)];
                dp[j] = ((bits[j] == (1 << n) - 1) ? 1 : 0);
            }
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = (1 << i) - 1; j < (1 << n); j = nextSameHammingWeightNumber(j)) {
                for (int k = j; k != 0; k = nextSubMask(k, j)) {
                    dp[j] = max(dp[j], dp[j ^ k] + dp[k]);
                }
            }
        }
        printf("Case %d: %d\n", ++cas, dp[(1 << n) - 1]);
    }

    return 0;
}
