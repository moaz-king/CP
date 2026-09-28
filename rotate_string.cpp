template <typename T>
void operator<<=(T &a, int n) {
  int sz = int(a.size());
  if (sz == 0) return;
  T f(a);
  f.insert(f.begin(), a.begin(), a.end());
  int ind = n % sz;
  a = T(f.begin() + ind, f.begin() + ind + sz);
}

template <typename T>
void operator>>=(T &a, int n) {
  int sz = int(a.size());
  if (sz == 0) return;
  a <<= sz - (n % sz);
}