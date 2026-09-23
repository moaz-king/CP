struct TreeNode {
  int64_t sum{};
  TreeNode() { }
  TreeNode(int64_t x) { sum = x; }
  void operator=(const TreeNode &other) { sum = other.sum; }
};
struct LazyNode {
  int64_t sum{};
  LazyNode() { }
  LazyNode(int64_t x) { sum = x; }
  void operator=(const LazyNode &other) { sum = other.sum; }
  bool operator==(const LazyNode &other) const { return sum == other.sum; }
};
template <typename T, typename U, typename V, auto merge_q, auto merge_u, auto apply>
struct SegmentTree {
  int n;
  vector<T> tree;
  vector<V> lazy;
  inline int left(int node) { return node << 1; }
  inline int right(int node) { return node << 1 | 1; }
  void update(int l, int r, V val) { update(1, 0, n - 1, l, r, val); }
  T query(int l, int r) { return query(1, 0, n - 1, l, r); }
  SegmentTree() { }
  SegmentTree(const vector<U> &v) { build(v); }
  void build(const vector<U> &v) {
    n = int(v.size());
    tree.resize(4 * n, T());
    lazy.resize(4 * n, V());
    build(1, 0, n - 1, v);
  }
  void push(int node, int l, int r) {
    if (lazy[node] == V()) return;
    if (l < r) {
      lazy[left(node)] = merge_u(lazy[node], lazy[left(node)]);
      lazy[right(node)] = merge_u(lazy[node], lazy[right(node)]);
    }
    apply(tree[node], lazy[node], l, r);
    lazy[node] = V();
  }
  void build(int node, int l, int r, const vector<U> &v) {
    if (l == r) {
      tree[node] = T(v[l]);
      return;
    }
    int m = l + r >> 1;
    build(left(node), l, m, v);
    build(right(node), m + 1, r, v);
    tree[node] = merge_q(tree[left(node)], tree[right(node)]);
  }
  void update(int node, int l, int r, int lx, int rx, V &val) {
    push(node, l, r);
    if (l > rx || r < lx) return;
    if (l >= lx && r <= rx) {
      lazy[node] = merge_u(val, lazy[node]);
      push(node, l, r);
      return;
    }
    int m = l + r >> 1;
    update(left(node), l, m, lx, rx, val);
    update(right(node), m + 1, r, lx, rx, val);
    tree[node] = merge_q(tree[left(node)], tree[right(node)]);
  }
  T query(int node, int l, int r, int lx, int rx) {
    push(node, l, r);
    if (r < lx || l > rx) return T();
    if (l >= lx && r <= rx) return tree[node];
    int m = l + r >> 1;
    T l_ans = query(left(node), l, m, lx, rx);
    T r_ans = query(right(node), m + 1, r, lx, rx);
    return merge_q(l_ans, r_ans);
  }
};
inline TreeNode merge_q(const TreeNode &a, const TreeNode &b) {
  // merge queries.
}
inline LazyNode merge_u(const LazyNode &a, const LazyNode &b) {
  // a is the new lazy.
  // b is the already existed lazy.
  // merge updates.
}
inline void apply_u(TreeNode &a, LazyNode &b, int l, int r) {
  // apply lazy update to a tree node.
}
