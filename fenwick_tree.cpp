template <typename T>
struct BIT {
  int n{};
  vector<T> tree;

  BIT() { }
  BIT(int sz) : n(sz + 5) { tree.assign(n, {}); }

  BIT(vector<int> &a) {
    n = int(a.size()) + 5;
    tree.assign(n, {});
    for (int i = 1; i <= int(a.size()); ++i) {
      tree[i] += a[i - 1];
      int r = i + (i & -i);
      if (r < n) tree[r] += tree[i];
    }
  }

  T query(int r) {
    T sum = 0;
    for (++r; r > 0; r -= r & -r) {
      sum += tree[r];
    }
    return sum;
  }

  T query(int l, int r) {
    return query(r) - query(l - 1);
  }

  // BIT must be monotonic.
  int lower_bound(T x) {
    int pos = 0;
    T sum = 0;
    for (int i = __lg(n); ~i; --i) {
      if (pos + (1 << i) < n && sum + tree[pos + (1 << i)] < x) {
        pos += 1 << i;
        sum += tree[pos];
      }
    }
    return pos;
  }

  void update(int i, T v) {
    for (++i; i < int(tree.size()); i += i & -i) {
      tree[i] += v;
    }
  }
};
