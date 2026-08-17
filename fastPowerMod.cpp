int64_t MOD = 1e9 + 7;
int64_t fpm(int64_t b, int64_t p) {
  if (!p) return 1;
  int64_t x = fpm(b, p >> 1);
  x = (x % MOD) * (x % MOD) % MOD;
  return p & 1 ? (x % MOD) * (b % MOD) % MOD : x;
}
