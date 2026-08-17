int64_t power(int64_t base, int64_t exp, int64_t mod) {
  int64_t res = 1;
  base %= mod;
  while (exp > 0) {
    if (exp % 2 == 1) res = (__int128_t)res * base % mod;
    base = (__int128_t)base * base % mod;
    exp /= 2;
  }
  return res;
}
bool MillerRabin(int64_t n, int a) {
  if (n % a == 0) return false;
  int64_t d = n - 1;
  int s = 0;
  while (d % 2 == 0) {
    d /= 2;
    s++;
  }
  int64_t x = power(a, d, n);
  if (x == 1 || x == n - 1) return true;
  for (int r = 1; r < s; r++) {
    x = (__int128_t)x * x % n;
    if (x == n - 1) return true;
  }
  return false;
}
bool isPrime(int64_t n) {
  if (n <= 1) return false;
  if (n <= 3) return true;
  if (n % 2 == 0 || n % 3 == 0) return false;
  int bases[] = {2, 7, 61};
  for (int a : bases) {
    if (n == a) return true;
    if (!MillerRabin(n, a)) return false;
  }
  return true;
}
