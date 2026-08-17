int big[N], sz[N];
void pre(int u, int p) {
  sz[u] = 1;
  for (int v : adj[u]) {
    if (v == p) continue;
    pre(v, u);
    sz[u] += sz[v];
    if (!big[u] || sz[v] > sz[big[u]]) {
      big[u] = v;
    }
  }
}
void update(int x, int d) {
  if (d == 1) {
    // add node x
    return;
  }
  // remove node x
}
void add(int u, int p, int d) {
  update(u, d);
  for (int v : adj[u]) {
    if (v == p) continue;
    add(v, u, d);
  }
}
void dfs(int u, int p, bool keep) {
  for (int v : adj[u]) {
    if (v == p || v == big[u]) continue;
    dfs(v, u, 0);
  }
  if (big[u]) {
    dfs(big[u], u, 1);
  }
  update(u, 1);
  for (int v : adj[u]) {
    if (v == p || v == big[u]) continue;
    add(v, u, 1);
  }
  // get nodes's answer
  if (keep) return;
  add(u, p, -1);
}
