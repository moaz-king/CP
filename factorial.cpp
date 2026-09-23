vector<Mint> fact(1, 1);
vector<Mint> inv_fact(1, 1);
 
Mint nCr(int n, int r) {
  if (r < 0 || r > n) return 0;
  while (int(fact.size()) < n + 1) {
    fact.push_back(fact.back() * int(fact.size()));
    inv_fact.push_back(1 / fact.back());
  }
  return fact[n] * inv_fact[r] * inv_fact[n - r];
}

Mint nPr(int n, int r) {
  if (r < 0 || r > n) return 0;
  while (int(fact.size()) < n + 1) {
    fact.push_back(fact.back() * int(fact.size()));
    inv_fact.push_back(1 / fact.back());
  }
  return fact[n] * inv_fact[n - r];
}
