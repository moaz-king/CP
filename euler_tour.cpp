int flat[2 * N], in[N], out[N], timer;
vector<vector<int>> adj;
void dfs(int u, int p) {
  in[u] = timer;
  flat[timer++] = u;
  for (int &v : adj[u]) {
    if (v == p) continue;
    dfs(v, u);
  }
  out[u] = timer;
  flat[timer++] = u;
}
