int64_t cum_xor(int64_t n) {
  short mod = n % 4;
  if (mod == 0) return n;
  if (mod == 1) return 1;
  if (mod == 2) return n + 1;
  return 0;
};

int64_t cum_xor(int64_t l, int64_t r) {
  return cum_xor(r) ^ (l > 0 ? cum_xor(l - 1) : 0);
};
