struct BIT {
  vector<int> tree;
  BIT(int n) { tree.assign(n + 5, {}); }
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
  void update(int i, int v) {
    for (++i; i < int(tree.size()); i += i & -i) {
      tree[i] += v;
    }
  }
};
