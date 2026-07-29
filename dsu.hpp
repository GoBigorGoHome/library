struct dsu {
    vector<int> ps; // parent or size
    dsu(int n) : ps(n, -1) {}
    int leader(int x) {
        return ps[x] < 0 ? x : ps[x] = leader(ps[x]);
    }
    int merge(int x, int y) {
        x = leader(x);
        y = leader(y);
        if (x == y) return x;
        if (ps[x] < ps[y])
            swap(x, y);
        ps[y] += ps[x];
        ps[x] = y;
        return y;
    }
    bool same(int x, int y) {
        return leader(x) == leader(y);
    }
    int size(int x) {
        return -ps[leader(x)];
    }
};