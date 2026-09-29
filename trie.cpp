struct TrieNode {
  int ch[26]{}, cnt{}, ed{};
  int& operator[](int x) { return ch[x]; }
};

struct Trie {
  vector<TrieNode> tr;

  Trie() { new_node(); }

  int new_node() {
    tr.emplace_back();
    return int(tr.size()) - 1;
  }

  void update(const string &s, int d) {
    int u = 0;
    tr[u].cnt += d;
    for (char c : s) {
      int idx = c - 'a';
      if (!tr[u][idx]) {
        int v = new_node();
        tr[u][idx] = v;
      }
      u = tr[u][idx];
      tr[u].cnt += d;
    }
    tr[u].ed += d;
  }

  void insert(const string &s) { update(s, 1); }

  bool erase(const string &s) {
    int end = find(s);
    if (end == -1 || tr[end].ed == 0) return false;
    update(s, -1);
    return true;
  }

  int count_word(const string &s) {
    int u = find(s);
    return u == -1 ? 0 : tr[u].ed;
  }

  int count_pfx(const string &s) {
    int u = find(s);
    return u == -1 ? 0 : tr[u].cnt;
  }

  int find(const string &s) {
    int u = 0;
    for (char c : s) {
      int idx = c - 'a';
      if (!tr[u][idx]) return -1;
      u = tr[u][idx];
    }
    return u;
  }
};