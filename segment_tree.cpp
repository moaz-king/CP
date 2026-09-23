struct Node {
  int64_t sum;
  Node() { sum = 0; }
  Node(int64_t x) { sum = x; }
  void operator=(const Node other) { sum = other.sum; }
};
template <typename T, typename U, auto merge>
struct SegmentTree {
  int n;
  vector<T> tree;
  inline int left(int node) { return node << 1; }
  inline int right(int node) { return node << 1 | 1; }
  void update(int idx, U val) { update(1, 0, n - 1, idx, val); }
  T query(int l, int r) { return query(1, 0, n - 1, l, r); }
  SegmentTree() { }
  SegmentTree(const vector<U> &v) { build(v); }
  void build(const vector<U> &v) {
    n = v.size();
    tree.resize(n << 2, T());
    build(1, 0, n - 1, v);
  }
  void build(int node, int l, int r, const vector<U> &v) {
    if (l == r) {
      tree[node] = T(v[l]);
      return;
    }
    int m = l + r >> 1;
    build(left(node), l, m, v);
    build(right(node), m + 1, r, v);
    tree[node] = merge(tree[left(node)], tree[right(node)]);
  }
  void update(int node, int l, int r, int idx, U &val) {
    if (l == r) {
      tree[node] = T(val);
      return;
    }
    int m = l + r >> 1;
    if (idx <= m) {
      update(left(node), l, m, idx, val);
    } else {
      update(right(node), m + 1, r, idx, val);
    }
    tree[node] = merge(tree[left(node)], tree[right(node)]);
  }
  T query(int node, int l, int r, int lx, int rx) {
    if (l >= lx && r <= rx) return tree[node];
    int m = l + r >> 1;
    T l_ans = lx <= m ? query(left(node), l, m, lx, rx) : T();
    T r_ans = rx > m ? query(right(node), m + 1, r, lx, rx) : T();
    return merge(l_ans, r_ans);
  }
};
inline Node merge_q(const Node &a, const Node &b) {
  // merge queries
}
