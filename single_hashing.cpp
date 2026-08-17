mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int64_t rnd(int64_t l, int64_t r) { return uniform_int_distribution<int64_t>(l, r)(rng); }
const uint64_t base = rnd(1e6, 1e9);
struct HashedString {
  int64_t n {};
  vector<uint64_t> hsh, pw;
  HashedString() {
    hsh.emplace_back();
    pw.push_back(1);
  }
  HashedString(const string &s) {
    hsh.emplace_back();
    pw.push_back(1);
    build(s);
  }
  void build(const string &s) {
    for (int i = 0; i < int(s.length()); i++) {
      push_back(s[i]);
    }
  }
  void push_back(char c) {
    hsh.push_back(hsh.back() * base + c);
    pw.push_back(pw.back() * base);
    ++n;
  }
  uint64_t get(int l, int r) {
    return hsh[r + 1] - hsh[l] * pw[r - l + 1];
  }
};
