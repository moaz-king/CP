int64_t fp(int64_t b, int64_t p) {
  if (!p) return 1;
  int64_t hp = fp(b, p >> 1);
  int64_t f = hp * hp;
  return p & 1 ? f * b : f;
}
