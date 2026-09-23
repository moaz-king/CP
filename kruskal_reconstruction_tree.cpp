template <typename T>
struct KruskalReconstructionTree {
  vector<int> par;
  vector<vector<int>> adj;
  vector<T> wei;
  int root = -1;
  KruskalReconstructionTree() {}
  KruskalReconstructionTree(int n) : par(n), adj(n), wei(n, T()) {
    iota(par.begin(), par.end(), 0);
    par.reserve(2 * n - 1);
    adj.reserve(2 * n - 1);
    wei.reserve(2 * n - 1);
  }
  int find(int u) {
    if (par[u] == u) return u;
    return par[u] = find(par[u]);
  }
  int new_node(T w) {
    root = int(par.size());
    par.push_back(root);
    adj.emplace_back();
    wei.push_back(w);
    return root;
  }
  int unite(int u, int v, T w) {
    int p1 = find(u), p2 = find(v);
    if (p1 == p2) return -1;
    int node = new_node(w);
    par[p1] = par[p2] = node;
    adj[node].push_back(p1);
    adj[node].push_back(p2);
    return node;
  }
};
