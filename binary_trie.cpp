struct TrieNode {
  int ch[2]{}, frq = 0, idx = INT_MIN;
  int& operator[](int x) { return ch[x]; }
};
struct BinaryTrie {
  vector<TrieNode> tr;
  const int M = 30;
  BinaryTrie() { newNode(); }
  int newNode() {
    tr.emplace_back();
    return sz(tr) - 1;
  }
  int size(int u) { return tr[u].frq; } // elements pass through node u
  int count(int x) {
    int u = 0;
    for (int i = M - 1; i >= 0; i--) {
      int bt = (x >> i) & 1;
      if (!size(tr[u][bt])) return 0;
      u = tr[u][bt];
    }
    return size(u);
  }
  void update(int x, int d, int id = 1) { // d = 1 to insert | d = -1 to delete
    if (d == -1 && !count(x)) return;
    int u = 0;
    tr[u].idx = max(tr[u].idx, id);
    for (int i = M - 1; i >= 0; i--) {
      int bt = x >> i & 1;
      if (!tr[u][bt]) tr[u][bt] = newNode();
      u = tr[u][bt];
      tr[u].idx = max(tr[u].idx, id);
      tr[u].frq += d;
    }
  }
  int less(int x, int k) {  // cnt of y ^ x < k
    int u = 0;
    int cnt = 0;
    for (int i = M - 1; i >= 0; i--) {
      int btk = (k >> i) & 1;
      int btx = (x >> i) & 1;
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
  pair<int64_t, int> greater(int x, int k) {  // {cnt of y ^ x >= k, last index}
    int u = 0;
    int64_t cnt = 0;
    int idx = INT_MIN;
    for (int i = M - 1; i >= 0; i--) {
      int btk = (k >> i) & 1;
      int btx = (x >> i) & 1;
      if (btk == 1) {
        u = tr[u][!btx];
      } else {
        int dif = tr[u][!btx];
        if (dif) {
          cnt += size(dif);
          idx = max(idx, tr[dif].idx);
        }
        u = tr[u][btx];
      }
      if (u == 0) break;
    }
    if (u != 0) {
      cnt += size(u);
      idx = max(idx, tr[u].idx);
    }
    return {cnt, idx};
  }
  int minXOR(int x) {
    int u = 0;
    int res = 0;
    for (int i = M - 1; i >= 0; i--) {
      int bt = x >> i & 1;
      if (size(tr[u][bt])) {
        u = tr[u][bt];
      } else {
        res |= (1 << i);
        u = tr[u][!bt];
      }
    }
    return res;
  }
  int maxXOR(int x) {
    int u = 0;
    int res = 0;
    for (int i = M - 1; i >= 0; i--) {
      int bt = (x >> i) & 1;
      if (size(tr[u][!bt])) {
        u = tr[u][!bt];
        res |= (1 << i);
      } else {
        u = tr[u][bt];
      }
    }
    return res;
  }
};
