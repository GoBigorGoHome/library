struct dsu { // 0-indexed
    vector<int> p;
    vector<int> sz;
    vector<int> op;

    dsu(int n) : p(n, -1), sz(n, 1) {}

    int find(int x) {
        while (p[x] != -1) {
            x = p[x];
        }
        return x;
    }

    void merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y)
            return;
        // small-to-large merging
        if (sz[x] > sz[y])
            swap(x, y);
        p[x] = y;
        sz[y] += sz[x];
        op.push_back(x);
    }
    
    void undo() { // 撤销最近一次的 merge 操作
        int x = op.back();
        op.pop_back();
        int y = p[x];
        p[x] = -1;
        sz[y] -= sz[x];
    }

    void rollback(int s) {
        while (s < (int) op.size())
            undo();
    }

    int size(int x) {
        return sz[find(x)];
    }
};
