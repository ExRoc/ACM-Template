#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

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
long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long gcd = exgcd(b, a % b, x, y);
    long long t = x;
    x = y;
    y = t - (a / b) * y;
    return gcd;
}

template<int MAXN = 1, long long MOD = 1>
class Inverse {
private:
    int n;
    long long mod;
    int inv[MAXN + 1];

    int getInvByCache(int n) {
        if (n <= this->n) {
            return inv[n];
        }
        for (int i = this->n + 1; i <= n; ++i) {
            inv[i] = (mod - mod / i) * inv[mod % i] % mod;
        }
        this->n = n;
        return inv[n];
    }

    long long getInvByExgcd(long long n, long long mod) {
        long long x, y;
        exgcd(n, mod, x, y);
        return (x % mod + mod) % mod;
    }

public:
    Inverse() {
        n = 1;
        mod = MOD;
        inv[1] = 1;
    }

    void resetN(int n) {
        getInvByCache(n);
    }

    void resetMod(long long mod) {
        this->mod = mod;
        n = 1;
    }

    long long getInv(long long n) {
        if (n <= MAXN) {
            return getInvByCache(n);
        }
        return getInvByExgcd(n, mod);
    }

    long long getInv(long long n, long long mod) {
        if (mod == this->mod) {
            return getInv(n);
        }
        return getInvByExgcd(n, mod);
    }
};

const int maxn = 5e6 + 100;
const LL MOD = 1e9 + 7;
const LL cnst = 998244353;
Inverse<1, MOD> inverse;
int n;
LL inv, ans;
LL num[maxn], mult[maxn];

int main() {
#ifdef ExRoc
    freopen("test.txt", "r", stdin);
#endif // ExRoc
    ios::sync_with_stdio(false);

    io.read(n);
    mult[0] = 1;
    for (int i = 1; i <= n; ++i) {
        io.read(num[i]);
        mult[i] = mult[i - 1] * num[i] % MOD;
    }
    inv = inverse.getInv(mult[n]);
    LL tmp = 1;
    for (int i = n; i >= 1; --i) {
        ans = (ans + inv * mult[i - 1] % MOD * tmp % MOD) % MOD;
        inv = inv * num[i] % MOD;
        tmp = tmp * cnst % MOD;
    }
    cout << ans << endl;

    return 0;
}