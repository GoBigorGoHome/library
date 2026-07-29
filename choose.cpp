const int mod = 998244353;
const int maxn = 3e6 + 5;
long long fact[maxn], invf[maxn];

long long power(long long x, int n) {
    long long ans = 1;
    while (n) {
        if (n & 1)
            ans = ans * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return ans;
}

void prepare() {
    fact[0] = 1;
    for (int i = 1; i < maxn; i++)
        fact[i] = fact[i - 1] * i % mod;
    invf[maxn - 1] = power(fact[maxn - 1], mod - 2);
    for (int i = maxn - 1; i > 0; i--)
        invf[i - 1] = invf[i] * i % mod;
}

long long choose(int n, int k) {
    return 0 <= k && k <= n ? fact[n] * invf[n - k] % mod * invf[k] % mod : 0;
}

long long mchoose(int n, int k) {
    return choose(n + k - 1, k);
}
