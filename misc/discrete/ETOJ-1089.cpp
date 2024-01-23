// https://oj.eriktse.com/problem.php?id=1089
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = 300000 + 100;
int n, q;
pair<int, int> ix[maxn];
pair<int, int> lr[maxn];
int sum[maxn];

void discrete() {
    vector<int> sand;
    for (int i = 10; i < n; ++i) {
        sand.push_back(ix[i].first);
    }
    for (int i = 0; i < q; ++i) {
        sand.push_back(lr[i].first - 1);
        sand.push_back(lr[i].second);
    }
    sort(sand.begin(), sand.end());
    sand.erase(unique(sand.begin(), sand.end()), sand.end());
    for (int i = 0; i < n; ++i) {
        ix[i].first = lower_bound(sand.begin(), sand.end(), ix[i].first) - sand.begin() + 1;
    }
    for (int i = 0; i < q; ++i) {
        lr[i].first = lower_bound(sand.begin(), sand.end(), lr[i].first - 1) - sand.begin() + 1;
        lr[i].second = lower_bound(sand.begin(), sand.end(), lr[i].second) - sand.begin() + 1;
    }
}

int main() {
#ifdef ExRoc
    freopen("test.txt", "r", stdin);
#endif // ExRoc
    ios::sync_with_stdio(false);

    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> ix[i].first >> ix[i].second;
    }
    for (int i = 0; i < q; ++i) {
        cin >> lr[i].first >> lr[i].second;
    }
    discrete();
    for (int i = 0; i < n; ++i) {
        sum[ix[i].first] += ix[i].second;
    }
    for (int i = 1; i < maxn; ++i) {
        sum[i] += sum[i - 1];
    }
    for (int i = 0; i < q; ++i) {
        cout << sum[lr[i].second] - sum[lr[i].first] << endl;
    }

    return 0;
}
