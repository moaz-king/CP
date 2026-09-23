template <typename T>
vector<int> kmp(const T &a) {
  int n = int(a.size());
  vector<int> pi(n);
  for (int i = 1; i < n; i++) {
    int j = pi[i - 1];
    while (j > 0 && a[i] != a[j]) {
      j = pi[j - 1];
    }
    if (a[i] == a[j]) j++;
    pi[i] = j;
  }
  return pi;
}
