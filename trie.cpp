struct TrieNode {
  int ch[26]{}, cnt{}, ed{};
  int& operator[](int x) { return ch[x]; }
};
struct Trie {
  vector<TrieNode> tr;
  Trie() { tr.emplace_back(); }
  int newNode() {
    tr.emplace_back();
    return int(tr.size()) - 1;
  }
  void insert(const string &s) {
    int node = 0;
    tr[node].cnt++;
    for (char c : s) {
      int idx = c - 'a';
      if (!tr[node][idx]) {
        tr[node][idx] = newNode();
      }
      node = tr[node][idx];
      tr[node].cnt++;
    }
    tr[node].ed++;
  }
  bool erase(const string &s) {
    int end = find(s);
    if (end == -1 || tr[end].ed == 0) return false;
    int node = 0;
    tr[node].cnt--;
    for (char c : s) {
      int idx = c - 'a';
      node = tr[node][idx];
      tr[node].cnt--;
    }
    tr[node].ed--;
    return true;
  }
  int count_word(const string &s) {
    int node = find(s);
    return node == -1 ? 0 : tr[node].ed;
  }
  int count_pfx(const string &s) {
    int node = find(s);
    return node == -1 ? 0 : tr[node].cnt;
  }
  int find(const string &s) {
    int node = 0;
    for (char c : s) {
      int idx = c - 'a';
      if (!tr[node][idx]) return -1;
      node = tr[node][idx];
    }
    return node;
  }
};