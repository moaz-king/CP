struct Node {
  int mn;
  Node() { mn = 0; }
  Node(int x) { mn = x; }
  void operator=(const Node other) { mn = other.mn; }
};
template <typename T, typename U, auto merge>
struct SparseTable {
  int n;
  vector<vector<T>> table;
  SparseTable() { }
  SparseTable(const vector<U> &v) { build(v); }
  void build(const vector<U> &v) {
    n = v.size();
    table = vector<vector<T>>(n, vector<T>(__lg(n) + 1));
    for (int i = 0; i < n; i++) {
      table[i][0] = T(v[i]);
    }
    for (int p = 1; p <= __lg(n); p++) {
      for (int i = 0; i <= n - (1 << p); i++) {
        table[i][p] = merge(table[i][p - 1], table[i + (1 << (p - 1))][p - 1]);
      }
    }
  }
  T query(int l, int r) {
    int p = __lg(r - l + 1);
    return merge(table[l][p], table[r - (1 << p) + 1][p]);
  }
};
inline Node merge_q(const Node &a, const Node &b) {
  return Node(min(a.mn, b.mn));
}
