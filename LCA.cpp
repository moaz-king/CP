struct LCA {
  int n, lg;
  vector<int> dep;
  vector<vector<int>> up;

  LCA() { }

  void dfs(const vector<vector<int>> &adj, int u, int p) {
    for (auto &v : adj[u]) {
      if (v == p) continue;
      dep[v] = 1 + dep[u];
      up[v][0] = u;
      for (int i = 1; i <= lg; ++i) {
        up[v][i] = up[up[v][i - 1]][i - 1];
      }
      dfs(adj, v, u);
    }
  }

  LCA(const vector<vector<int>> &adj, int rt = 1) {
    n = int(adj.size());
    lg = __lg(n) + 1;
    dep.assign(n + 1, 0);
    up.assign(n + 1, vector<int>(lg + 1));
    dfs(adj, rt, -1);
  }

  int kth_anc(int u, int k) {
    if (k > dep[u]) return -1;
    for (int i = lg; i >= 0; --i) {
      if (k >> i & 1) {
        u = up[u][i];
      }
    }
    return u;
  }
  
  int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int k = dep[u] - dep[v];
    u = kth_anc(u, k);
    if (u == v) return u;
    for (int i = lg; i >= 0; --i) {
      if (up[u][i] != up[v][i]) {
        u = up[u][i];
        v = up[v][i];
      }
    }
    return up[u][0];
  }
};
