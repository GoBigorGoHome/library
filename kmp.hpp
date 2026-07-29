vector<int> border_array(string s) {
    int n = s.size();
    vector<int> border(n);
    border[0] = 0;
    for (int i = 1; i < n; i++) {
        int j = border[i - 1];
        while (j > 0 && s[j] != s[i]) {
            j = border[j - 1];
        }
        if (s[j] == s[i])
            j++;
        border[i] = j;
    }
    return border;
}

vector<int> kmp_search(string t, string p) {
    vector<int> border = border_array(p);
    vector<int> res;
    int n = t.size();
    int m = p.size();
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j > 0 && t[i] != p[j])
            j = border[j - 1];
        if (t[i] == p[j])
            j++;
        if (j == m)
            res.push_back(i - m + 1);
    }
    return res;
}
