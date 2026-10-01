struct Tarjan {
  vector<int> stk, roots, in, low;
  vector<vector<int>> comps;
  int timer{};
  
  Tarjan() { }
  Tarjan(vector<vector<int>> &adj) { build(adj); }

  void dfs(int u, vector<vector<int>> &adj) {
    low[u] = in[u] = timer++;
    stk.push_back(u);
  
    for (int v : adj[u]) {
      if (in[v] == -1) dfs(v, adj);
      if (roots[v] == -1) low[u] = min(low[u], low[v]);
    }
  
    if (low[u] == in[u]) {
      comps.push_back({u});
      while (true) {
        int v = stk.back();
        stk.pop_back();
        roots[v] = u;
        if (v == u) break;
        comps.back().push_back(v);
      }
    }
  }
  
  void build(vector<vector<int>> &adj) {
    int n = int(adj.size());
    
    roots.assign(n, -1);
    in.assign(n, -1);
    low.assign(n, -1);

    // change u to 0 if the nodes are 0 based
    for (int u = 1; u < n; ++u) {
      if (in[u] == -1) {
        dfs(u, adj);
      }
    }
  }
};