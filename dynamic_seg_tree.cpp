struct Node {
  int64_t sum;
  Node() { sum = 0; }
  Node(int64_t x) { sum = x; }
  void operator=(const Node other) { sum = other.sum; }
};
template <typename T, typename U, auto merge>
struct DynamicSegmentTree {
  int64_t lo, hi;
  vector<T> tree;
  vector<int> left, right;
  DynamicSegmentTree() {}
  DynamicSegmentTree(int64_t lo_, int64_t hi_) { init(lo_, hi_); }
  void init(int64_t lo_, int64_t hi_) {
    lo = lo_, hi = hi_;
    tree.assign(1, T());
    left.assign(1, -1);
    right.assign(1, -1);
  }
  int new_node() {
    tree.push_back(T());
    left.push_back(-1);
    right.push_back(-1);
    return int(tree.size()) - 1;
  }
  void update(int64_t idx, U val) { update(0, lo, hi, idx, val); }
  T query(int64_t l, int64_t r) { return query(0, lo, hi, l, r); }
  void update(int node, int64_t l, int64_t r, int64_t idx, U& val) {
    if (l == r) {
      tree[node] = T(val);
      return;
    }
    int64_t m = l + r >> 1;
    if (idx <= m) {
      if (left[node] == -1) left[node] = new_node();
      update(left[node], l, m, idx, val);
    } else {
      if (right[node] == -1) right[node] = new_node();
      update(right[node], m + 1, r, idx, val);
    }
    T l_val = left[node] == -1 ? T() : tree[left[node]];
    T r_val = right[node] == -1 ? T() : tree[right[node]];
    tree[node] = merge(l_val, r_val);
  }
  T query(int node, int64_t l, int64_t r, int64_t lx, int64_t rx) {
    if (node == -1) return T();
    if (l >= lx && r <= rx) return tree[node];
    int64_t m = l + r >> 1;
    T l_ans = lx <= m ? query(left[node], l, m, lx, rx) : T();
    T r_ans = rx > m ? query(right[node], m + 1, r, lx, rx) : T();
    return merge(l_ans, r_ans);
  }
};
inline Node merge_q(const Node& a, const Node& b) {
  // merge queries
}
