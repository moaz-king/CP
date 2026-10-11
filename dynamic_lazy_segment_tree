struct TreeNode {
  int64_t sum{};
  TreeNode() { }
  TreeNode(int64_t x) { sum = x; }
  void operator=(const TreeNode &other) { memcpy(this, &other, sizeof other); }
};

struct LazyNode {
  int64_t sum{};
  LazyNode() { }
  LazyNode(int64_t x) { sum = x; }
  void operator=(const LazyNode &other) { memcpy(this, &other, sizeof other); }
  bool operator==(const LazyNode &other) const { return sum == other.sum; }
};

template <typename T, typename U, typename V, auto merge_q, auto merge_u, auto apply>
struct SegmentTree {
  int64_t low, high;
  vector<T> tree;
  vector<V> lazy;
  vector<int> left, right;

  SegmentTree() { }
  SegmentTree(int64_t L, int64_t R) { init(L, R); }

  void init(int64_t L, int64_t R) {
    low = L, high = R;
    tree.assign(1, T());
    lazy.assign(1, V());
    left.assign(1, -1);
    right.assign(1, -1);
  }

  int new_node() {
    tree.push_back(T());
    lazy.push_back(V());
    left.push_back(-1);
    right.push_back(-1);
    return int(tree.size()) - 1;
  }

  void update(int64_t l, int64_t r, V val) { update(0, low, high, l, r, val); }
  T query(int64_t l, int64_t r) { return query(0, low, high, l, r); }

  void push(int node, int64_t l, int64_t r) {
    if (lazy[node] == V()) return;
    if (l < r) {
      if (left[node] == -1) {
        int c = new_node();
        left[node] = c;
      }
      if (right[node] == -1) {
        int c = new_node();
        right[node] = c;
      }
      int lc = left[node], rc = right[node];
      lazy[lc] = merge_u(lazy[node], lazy[lc]);
      lazy[rc] = merge_u(lazy[node], lazy[rc]);
    }
    apply(tree[node], lazy[node], l, r);
    lazy[node] = V();
  }

  void update(int node, int64_t l, int64_t r, int64_t lx, int64_t rx, V &val) {
    push(node, l, r);
    if (l > rx || r < lx) return;
    if (l >= lx && r <= rx) {
      lazy[node] = merge_u(val, lazy[node]);
      push(node, l, r);
      return;
    }
    int64_t m = l + r >> 1;
    update(left[node], l, m, lx, rx, val);
    update(right[node], m + 1, r, lx, rx, val);
    tree[node] = merge_q(tree[left[node]], tree[right[node]]);
  }

  T query(int node, int64_t l, int64_t r, int64_t lx, int64_t rx) {
    if (node == -1) return T();
    push(node, l, r);
    if (r < lx || l > rx) return T();
    if (l >= lx && r <= rx) return tree[node];
    int64_t m = l + r >> 1;
    T l_ans = query(left[node], l, m, lx, rx);
    T r_ans = query(right[node], m + 1, r, lx, rx);
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

inline void apply_u(TreeNode &a, LazyNode &b, int64_t l, int64_t r) {
  // apply lazy update to a tree node.
}