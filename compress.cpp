template<typename T>
vector<int> compress(vector<T>& a) {
    int n = (int) a.size();
    vector<int> I(n);
    iota(I.begin(), I.end(), 0);
    sort(I.begin(), I.end(), [&](int i, int j) { return a[i] < a[j]; });

    vector<T> b;
    vector<int> res(n);
    for (int i : I) {
        if (b.empty() || b.back() < a[i])
            b.push_back(a[i]);
        res[i] = b.size() - 1;
    }

    a = b;
    return res;
}

