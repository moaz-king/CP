template <typename T, typename U, auto merge>
struct SparseTable {
  int lg;
  vector<T> table;
  SparseTable() { }
  SparseTable(const vector<U> &v) { build(v); }
  inline T& at(int i, int j) { return table[i * lg + j]; }
  void build(const vector<U> &v) {
    int n = int(v.size());
    lg = __lg(n) + 1;
    table.assign(n * lg, T());
    for (int i = 0; i < n; i++) {
      at(i, 0) = T(v[i]);
    }
    for (int p = 1; p < lg; p++) {
      for (int i = 0; i <= n - (1 << p); i++) {
        at(i, p) = merge(at(i, p - 1), at(i + (1 << (p - 1)), p - 1));
      }
    }
  }
  T query(int l, int r) {
    int p = __lg(r - l + 1);
    return merge(at(l, p), at(r - (1 << p) + 1, p));
  }
};
inline int merge_q(const int &a, const int &b) {
  return min(a, b);
}
