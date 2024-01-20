// https://acm.hdu.edu.cn/showproblem.php?pid=6356
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = 100000 + 100;
int T, n, m, l, r, v;
LL ans;
unsigned int x, y, z;
LL items[maxn << 2];

void pushDown(int rt) {
    items[rt << 1] = max(items[rt << 1], items[rt]);
    items[rt << 1 | 1] = max(items[rt << 1 | 1], items[rt]);
}

void update(int rt, int l, int r, int L, int R, LL x) {
    if (l >= R || r <= L) {
        return;
    }
    if (l >= L && r <= R) {
        items[rt] = max(items[rt], x);
        return;
    }
    if (items[rt] >= x) {
        return;
    }
    int m = (l + r) >> 1;
    pushDown(rt);
    update(rt << 1, l, m, L, R, x);
    update(rt << 1 | 1, m, r, L, R, x);
}


void build(int rt, int l, int r) {
    items[rt] = 0;
    if (r - l == 1) {
        return;
    }
    int m = (l + r) >> 1;
    build(rt << 1, l, m);
    build(rt << 1 | 1, m, r);
};

long long query(int rt, int l, int r) {
    if (r - l == 1) {
        return items[rt] * (l + 1);
    }
    pushDown(rt);
    int m = (l + r) >> 1;
    return query(rt << 1, l, m) ^ query(rt << 1 | 1, m, r);
}

long long query() {
    return query(1, 0, n);
}

void update(int l, int r, LL x) {
    return update(1, 0, n, l, r, x);
}

unsigned int rng61() {
    x = x ^ (x << 11);
    x = x ^ (x >> 4);
    x = x ^ (x << 5);
    x = x ^ (x >> 14);
    unsigned int w = x ^ (y ^ z);
    x = y;
    y = z;
    z = w;
    return z;
}

void read() {
    unsigned int nn = n;
    int a = rng61() % nn + 1;
    int b = rng61() % nn + 1;
    l = min(a, b);
    r = max(a, b);
    v = rng61() & ((1 << 30) - 1);
}

int main() {
#ifdef ExRoc
    freopen("test.txt", "r", stdin);
#endif // ExRoc
    ios::sync_with_stdio(false);

    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d%d%d", &n, &m, &x, &y, &z);
        build(1, 0, n);
        while (m--) {
            read();
            --l;
            update(l, r, v);
        }
        printf("%I64d\n", query());
    }

    return 0;
}
