template <typename T>
vector<int> manacher_odd(T a) {
  int n = int(a.size());
  a.insert(a.begin(), 0);
  a.push_back(1);
  vector<int> p(n + 2);
  int l = 0, r = 1;
  for (int i = 1; i <= n; i++) {
    if (i <= r) {
      p[i] = min(r - i, p[l + (r - i)]);
    }
    while (a[i - p[i]] == a[i + p[i]]) {
      p[i]++;
    }
    if (i + p[i] > r) {
      l = i - p[i];
      r = i + p[i];
    }
  }
  for (int i = 1; i <= n; i++) {
    p[i] = (p[i] << 1) - 1;
  }
  return vector<int>(p.begin() + 1, p.end() - 1);
}
template <typename T>
vector<int> manacher(const T &a) {
  int n = int(a.size());
  vector<int> all;
  for (int i = 0; i < n; i++) {
    all.push_back(-1);
    all.push_back(a[i]);
  }
  all.push_back(-1);
  auto m(manacher_odd(all));
  for (int i = 0; i < int(m.size()); i++) {
    m[i] >>= 1;
  }
  return m;
}
