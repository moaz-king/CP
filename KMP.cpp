template <typename T>
vector<int> kmp(const T &a) {
  int n = int(a.size());
  vector<int> pi(n);
  for (int i = 1; i < n; ++i) {
    int j = pi[i - 1];
    while (j > 0 && a[i] != a[j]) {
      j = pi[j - 1];
    }
    if (a[i] == a[j]) ++j;
    pi[i] = j;
  }
  return pi;
}

template <typename T>
vector<vector<int>> kmp_automaton(const T &a) {
  int n = int(a.size());
  vector aut(n + 1, vector<int>(26));

  if (n == 0) return aut;

  aut[0][a[0] - 'a'] = 1;
  int x = 0;

  for (int i = 1; i <= n; ++i) {
    for (int c = 0; c < 26; ++c) {
      if (i < n && c == a[i] - 'a') {
        aut[i][c] = i + 1;
      } else {
        aut[i][c] = aut[x][c];
      }
    }
    if (i < n) x = aut[x][a[i] - 'a'];
  }

  return aut;
}