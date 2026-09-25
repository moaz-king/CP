auto primeFact(int64_t n) {
  map<int64_t, int64_t> mp;
  for (int64_t i = 2; i * i <= n; ++i) {
    while (n % i == 0) {
      n /= i;
      mp[i]++;
    }
  }
  if (n > 1) mp[n]++;
  return mp;
}
