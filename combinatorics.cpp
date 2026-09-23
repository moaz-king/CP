int64_t nCr(int64_t n, int64_t r) {
  if (r > n || r < 0) {
    return 0;
  }
  if (r > n - r) {
    r = n - r;
  }
  int64_t res = 1;
  for (int i = 0; i < r; i++) {
    res *= (n - i);
    res /= (i + 1);
  }
  return res;
}
int64_t nPr(int64_t n, int64_t r) {
  if (r > n || r < 0) {
    return 0;
  }
  int64_t res = 1;
  for (int i = 0; i < r; i++) {
    res *= n - i;
  }
  return res;
}
