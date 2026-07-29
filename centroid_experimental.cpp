// Requires -std=c++23 to compile.
// Nodes are 0-indexed.
vector<int> centroid_decomposition(const vector<vector<int>>& tree) {
    int n = (int) tree.size();
    vector<int> sz(n);
    vector<bool> del(n);
    vector<int> seq;

    [&](this auto divide, int x) -> void {
        [&](this auto get_sz, int u, int p) -> void {
            sz[u] = 1;
            for (int v : tree[u]) {
                if (del[v] || v == p) continue;
                get_sz(v, u);
                sz[u] += sz[v];
            }
        }(x, -1);

        int c = [&](this auto find_centroid, int u, int p, int tree_sz) -> int {
            for (int v : tree[u]) {
                if (del[v] || v == p) continue;
                if (sz[v] * 2 > tree_sz)
                    return find_centroid(v, u, tree_sz);
            }
            return u;
        }(x, -1, sz[x]);

        seq.push_back(c);
        del[c] = true;

        for (int v : tree[c]) // 这里容易写错，是 tree[c]，不是 tree[x]！
            if (!del[v])
                divide(v);
    }(0);

    return seq;
}
