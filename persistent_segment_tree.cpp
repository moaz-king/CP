struct Node {
  int64_t sum{};
  Node() { }
  Node(int64_t x) { sum = x; }
  void operator=(const Node &other) { sum = other.sum; }
};

template <typename T, typename U, auto merge>
struct SegmentTree {
  int n;
  vector<T> tree;
  vector<int> left, right, roots;

  SegmentTree() {}
  SegmentTree(const vector<U> &v) { build(v); }

  T query(int root, int l, int r) { return query(root, 0, n - 1, l, r); }

  int update(int root, int idx, U val) {
    int new_root = update(root, 0, n - 1, idx, val);
    roots.push_back(new_root);
    return new_root;
  }

  int new_node(T val, int l, int r) {
    tree.push_back(val);
    left.push_back(l);
    right.push_back(r);
    return int(tree.size()) - 1;
  }

  void build(const vector<U> &v) {
    n = int(v.size());
    roots.push_back(build(0, n - 1, v));
  }

  int build(int l, int r, const vector<U> &v) {
    if (l == r) return new_node(T(v[l]), -1, -1);
    int m = l + r >> 1;
    int L = build(l, m, v);
    int R = build(m + 1, r, v);
    return new_node(merge(tree[L], tree[R]), L, R);
  }

  int update(int node, int l, int r, int idx, U &val) {
    if (l == r) return new_node(T(val), -1, -1);
    int m = l + r >> 1;
    int L = left[node], R = right[node];
    if (idx <= m) L = update(L, l, m, idx, val);
    else R = update(R, m + 1, r, idx, val);
    return new_node(merge(tree[L], tree[R]), L, R);
  }

  T query(int node, int l, int r, int lx, int rx) {
    if (node == -1) return T();
    if (l >= lx && r <= rx) return tree[node];
    int m = l + r >> 1;
    T l_ans = lx <= m ? query(left[node], l, m, lx, rx) : T();
    T r_ans = rx > m ? query(right[node], m + 1, r, lx, rx) : T();
    return merge(l_ans, r_ans);
  }
};

inline Node merge_q(const Node &a, const Node &b) {
  // merge queries
}
