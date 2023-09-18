#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int exgcd(int a, int b, int& x, int& y) {
    x = 1, y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1 != 0) {
        int q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}

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

int main() {
#ifdef ExRoc
    freopen("test.txt", "r", stdin);
#endif // ExRoc
    ios::sync_with_stdio(false);

    int x;
    while (io.read(x), x != 0) {
        io.write(x, ' ');
    }

    return 0;
}