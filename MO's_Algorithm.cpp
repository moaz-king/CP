constexpr int SQ = 450;

struct Query {
  int l, r, ind;

  Query() { l = r = -1; }
  Query(int l, int r, int i) : l(l), r(r), ind(i) { }

  bool operator<(const Query &other) const {
    if (l / SQ != other.l / SQ) {
      return l / SQ < other.l / SQ;
    }
    return (l / SQ) & 1 ? r > other.r : r < other.r;
  }
};

vector<int> MO(vector<Query> &que) {
  int q = que.size();
  vector<int> ans(q);
  sort(que.begin(), que.end());
  
  auto add = [&] (int i) {
    // add index i
  };
  auto rem = [&] (int i) {
    // remove index i
  };

  int l = 0, r = -1;
  for (auto [L, R, ind] : que) {
    while (r < R) add(++r);
    while (l > L) add(--l);
    while (r > R) rem(r--);
    while (l < L) rem(l++);
    ans[ind] = // get answer
  }
  return ans;
}
