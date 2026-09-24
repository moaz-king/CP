struct Edge {
  int mn, mx;
  Edge() { mn = 2e9, mx = -2e9; }
  Edge(int x) { mn = mx = x; }
};

template<typename T, auto merge>
struct LCA {
  int n, lg;
  vector<int> dep;
  vector<vector<int>> up;
  vector<vector<T>> tbl;

  LCA() { }

  void dfs(const vector<vector<pair<int, int>>> &adj, int u, int p = -1) {
    for (auto &[v, w] : adj[u]) {
      if (v == p) continue;
      dep[v] = dep[u] + 1;
      up[v][0] = u;
      tbl[v][0] = Edge(w);
      for (int i = 1; i < lg; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
        tbl[v][i] = merge(tbl[v][i - 1], tbl[up[v][i - 1]][i - 1]);
      }
      dfs(adj, v, u);
    }
  }

  LCA(const vector<vector<pair<int, int>>> &adj, int rt = 1) {
    n = adj.size();
    lg = __lg(n) + 1;
    dep = vector<int>(n + 1);
    up = vector<vector<int>>(n + 1, vector<int>(lg + 1));
    tbl = vector<vector<T>>(n + 1, vector<T>(lg + 1));
    dfs(adj, rt);
  }

  int kth_anc(int u, int k) {
    if (k > dep[u]) return -1;
    for (int i = lg; i >= 0; i--) {
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
    for (int i = lg; i >= 0; i--) {
      if (up[u][i] != up[v][i]) {
        u = up[u][i];
        v = up[v][i];
      }
    }
    return up[u][0];
  }

  T query(int u, int k) {
    // query on k nodes above u
    T cur;
    for (int i = 0; i <= lg; ++i) {
      if (k >> i & 1) {
        cur = merge(cur, tbl[u][i]);
        u = up[u][i];
      }
    }
    return cur;
  }
};

inline Edge merge_q(const Edge &a, const Edge &b) {
  // a is the closest half, b is the farthest
  Edge res;
  res.mn = min(a.mn, b.mn);
  res.mx = max(a.mx, b.mx);
  return res;
}
