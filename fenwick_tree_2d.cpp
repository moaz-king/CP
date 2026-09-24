template <typename T>
struct BIT_2D {
  int n{}, m{};
  vector<T> tree;

  BIT_2D(int x, int y) : n(x + 2), m(y + 2), tree(n * m) { }

  inline T& at(int i, int j) { return tree[i * m + j]; }

  void update(int x, int y, T d) {
    ++x, ++y;
    assert(x >= 0 && x < n - 1);
    assert(y >= 0 && y < m - 1);
    for (int i = x; i < n; i += i & -i) {
      for (int j = y; j < m; j += j & -j) {
        at(i, j) += d;
      }
    }
  }

  T query(int x, int y) {
    ++x, ++y;
    assert(x >= 0 && x < n - 1);
    assert(y >= 0 && y < m - 1);
    T sum = 0;
    for (int i = x; i; i -= i & -i) {
      for (int j = y; j; j -= j & -j) {
        sum += at(i, j);
      }
    }
    return sum;
  }

  T query(int x1, int y1, int x2, int y2) {
    return query(x2, y2) - query(x2, y1 - 1) - query(x1 - 1, y2) + query(x1 - 1, y1 - 1);
  }
};
