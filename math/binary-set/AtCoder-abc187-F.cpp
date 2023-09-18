#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = 18;
int n, m, a, b;
int dp[1 << maxn];
bool G[maxn][maxn];

inline int lowbit(int x) {
    return x & -x;
}

inline int nextSameHammingWeightNumber(int x) {
    int t = x + lowbit(x);
    return t | (((lowbit(t) / lowbit(x)) >> 1) - 1);
}

inline int nextSubMask(int subMask, int mask) {
	return (subMask - 1) & mask;
}

bool judge(int status) {
    if (__builtin_popcount(status) == 1) {
        return true;
    }
    for (int i = 0; i < n; ++i) {
        if ((status & (1 << i)) != 0) {
            for (int j = i + 1; j < n; ++j) {
                if ((status & (1 << j)) != 0) {
                    if (!G[i][j]) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int main() {
#ifdef ExRoc
    freopen("test.txt", "r", stdin);
#endif // ExRoc
    ios::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        --a;
        --b;
        G[a][b] = G[b][a] = true;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = (1 << i) - 1; j < (1 << n); j = nextSameHammingWeightNumber(j)) {
            if (judge(j)) {
                dp[j] = 1;
                continue;
            }
            dp[j] = n;
            for (int s = nextSubMask(j, j); s > 0; s = nextSubMask(s, j)) {
                dp[j] = min(dp[j], dp[s] + dp[j ^ s]);
            }
        }
    }
    cout << dp[(1 << n) - 1] << endl;

    return 0;
}
