// A generic fenwick tree where a[i] is sum over the range [i, i | (i + 1)).
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
        assert(p < (int) a.size());
        p += 1;
        while (p > 0) {
            a[p - 1] = op(a[p - 1], v);
            p &= p - 1;
        }
    }

    void push_back(T v) {
        int p = (int) a.size();
        a.push_back(e());
        add(p, v);
    }

    T sum(int p) { // sum of all but the first p elements.
        p = max(0, p);
        T ans = e();
        while (p < n) {
            ans = op(ans, a[p]);
            p |= p + 1;
        }
        return ans;
    }

    int max_suffix(std::predicate<T> auto auto f) {
        
    }
};
