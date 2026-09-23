struct Node {
  vector<int> a;
  Node() { }
  Node(int x) { a.push_back(x); }
  void operator=(const Node other) { a = other.a; }
};
template <typename T, typename U, auto merge>
struct SegmentTree {
  int n;
  vector<T> tree;
  inline int left(int node) { return node << 1; }
  inline int right(int node) { return node << 1 | 1; }
  int query(int l, int r, int k) { return query(1, 0, n - 1, l, r, k); }
  SegmentTree() { }
  SegmentTree(const vector<U> &v) { build(v); }
  void build(const vector<U> &v) {
    n = int(v.size());
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
  int query(int node, int l, int r, int lx, int rx, int k) {
    if (r < lx || l > rx) return 0;
    if (l >= lx && r <= rx) {
      auto &v = tree[node].a;
      // count greater than or equal to k
      int it = lower_bound(v.begin(), v.end(), k) - v.begin();
      return int(v.size()) - it;
    }
    int m = l + r >> 1;
    int l_ans = query(left(node), l, m, lx, rx, k);
    int r_ans = query(right(node), m + 1, r, lx, rx, k);
    return l_ans + r_ans;
  }
};
inline Node merge_q(const Node &a, const Node &b) {
  Node res;
  int p1 = 0, p2 = 0;
  auto &A = a.a;
  auto &B = b.a;
  auto &C = res.a;
  int Al = int(A.size());
  int Bl = int(B.size());
  while (p1 < Al || p2 < Bl) {
    if (p1 < Al && p2 < Bl) {
      if (A[p1] < B[p2]) {
        C.push_back(A[p1++]);
      } else {
        C.push_back(B[p2++]);
      }
    } else if (p1 < Al) {
      C.push_back(A[p1++]);
    } else {
      C.push_back(B[p2++]);
    }
  }
  return res;
}
