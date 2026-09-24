constexpr int N = 2e5 + 10;
bitset<N> compo;

void sieve(int n) {
  compo[0] = compo[1] = 1;
  for (int i = 2; i * i < n; i++) {
    if (compo[i]) continue;
    for (int j = i * i; j < n; j += i) {
      compo[j] = 1;
    }
  }
}
