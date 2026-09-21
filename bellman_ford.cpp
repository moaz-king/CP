struct Edge {
  int u, v, weight;
};
bool bellmanFord(vector<Edge>& edges, int n, int src, vector<int>& dist) {
  int INF = 1e9;
  dist.assign(n, INF);
  dist[src] = 0;
  // Relax all edges n - 1 times
  for (int i = 0; i < n - 1; ++i) {
    for (auto &e : edges) {
      if (dist[e.u] != INF && dist[e.u] + e.weight < dist[e.v]) {
        dist[e.v] = dist[e.u] + e.weight;
      }
    }
  }
  // Check for negative-weight cycles
  for (auto& e : edges) {
    if (dist[e.u] != INF && dist[e.u] + e.weight < dist[e.v]) {
      return false;  // negative cycle detected
    }
  }
  return true;
}
