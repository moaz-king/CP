template <typename T>
vector<int> Z_function(const T &a) {
  int n = int(a.size());
  vector<int> Z(n);
  int l = 0, r = 0;
  for (int i = 1; i < n; i++) {
    if (i <= r) {
      Z[i] = min(r - i, Z[i - l]);
    }
    while (i + Z[i] < n && a[Z[i]] == a[i + Z[i]]) {
      Z[i]++;
    }
    if (i + Z[i] > r) {
      l = i;
      r = i + Z[i];
    }
  }
  return Z;
}
