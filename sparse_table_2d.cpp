template <typename T, typename U, auto merge>
struct SparseTable_2D {
  int n, m, lg_n, lg_m;
  vector<T> table;

  SparseTable_2D() { }
  SparseTable_2D(const vector<vector<U>> &v) { build(v); }

  inline T& at(int i, int j, int k, int l) { return table[((i * m + j) * lg_n + k) * lg_m + l]; }

  void build(const vector<vector<U>> &v) {
    n = int(v.size());
    m = int(v[0].size());
    lg_n = __lg(n) + 1;
    lg_m = __lg(m) + 1;
    table.assign(n * m * lg_n * lg_m, T());
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        at(i, j, 0, 0) = T(v[i][j]);
      }
    }
    for (int p = 1; p < lg_n; ++p) {
      for (int i = 0; i <= n - (1 << p); ++i) {
        for (int j = 0; j < m; ++j) {
          at(i, j, p, 0) = merge(at(i, j, p - 1, 0), at(i + (1 << (p - 1)), j, p - 1, 0));
        }
      }
    }
    for (int p = 1; p < lg_m; ++p) {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= m - (1 << p); ++j) {
          at(i, j, 0, p) = merge(at(i, j, 0, p - 1), at(i, j + (1 << (p - 1)), 0, p - 1));
        }
      }
    }
    for (int pn = 1; pn < lg_n; ++pn) {
      for (int pm = 1; pm < lg_m; ++pm) {
        for (int i = 0; i <= n - (1 << pn); ++i) {
          for (int j = 0; j <= m - (1 << pm); ++j) {
            at(i, j, pn, pm) = merge(
              merge(at(i, j, pn - 1, pm - 1), at(i + (1 << (pn - 1)), j, pn - 1, pm - 1)),
              merge(at(i, j + (1 << (pm - 1)), pn - 1, pm - 1), at(i + (1 << (pn - 1)), j + (1 << (pm - 1)), pn - 1, pm - 1))
            );
          }
        }
      }
    }
  }

  T query(int x1, int y1, int x2, int y2) {
    int pn = __lg(x2 - x1 + 1);
    int pm = __lg(y2 - y1 + 1);
    return merge(
      merge(at(x1, y1, pn, pm), at(x2 - (1 << pn) + 1, y1, pn, pm)),
      merge(at(x1, y2 - (1 << pm) + 1, pn, pm), at(x2 - (1 << pn) + 1, y2 - (1 << pm) + 1, pn, pm))
    );
  }
};

inline int merge_q(const int &a, const int &b) {
  return min(a, b);
}
