template<int MOD = 1>
class mint {
private:
    int value;
    int mod;

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

public:
    mint(): value(0), mod(MOD) {}

    mint(long long value): mod(MOD) {
        setValue(value);
    }

    void setValue(long long value) {
        if (value >= 0 && value < mod) {
            this->value = value;
            return ;
        }
        value %= mod;
        if (value < 0) {
            value += mod;
        }
        this->value = value;
    }

    void setMod(int mod) {
        this->mod = mod;
    }

    int mod() {
        return mod;
    }

    int value() {
        return value;
    }

    mint& operator++() {
        ++value;
        if (value == mod) {
            value = 0;
        }
        return *this;
    }

    mint operator++(int) {
        mint res = *this;
        ++*this;
        return res;
    }

    mint operator--() {
        if (value == 0) {
            value = mod;
        }
        --value;
        return *this;
    }

    mint operator--(int) {
        mint res = *this;
        --*this;
        return res;
    }

    mint& operator+=(const mint& rhs) {
        value += rhs.value;
        if (value >= mod) {
            value -= mod;
        }
        return *this;
    }

    mint& operator-=(const mint& rhs) {
        value -= rhs.value;
        if (value < 0) {
            value += mod;
        }
        return *this;
    }

    mint& operator*=(const mint& rhs) {
        value = (long long) value * rhs.value % mod;
        return *this;
    }

    mint& operator/=(const mint& rhs) {
        return *this = *this * rhs.inv();
    }

    mint operator+() const {
        return *this;
    }

    mint operator-() const {
        return mint() - *this;
    }

    mint pow(long long n) const {
        mint res = *this;
        mint ans = 1;
        while (n != 0) {
            if ((n & 1) == 1) {
                ans *= res;
            }
            res *= res;
            n >>= 1;
        }
        return ans;
    }

    mint inv() const {
        long long x, y;
        exgcd(value, mod, x, y);
        return x;
    }

    friend mint operator+(const mint& lhs, const mint& rhs) {
        return mint(lhs) += rhs;
    }

    friend mint operator-(const mint& lhs, const mint& rhs) {
        return mint(lhs) -= rhs;
    }

    friend mint operator*(const mint& lhs, const mint& rhs) {
        return mint(lhs) *= rhs;
    }

    friend mint operator/(const mint& lhs, const mint& rhs) {
        return mint(lhs) /= rhs;
    }

    friend bool operator==(const mint& lhs, const mint& rhs) {
        return lhs.value == rhs.value;
    }

    friend bool operator!=(const mint& lhs, const mint& rhs) {
        return lhs.value != rhs.value;
    }
};
