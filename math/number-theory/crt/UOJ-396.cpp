// https://uoj.ac/problem/396
#include <bits/stdc++.h>
using namespace std;

class IO {
private:
    static const int MAX_SIZE = 1 << 20;
    char buf[MAX_SIZE], *p1, *p2;
    char pbuf[MAX_SIZE], *pp;

public:
#ifdef ExRoc
#else
    IO() : p1(buf), p2(buf), pp(pbuf) {}

    ~IO() {
        fwrite(pbuf, 1, pp - pbuf, stdout);
    }
#endif

    char getCh() {
#ifdef ExRoc
        return getchar();
#endif
        if (p1 == p2) {
            p1 = buf;
            p2 = p1 + fread(buf, 1, MAX_SIZE, stdin);
        }
        return p1 == p2 ? ' ' : *p1++;
    }

    bool isBlank(char ch) {
        return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
    }

    template <class T>
    void read(T &x) {
        bool sign = 0;
        char ch = getCh();
        while (!isdigit(ch)) {
            if (ch == '-') {
                sign = true;
            }
            ch = getCh();
        }

        x = 0;
        while (isdigit(ch)) {
            x = x * 10 + (ch - '0');
            ch = getCh();
        }

        if (ch == '.') {
            double tmp = 1.0;
            for (ch = getCh(); isdigit(ch); ch = getCh()) {
                tmp /= 10.0;
                x += tmp * (ch - '0');
            }
        }
        if (sign) {
            x = -x;
        }
    }

    void read(char *s) {
        char ch;
        for (ch = getCh(); isBlank(ch); ch = getCh());
        while (!isBlank(ch)) {
            *s++ = ch;
            ch = getCh();
        }
        *s = 0;
    }

    void read(char &c) {
        for (c = getCh(); isBlank(c); c = getCh());
    }

    void putCh(const char &c) {
#ifdef ExRoc
        putchar(c);
#else
        if (pp - pbuf == MAX_SIZE) {
            fwrite(pbuf, 1, MAX_SIZE, stdout);
            pp = pbuf;
        }
        *pp++ = c;
#endif
    }

    template <class T>
    void write(T x) {
        if (x < 0) {
            x = -x;
            putCh('-');
        }
        static T sta[35];
        int top = 0;
        do {
            sta[top++] = x % 10;
            x /= 10;
        } while (x != 0);
        while (top != 0) {
            putCh(sta[--top] + '0');
        }
    }

    template <class T>
    void write(T x, char lastChar) {
        write(x);
        putCh(lastChar);
    }
} io;

class CRT {
private:
    static void swap(__int128 &a, __int128 &b) {
        a ^= b ^= a ^= b;
    }

public:
    static __int128 exgcd(__int128 a, __int128 b, __int128 &x, __int128 &y) {
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }
        __int128 gcd = exgcd(b, a % b, x, y);
        __int128 t = x;
        x = y;
        y = t - (a / b) * y;
        return gcd;
    }

    static __int128 solve(__int128 *r, __int128 *m, int n, __int128 &lcm) {
        __int128 r0 = 0, m0 = 1;
        for (int i = 0; i < n; i++) {
            __int128 r1 = (r[i] % m[i] + m[i]) % m[i];
            __int128 m1 = m[i];
            if (m0 < m1) {
                swap(r0, r1);
                swap(m0, m1);
            }
            if (m0 % m1 == 0) {
                if (r0 % m1 != r1) {
                    lcm = 0;
                    return 0;
                }
                continue;
            }
            __int128 im, tmp;
            __int128 g = exgcd(m0, m1, im, tmp);
            __int128 u1 = (m1 / g);
            if ((r1 - r0) % g) {
                lcm = 0;
                return 0;
            }
            __int128 x = (r1 - r0) / g % u1 * im % u1;
            r0 += x * m0;
            m0 *= u1;
            if (r0 < 0) {
                r0 += m0;
            }
        }
        lcm = m0;
        return r0;
    }
};

typedef __int128 LL;
const int maxn = 100000 + 100;
int T, n, m, idx;
LL x, y, g, ans, mx;
map<LL, int> cnt;
map<LL, int>::iterator it;
LL a[maxn], p[maxn], newAtk[maxn];
LL atk[maxn], r[maxn], mm[maxn];

int main() {
#ifdef ExRoc
    freopen("test.txt", "r", stdin);
#endif // ExRoc
    ios::sync_with_stdio(false);

    io.read(T);
    while (T--) {
        cnt.clear();
        io.read(n);
        io.read(m);
        for (int i = 0; i < n; ++i) {
            io.read(a[i]);
        }
        for (int i = 0; i < n; ++i) {
            io.read(p[i]);
        }
        for (int i = 0; i < n; ++i) {
            io.read(newAtk[i]);
        }
        for (int i = 0; i < m; ++i) {
            io.read(x);
            ++cnt[x];
        }
        mx = 0;
        for (int i = 0; i < n; ++i) {
            it = cnt.upper_bound(a[i]);
            if (it != cnt.begin()) {
                --it;
            }
            atk[i] = it->first;
            mx = max(mx, (a[i] + atk[i] - 1) / atk[i]);
            --it->second;
            if (it->second == 0) {
                cnt.erase(it);
            }
            ++cnt[newAtk[i]];
        }

        idx = 0;
        ans = 1;
        for (int i = 0; i < n; ++i) {
            if (p[i] == 1) {
                mx = max(mx, (a[i] + atk[i] - 1) / atk[i]);
                continue;
            }
            g = CRT::exgcd(atk[i], p[i], x, y);
            if (a[i] % g != 0) {
                ans = -1;
                break;
            }
            LL pg = p[i] / g;
            r[idx] = (x * (a[i] / g) % pg + pg) % pg;
            mm[idx] = pg;
            ++idx;
        }
        if (ans == -1) {
            io.write(-1, '\n');
            continue;
        }
        if (idx == 0) {
            io.write(mx, '\n');
            continue;
        }
        ans = CRT::solve(r, mm, idx, x);
        if (ans == 0 && x == 0) {
            io.write(-1, '\n');
            continue;
        }
        if (ans < mx) {
            ans += (mx - ans + x - 1) / x * x;
        }
        io.write(ans, '\n');
    }

    return 0;
}
