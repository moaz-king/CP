using u64 = uint64_t;
using u128 = __uint128_t;

u64 power(u64 base, u64 exp, u64 mod) {
  u64 res = 1;
  base %= mod;
  while (exp > 0) {
    if (exp & 1) res = (u128)res * base % mod;
    base = (u128)base * base % mod;
    exp >>= 1;
  }
  return res;
}

bool millerRabin(u64 n, u64 a) {
  if (n % a == 0) return n == a;
  u64 d = n - 1;
  int r = 0;
  while (d % 2 == 0) {
    d /= 2;
    r++;
  }
  u64 x = power(a, d, n);
  if (x == 1 || x == n - 1) return true;
  for (int i = 1; i < r; ++i) {
    x = (u128)x * x % n;
    if (x == n - 1) return true;
  }
  return false;
}

// checks primality up to 3e24
bool isPrime(u64 n) {
  if (n < 2) return false;
  for (u64 p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
    if (n % p == 0) return n == p;
  }
  for (u64 a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
    if (!millerRabin(n, a)) return false;
  }
  return true;
}