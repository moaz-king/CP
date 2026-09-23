struct BIT {
  int n{};
  vector<int> tree;
  BIT(int sz) : n(sz + 5) { tree.assign(n, {}); }
  BIT(vector<int> &a) {
    n = int(a.size()) + 5;
    tree.assign(n, {});
    for (int i = 1; i <= int(a.size()); ++i) {
      tree[i] += a[i - 1];
      int r = i + (i & -i);
      if (r < n) tree[r] += tree[i];
    }
  }
  int query(int r) {
    int res = 0;
    for (++r; r > 0; r -= r & -r) {
      res += tree[r];
    }
    return res;
  }
  int query(int l, int r) {
    return query(r) - query(l - 1);
  }
  // BIT must be monotonic.
  int lower_bound(int x) {
    int pos = 0, sum = 0;
    for (int i = __lg(n); ~i; --i) {
      if (pos + (1 << i) < n && sum + tree[pos + (1 << i)] < x) {
        pos += 1 << i;
        sum += tree[pos];
      }
    }
    return pos;
  }
  void update(int i, int v) {
    for (++i; i < int(tree.size()); i += i & -i) {
      tree[i] += v;
    }
  }
};
