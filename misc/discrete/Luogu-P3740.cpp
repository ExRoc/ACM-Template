// https://www.luogu.com.cn/problem/P3740
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = 3000 + 100;
struct Node {
    int l, r;
    Node() {}
    Node(int l, int r) : l(l), r(r) {}
};

int n, m;
int num[maxn];
Node node[maxn];
set<int> st;

void discrete() {
    vector<int> sand;
    for (int i = 1; i <= m; ++i) {
        sand.push_back(node[i].l);
        sand.push_back(node[i].r);
        sand.push_back(node[i].r + 1);
    }
    sand.push_back(n);
    sort(sand.begin(), sand.end());
    sand.erase(unique(sand.begin(), sand.end()), sand.end());
    for (int i = 1; i <= m; ++i) {
        node[i].l = lower_bound(sand.begin(), sand.end(), node[i].l) - sand.begin();
        node[i].r = lower_bound(sand.begin(), sand.end(), node[i].r) - sand.begin();
    }
    n = lower_bound(sand.begin(), sand.end(), n) - sand.begin();
}

int main() {
#ifdef ExRoc
    freopen("test.txt", "r", stdin);
#endif // ExRoc
    ios::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> node[i].l >> node[i].r;
    }
    discrete();
    for (int i = 1; i <= m; ++i) {
        for (int j = node[i].l; j <= node[i].r; ++j) {
            num[j] = i;
        }
    }
    for (int i = 0; i <= n; ++i) {
        st.insert(num[i]);
    }
    st.erase(0);
    cout << st.size() << endl;

    return 0;
}
