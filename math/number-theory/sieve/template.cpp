template<int MAX_SIZE>
class Sieve {
private:
    int cnt;
    int phi[MAX_SIZE + 1];
    int prime[MAX_SIZE + 1];
    int mobius[MAX_SIZE + 1];
    bool isPrime[MAX_SIZE + 1];

public:
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
};