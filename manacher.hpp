vector<int> manacher(string s) {
    int n = s.size();
    vector<int> rad(2 * n - 1);
    int l = -1, r = -1;
    for (int i = 0; i < 2 * n - 1; i++) {
        int p = i / 2, q = (i + 1) / 2;
        int k = r <= p ? 0 : min(r - p, rad[2 * (l + r) - i]);
        while (0 <= q - k - 1 && p + k + 1 < n && s[q - k - 1] == s[p + k + 1]) {
            k++;
        }
        rad[i] = k;
        if (p + k > r) {
            r = p + k;
            l = q - k;
        }
    }
    return rad;
}