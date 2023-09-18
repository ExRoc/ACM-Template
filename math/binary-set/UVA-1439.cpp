#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = 15;
struct Node {
    int depth;
    int pre;

    Node() {}

    Node(int d, int p) {
        depth = d;
        pre = p;
    }
};

int n, idd;
char ch1, ch2;
int depth[maxn];
bool isIndependent[1 << maxn];
Node dp[1 << maxn];
bool G[maxn][maxn];
pair<int, int> p[100];
char rid[maxn];
unordered_map<char, int> id;
unordered_map<char, int>::iterator it;

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

void init() {
    id.clear();
    idd = 0;
    memset(G, 0, sizeof(G));
}

int getId(char ch) {
    it = id.find(ch);
    if (it != id.end()) {
        return it->second;
    }
    rid[idd] = ch;
    id[ch] = idd++;
    return idd - 1;
}

bool judgeIsIndependent(int status) {
    while (status != 0) {
        int idx = __builtin_ctz(status);
        status ^= lowbit(status);
        int tmp = status;
        while (tmp != 0) {
            if (G[idx][__builtin_ctz(tmp)]) {
                return false;
            }
            tmp ^= lowbit(tmp);
        }
    }
    return true;
}

void getDepth(int status) {
    int d = dp[status].depth;
    status ^= dp[status].pre;
    while (status != 0) {
        depth[__builtin_ctz(status)] = d;
        status ^= lowbit(status);
    }
}

int main() {
    #ifdef ExRoc
    freopen("test.txt", "r", stdin);
    #endif // ExRoc
    ios::sync_with_stdio(false);

    while (cin >> n) {
        init();
        for (int i = 0; i < n; ++i) {
            cin >> ch1 >> ch2;
            p[i].first = getId(ch1);
            p[i].second = getId(ch2);
            G[p[i].first][p[i].second] = true;
            G[p[i].second][p[i].first] = true;
        }
        for (int i = 0; i < (1 << maxn); ++i) {
            isIndependent[i] = judgeIsIndependent(i);
        }
        for (int i = 1; i <= idd; ++i) {
            for (int j = (1 << i) - 1; j < (1 << idd); j = nextSameHammingWeightNumber(j)) {
                if (isIndependent[j]) {
                    dp[j] = Node(0, 0);
                    continue;
                }
                dp[j] = Node(-1, -1);
                for (int k = nextSubMask(j, j); k != 0; k = nextSubMask(k, j)) {
                    if (dp[k].depth != -1 && isIndependent[j ^ k]) {
                        if (dp[j].depth == -1) {
                            dp[j] = Node(dp[k].depth + 1, k);
                        } else {
                            if (dp[j].depth > dp[k].depth + 1) {
                                dp[j] = Node(dp[k].depth + 1, k);
                            }
                        }
                    }
                }
            }
        }
        int status = (1 << idd) - 1;
        while (status != 0) {
            getDepth(status);
            status = dp[status].pre;
        }
        cout << dp[(1 << idd) - 1].depth - 1 << endl;
        for (int i = 0; i < n; ++i) {
            if (depth[p[i].first] > depth[p[i].second]) {
                swap(p[i].first, p[i].second);
            }
            cout << rid[p[i].first] << " " << rid[p[i].second] << endl;
        }
    }

    return 0;
}
