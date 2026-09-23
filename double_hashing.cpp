mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int64_t rnd(int64_t l, int64_t r) { return uniform_int_distribution<int64_t>(l, r)(rng); }
const int64_t MOD1 = 1e9 + 7;
const int64_t MOD2 = 1e9 + 9;
const int64_t base1 = rnd(0.25 * MOD1, 0.75 * MOD1);
const int64_t base2 = rnd(0.25 * MOD1, 0.75 * MOD1);
struct HashedString {
  int64_t n{};
  vector<int64_t> hash1, hash2, pw1, pw2;
  HashedString() {
    hash1.emplace_back();
    hash2.emplace_back();
    pw1.push_back(1);
    pw2.push_back(1);
  }
  HashedString(const string &s) {
    hash1.emplace_back();
    hash2.emplace_back();
    pw1.push_back(1);
    pw2.push_back(1);
    build(s);
  }
  void build(const string &s) {
    for (int i = 0; i < int(s.length()); i++) {
      push_back(s[i]);
    }
  }
  void push_back(char c) {
    hash1.push_back((hash1.back() * base1 + c) % MOD1);
    pw1.push_back(pw1.back() * base1 % MOD1);
    hash2.push_back((hash2.back() * base2 + c) % MOD2);
    pw2.push_back(pw2.back() * base2 % MOD2);
    ++n;
  }
  pair<int64_t, int64_t> get(int l, int r) {
    auto h1 = (hash1[r + 1] - (hash1[l] * pw1[r - l + 1] % MOD1) + MOD1) % MOD1;
    auto h2 = (hash2[r + 1] - (hash2[l] * pw2[r - l + 1] % MOD2) + MOD2) % MOD2;
    return make_pair(h1, h2);
  }
};
