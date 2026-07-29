vector<int> get_primes(int n) {
    vector<int> primes;
    vector<bool> flag(n + 1);
    for (int i = 2; i <= n; i++) {
        if (!flag[i]) {
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p * i > n) break;
            flag[p * i] = true;
            if (i % p == 0) break;
        }
    }
    return primes;
}
