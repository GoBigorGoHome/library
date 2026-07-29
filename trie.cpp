template<int sigma_size, int (*ctoi)(char)>
struct Trie {
    vector<array<int, sigma_size>> go;
    int new_node() {
        go.push_back({});
        return (int) go.size() - 1;
    }

    Trie() {
        new_node();
    }

    int add(string s) {
        int p = 0;
        for (char c : s) {
            int i = ctoi(c);
            if (go[p][i] == 0) {
                go[p][i] = new_node();
            }
            p = go[p][i];
        }
        return p;
    }

    vector<pair<int,int>> get_suffix_link() {
    vector<pair<int,int>> q; //队列
    for (int i = 0; i < sigma_size; i++)
        if (go[0][i])
            q.push_back({go[0][i], 0});
    for (int j = 0; j < (int) q.size(); j++) {
        int u = q[j].first, v = q[j].second;
        for (int i = 0; i < sigma_size; i++)
            if (go[u][i])
                q.push_back({go[u][i], go[v][i]});
            else
                go[u][i] = go[v][i]; //把缺的边补上
    }
        return q;
    }
};

int ctoi(char c) {
    return c - 'a';
}
// usage: Trie<26, ctoi> ac;
