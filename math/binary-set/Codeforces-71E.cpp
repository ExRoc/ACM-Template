// https://codeforces.com/problemset/problem/71/E
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
const int maxn = 17;
struct Node {
    int length;
    int pre;

    Node() {}

    Node(int l, int p) {
        length = l;
        pre = p;
    }
};

int n, m;
int a[maxn], b[maxn];
string e1[maxn], e2[maxn];
int sum[1 << maxn];
Node dp[1 << maxn];
unordered_map<string, int> w;
string element[101] = {
        "kong", "H", "He", "Li", "Be", "B", "C", "N", "O", "F", "Ne", "Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar",
        "K", "Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se", "Br",
        "Kr", "Rb", "Sr", "Y", "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb", "Te",
        "I", "Xe", "Cs", "Ba", "La", "Ce", "Pr", "Nd", "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm",
        "Yb", "Lu", "Hf", "Ta", "W", "Re", "Os", "Ir", "Pt", "Au", "Hg", "Tl", "Pb", "Bi", "Po", "At", "Rn",
        "Fr", "Ra", "Ac", "Th", "Pa", "U", "Np", "Pu", "Am", "Cm", "Bk", "Cf", "Es", "Fm"};

void print(int status) {
    int sstatus = status;
    status ^= dp[status].pre;
    bool flag = false;
    while (status != 0) {
        int idx = __builtin_ctz(status);
        if (flag) {
            cout << "+";
        }
        flag = true;
        cout << e1[idx];
        status ^= lowbit(status);
    }
    cout << "->" << e2[dp[sstatus].length - 1] << endl;
}

int main() {
#ifdef ExRoc
    freopen("test.txt", "r", stdin);
#endif // ExRoc
    ios::sync_with_stdio(false);

    for (int i = 1; i <= 100; ++i) {
        w[element[i]] = i;
    }
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> e1[i];
        a[i] =  w[e1[i]];
    }
    for (int i = 0; i < m; ++i) {
        cin >> e2[i];
        b[i] = w[e2[i]];
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = (1 << i) - 1; j < (1 << n); j = nextSameHammingWeightNumber(j)) {
            sum[j] = sum[j ^ lowbit(j)] + a[__builtin_ctz(j)];
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = (1 << i) - 1; j < (1 << n); j = nextSameHammingWeightNumber(j)) {
            dp[j] = Node(-1, -1);
            if (sum[j] == b[0]) {
                dp[j] = Node(1, 0);
                continue;
            }
            for (int k = nextSubMask(j, j); k != 0; k = nextSubMask(k, j)) {
                if (dp[k].length != -1 && dp[k].length != m) {
                    if (b[dp[k].length] == sum[j ^ k]) {
                        dp[j] = Node(dp[k].length + 1, k);
                        break;
                    }
                }
                if (dp[j].length != -1) {
                    break;
                }
            }
        }
    }
    if (dp[(1 << n) - 1].length != m) {
        cout << "NO" << endl;
        return 0;
    }
    cout << "YES" << endl;
    int status = (1 << n) - 1;
    while (status != 0) {
        print(status);
        status = dp[status].pre;
    }

    return 0;
}