vector<short> spf(N);
for (int i = 2; i * i < N; i++) {
  if (spf[i]) continue;
  for (int j = i * i; j < N; j += i) {
    if (!spf[j]) spf[j] = i;
  }
}
