Mint fact[N], inv_fact[N];
void pre_fact(int n) {
  fact[0] = 1;
  for (int i = 1; i < n; i++) {
    fact[i] = fact[i - 1] * i;
  }
  inv_fact[n - 1] = (Mint)1 / fact[n - 1];
  for (int i = n - 2; i >= 0; i--) {
    inv_fact[i] = inv_fact[i + 1] * (i + 1);
  }
}
Mint nCr(int64_t n, int64_t r) {
  if (n < 0 || r > n) return 0;
  return fact[n] * inv_fact[n - r] * inv_fact[r];
}
Mint nPr(int64_t n, int64_t r) {
  if (n < 0 || r > n) return 0;
  return fact[n] * inv_fact[n - r];
}
