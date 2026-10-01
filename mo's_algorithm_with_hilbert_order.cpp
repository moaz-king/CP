constexpr int lg = 21;

inline int64_t hilbertOrder(int x, int y, int pow, int rotate) {
  if (pow == 0) return 0;
  int hpow = 1 << (pow - 1);
  int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
  seg = (seg + rotate) & 3;
  const int rotateDelta[4] = {3, 0, 0, 1};
  int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
  int nrot = (rotate + rotateDelta[seg]) & 3;
  int64_t subSquareSize = int64_t(1) << (2 * pow - 2);
  int64_t ans = seg * subSquareSize;
  int64_t add = hilbertOrder(nx, ny, pow - 1, nrot);
  ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
  return ans;
}

struct Query {
  int l, r, ind;
  int64_t ord;

  Query() { }
  Query(int l, int r, int i) : l(l), r(r), ind(i) { calcOrder(); }

  inline void calcOrder() { ord = hilbertOrder(l, r, lg, 0); }
  bool operator<(const Query& other) const { return ord < other.ord; }
};

vector<int> MO(vector<Query>& que) {
  int q = que.size();
  vector<int> ans(q);
  sort(que.begin(), que.end());

  auto add = [&](int i) {
    // add index i
  };
  auto rem = [&](int i) {
    // remove index i
  };
  
  int l = 0, r = -1;
  for (auto [L, R, ind, ord] : que) {
    while (r < R) add(++r);
    while (l > L) add(--l);
    while (r > R) rem(r--);
    while (l < L) rem(l++);
    ans[ind] = // get answer
  }
  return ans;
}
