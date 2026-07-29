const int maxn = 1e5 + 5;
bool del[maxn];
int sz[maxn];

vector<int> g[maxn];

void get_size(int u, int p) {
    sz[u] = 1;
    for (int v : g[u]) {
        if (v == p || del[v]) continue;
        get_size(v, u);
        sz[u] += sz[v];
    }
}

int find_centroid(int u) {
    get_size(u, 0);
    int p = 0;
    int tree_sz = sz[u];
    while (1) {
        int next = -1;
        for (int v : g[u]) {
            if (del[v] || v == p) continue;
            if (sz[v] * 2 > tree_sz) {
                next = v;
                break;
            }
        }
        if (next == -1) break;
        p = u;
        u = next;
    }
    return u;
}

vector<int> divide() {
    vector<int> seq;
    seq.push_back(find_centroid(1));
    for (int i = 0; i < (int) seq.size(); i++) {
        int u = seq[i];
        del[u] = true;
        for (int v : g[u]) {
            if (!del[v])
                seq.push_back(find_centroid(v));
        }
    }
    for (int u : seq)
        del[u] = false;
    return seq;
}
//以上是树的重心分解。
