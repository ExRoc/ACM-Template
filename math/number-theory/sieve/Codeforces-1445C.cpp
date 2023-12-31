// https://codeforces.com/contest/1445/problem/C
#include <bits/stdc++.h>
using namespace std;

template<int MAX_SIZE>
struct Sieve {
    int cnt;
    int phi[MAX_SIZE + 1];
    int prime[MAX_SIZE + 1];
    int mobius[MAX_SIZE + 1];
    bool isPrime[MAX_SIZE + 1];

    Sieve() {
        cnt = 0;
        isPrime[0] = isPrime[1] = false;
        for (int i = 2; i <= MAX_SIZE; ++i) {
            isPrime[i] = true;
        }
        phi[1] = 1;
        mobius[1] = 1;
        for (int i = 2; i <= MAX_SIZE; ++i) {
            if (isPrime[i]) {
                prime[++cnt] = i;
                phi[i] = i - 1;
                mobius[i] = -1;
            }
            for (int j = 1; j <= cnt && i <= MAX_SIZE / prime[j]; ++j) {
                int k = i * prime[j];
                isPrime[k] = false;
                if (i % prime[j] != 0) {
                    phi[k] = phi[i] * phi[prime[j]];
                    mobius[k] = -mobius[i];
                } else {
                    mobius[k] = 0;
                    phi[k] = phi[i] * prime[j];
                    break;
                }
            }
        }
    }

    vector<pair<long long, int>> getPrimeFactor(long long n) {
        vector<pair<long long, int>> result;
        for (int i = 1; i <= cnt && prime[i] <= n / prime[i]; ++i) {
            if (n % prime[i] == 0) {
                int k = 0;
                while (n % prime[i] == 0) {
                    n /= prime[i];
                    ++k;
                }
                result.push_back({prime[i], k});
            }
        }
        if (n != 1) {
            result.push_back({n, 1});
        }
        return result;
    }

    long long getPhi(long long n) {
        if (n <= MAX_SIZE) {
            return phi[n];
        }
        long long ret = n;
        for (int i = 1; i <= cnt && prime[i] <= n / prime[i]; ++i) {
            if (n % prime[i] == 0) {
                ret = ret / prime[i] * (prime[i] - 1);
                while (n % prime[i] == 0) {
                    n /= prime[i];
                }
            }
        }
        if (n != 1) {
            ret = ret / n * (n - 1);
        }
        return ret;
    }
};

typedef long long LL;
const int maxn = 100000 + 100;
int T, q;
LL p, ans;
Sieve<maxn> sieve;

LL solve(LL p, const pair<LL, int> &pr) {
    while (p % pr.first == 0) {
        p /= pr.first;
    }
    for (int i = 1; i < pr.second; ++i) {
        p *= pr.first;
    }
    return p;
}

int main() {
#ifdef ExRoc
    freopen("test.txt", "r", stdin);
#endif // ExRoc
    ios::sync_with_stdio(false);

    cin >> T;
    while (T--) {
        cin >> p >> q;
        if (p % q != 0) {
            cout << p << endl;
            continue;
        }
        ans = 1;
        vector<pair<LL, int>> result = sieve.getPrimeFactor(q);
        for (pair<LL, int> &pr: result) {
            ans = max(ans, solve(p, pr));
        }
        cout << ans << endl;
    }

    return 0;
}
