struct Tarjan {
  vector<int> stk, root, in, low;
  vector<vector<int>> comps, adj;
  int timer{};
  
  Tarjan() { }
  Tarjan(vector<vector<int>> &adj) : adj(adj) { build(); }

  void dfs(int u) {
    low[u] = in[u] = timer++;
    stk.push_back(u);
  
    for (int v : adj[u]) {
      if (in[v] == -1) dfs(v);
      if (root[v] == -1) low[u] = min(low[u], low[v]);
    }
  
    if (low[u] == in[u]) {
      comps.push_back({u});
      while (true) {
        int v = stk.back();
        stk.pop_back();
        root[v] = u;
        if (v == u) break;
        comps.back().push_back(v);
      }
    }
  }
  
  void build() {
    int n = int(adj.size());
    
    root.assign(n, -1);
    in.assign(n, -1);
    low.assign(n, -1);

    for (int u = 1; u < n; ++u) {
      if (in[u] == -1) {
        dfs(u);
      }
    }
  }

  vector<vector<int>> get_cond() {
    int n = int(adj.size());
    
    vector<vector<int>> adj_cond(n);
    for (int u = 1; u < n; ++u) {
      for (int v : adj[u]) {
        if (root[u] != root[v]) {
          adj_cond[root[u]].push_back(root[v]);
        }
      }
    }
    
    return adj_cond;
  }
};