template <integral T>
struct fenwick {
    vector<T> a;

    fenwick(const vector<T>& a_) : a(a_) {
        for (size_t i = 0; i < a.size(); i++)
            if ((i | (i + 1))  < a.size())
                a[i | (i + 1)] += a[i];
    }

    fenwick(int n = 0, T v = 0) : fenwick(vector<T>(n, v)) {}

    // 返回前n项之和，即 a[0] + ... + a[n - 1]
    T sum(int n) {
        n = min(n, (int) a.size());
        T ans = 0;
        while (n > 0) {
            ans += a[n - 1];
            n &= n - 1;
        }
        return ans;
    }
    // 返回 a[l] + ... + a[r - 1]
    T sum(int l, int r) {
        return sum(r) - sum(l);
    }

    void push_back(T v) {
        size_t p = a.size();
        for (size_t len = 1; len & p; len <<= 1)
            v += a[p ^ len];
        a.push_back(v);
    }

    void add(int p, T v) {
        while (p < (int) a.size()) {
            a[p] += v;
            p |= p + 1;
        }
    }
    // Returns the length of the longest prefix with sum <= v
    int max_prefix(T v) {
        T sum = 0;
        size_t p = 0;
        for (size_t len = bit_floor(a.size()); len > 0; len >>= 1) {
            if (p + len <= a.size() && !(v < sum + a[p + len - 1])) {
                sum += a[p + len - 1];
                p += len;
            }
        }
        return (int) p;
    }
};
