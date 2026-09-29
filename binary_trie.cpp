struct TrieNode {
  int ch[2]{};
  int64_t fr{};
  int& operator[](int x) { return ch[x]; }
};

struct BinaryTrie {
  vector<TrieNode> tr;
  int64_t total = 0;
  int M;

  BinaryTrie(int M = 30, int n = 1) : M(M) {
    tr.reserve(1ll * n * M + 1);
    newNode();
  }

  int newNode() {
    tr.emplace_back();
    return int(tr.size()) - 1;
  }

  int64_t size(int u) { return tr[u].fr; }

  int64_t count(int64_t x) {
    int u = 0;
    for (int i = M - 1; ~i; --i) {
      int bt = x >> i & 1;
      if (!size(tr[u][bt])) return 0;
      u = tr[u][bt];
    }
    return size(u);
  }

  void update(int64_t x, int64_t d) {
    assert(x >> M == 0);
    if (d < 0 && count(x) < -d) return;
    total += d;
    int u = 0;
    for (int i = M - 1; ~i; --i) {
      int bt = x >> i & 1;
      if (!tr[u][bt]) {
        int v = newNode();
        tr[u][bt] = v;
      }
      u = tr[u][bt];
      tr[u].fr += d;
    }
  }

  void insert(int64_t x) { update(x, 1); }
  void erase(int64_t x) { update(x, -1); }

  int64_t less(int64_t x, int64_t k) {  // cnt of y ^ x < k
    if (k >> M) return total;
    int u = 0;
    int64_t cnt = 0;
    for (int i = M - 1; ~i; --i) {
      int btk = k >> i & 1;
      int btx = x >> i & 1;
      if (btk == 1) {
        int same = tr[u][btx];
        if (same) cnt += size(same);
        u = tr[u][!btx];
      } else {
        u = tr[u][btx];
      }
      if (u == 0) break;
    }
    return cnt;
  }

  int64_t greater_or_equal(int64_t x, int64_t k) {  // cnt of y ^ x >= k
    return total - less(x, k);
  }

  int64_t min_xor(int64_t x) {
    assert(total);
    int u = 0;
    int64_t res = 0;
    for (int i = M - 1; ~i; --i) {
      int bt = x >> i & 1;
      if (size(tr[u][bt])) {
        u = tr[u][bt];
      } else {
        res |= 1ll << i;
        u = tr[u][!bt];
      }
    }
    return res;
  }

  int64_t max_xor(int64_t x) {
    assert(total);
    int u = 0;
    int64_t res = 0;
    for (int i = M - 1; ~i; --i) {
      int bt = x >> i & 1;
      if (size(tr[u][!bt])) {
        u = tr[u][!bt];
        res |= 1ll << i;
      } else {
        u = tr[u][bt];
      }
    }
    return res;
  }
};