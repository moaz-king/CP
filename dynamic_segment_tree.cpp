struct Node {
  int64_t sum{};
  Node() { }
  Node(int64_t x) { sum = x; }
  void operator=(const Node &other) { sum = other.sum; }
};

template <typename T, typename U, auto merge>
struct SegmentTree {
  int64_t low, high;
  vector<T> tree;
  vector<int> left, right;

  SegmentTree() {}
  SegmentTree(int64_t L, int64_t R) { init(L, R); }
  
  void init(int64_t L, int64_t R) {
    low = L, high = R;
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

  void update(int64_t idx, U val) { update(0, low, high, idx, val); }
  T query(int64_t l, int64_t r) { return query(0, low, high, l, r); }

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
