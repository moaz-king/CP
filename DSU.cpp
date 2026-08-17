struct DSU {
  int n;
  vector<int> par, sz;
  DSU(int x) : n(x) {
    par = vector<int>(n + 1);
    sz = vector<int>(n + 1, 1);
    iota(par.begin(), par.end(), 0);
  }
  int find(int u) {
    if (par[u] == u) return u;
    return par[u] = find(par[u]);
  }
  bool unite(int u, int v) {
    int p1 = find(u);
    int p2 = find(v);
    if (p1 == p2) return;
    if (sz[p1] > sz[p2]) swap(p1, p2);
    par[p1] = p2;
    sz[p2] += sz[p1];
    return true;
  }
  bool same(int u, int v) { return find(u) == find(v); }
  int size(int u) { return sz[find(u)]; }
};
