template<typename T, auto op, auto e> // requires op be commutative.
struct fenwick {
    vector<T> a;

    fenwick(int n) : a(n, e()) {}

    fenwick(const vector<T>& a_) : a(a_) {
        for (size_t i = 0; i < a.size(); i++)
            if ((i | (i + 1))  < a.size())
                a[i | (i + 1)] = op(a[i], a[i | (i + 1)]);
    }

    fenwick(int n, T v) : fenwick(vector<T>(n, v)) {}

    void add(int p, T v) {
        while (p <  a.size()) {
            a[p] = op(a[p], v);
            p |= p + 1;
        }
    }

    void push_back(T v) {
        size_t p = a.size();
        for (size_t len = 1; len & p; len <<= 1)
            v = op(a[p ^ len], v);
        a.push_back(v);
    }

    T sum(int n) {
        n = min(n, (int) a.size());
        T ans = e();
        while (n > 0) {
            ans = op(ans, a[n - 1]);
            n &= n - 1;
        }
        return ans;
    }

    int max_prefix(std::predicate<T> auto f) {
        T sum = e();
        size_t at = 0;
        for (size_t len = std::bit_floor(a.size()); len > 0; len >>= 1) {
            if (at + len <= a.size()) {
                T new_sum = op(sum, a[at + len - 1]);
                if (f(new_sum)) {
                    sum = new_sum;
                    at += len;
                }
            }
        }
        return (int) at;
    }
};
