struct Node {
  int cnt {};
};
struct Trie {
  int n {};
  vector<array<int, 26>> adj;
  vector<Node> a;
  Trie() { adj.emplace_back(), a.emplace_back(); }
  void insert(const string &s) {
    int node = 0;
    for (int i = 0; i < s.length(); i++) {
      if (adj[node][s[i] - 'a']) {
        node = adj[node][s[i] - 'a'];
        a[node]++;
      } else {
        n++;
        a.emplace_back();
        adj.emplace_back();
        adj[node][s[i] - 'a'] = n;
        node = n;
        a[node]++;
      }
    }
  }
  int count(const string &s) {
    int node = 0;
    for (int i = 0; i < s.length(); i++) {
      if (adj[node][s[i] - 'a']) {
        node = adj[node][s[i] - 'a'];
      } else {
        return 0;
      }
    }
    return a[node].cnt;
  }
};
