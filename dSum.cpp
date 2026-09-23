int64_t dSum(int64_t n) {
  int64_t sum = 0;
  while (n) {
    sum += n % 10;
    n /= 10;
  }
  return sum;
}
