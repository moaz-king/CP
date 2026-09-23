struct LCA {
  int n;
  vector<int> in, flat, node;
  vector<vector<int>> table;
  LCA() { }
  LCA(vector<vector<int>> &adj, int root) {
    n = int(adj.size()) - 1;
    in.assign(n + 1, 0);
    dfs(root, -1, adj);
    build();
  }
  void dfs(int u, int p, vector<vector<int>> &adj) {
    int idx = int(node.size());
    node.push_back(u);
    in[u] = int(flat.size());
    flat.push_back(idx);
    for (int v : adj[u]) {
      if (v == p) continue;
      dfs(v, u, adj);
      flat.push_back(idx);
    }
  }
  void build() {
    int sz = int(flat.size());
    int m = __lg(sz) + 1;
    table.assign(sz, vector<int>(m));
    for (int i = 0; i < sz; ++i) {
      table[i][0] = flat[i];
    }
    for (int p = 1; p < m; ++p) {
      for (int i = 0; i + (1 << p) <= sz; ++i) {
        table[i][p] = min(table[i][p - 1], table[i + (1 << (p - 1))][p - 1]);
      }
    }
  }
  int lca(int u, int v) {
    if (min(u, v) <= 0) return max(u, v);
    assert(u >= 1 && u <= n && v >= 1 && v <= n);
    int l = in[u], r = in[v];
    if (l > r) swap(l, r);
    int p = __lg(r - l + 1);
    return node[min(table[l][p], table[r - (1 << p) + 1][p])];
  }
};
