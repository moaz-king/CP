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
  vector<int> left, right, roots;
  SegmentTree(int64_t L, int64_t R) : low(L), high(R) { }
  T query(int root, int l, int r) { return query(root, low, high, l, r); }
  int update(int root, int idx, U val) {
    int new_root = update(root, low, high, idx, val);
    roots.push_back(new_root);
    return new_root;
  }
  int new_node(T val, int l, int r) {
    tree.push_back(val);
    left.push_back(l);
    right.push_back(r);
    return int(tree.size()) - 1;
  }
  inline int getL(int node) { return node == -1 ? -1 : left[node]; }
  inline int getR(int node) { return node == -1 ? -1 : right[node]; }
  inline T getS(int node) { return node == -1 ? T() : tree[node]; }
  int update(int node, int l, int r, int idx, U &val) {
    if (l == r) return new_node(T(val), -1, -1);
    int m = l + r >> 1;
    int L = getL(node), R = getR(node);
    if (idx <= m) L = update(L, l, m, idx, val);
    else R = update(R, m + 1, r, idx, val);
    return new_node(merge(getS(L), getS(R)), L, R);
  }
  T query(int node, int l, int r, int lx, int rx) {
    if (node == -1) return T();
    if (l >= lx && r <= rx) return getS(node);
    int m = l + r >> 1;
    T l_ans = lx <= m ? query(getL(node), l, m, lx, rx) : T();
    T r_ans = rx > m ? query(getR(node), m + 1, r, lx, rx) : T();
    return merge(l_ans, r_ans);
  }
};
inline Node merge_q(const Node &a, const Node &b) {
  // merge queries
}
