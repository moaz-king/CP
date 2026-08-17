vector<short> spf($1 + 10);
for (int i = 2; i * i <= $1; i++) {
  if (spf[i]) continue;
  for (int j = i * i; j <= $1; j += i) {
    if (!spf[j]) {
      spf[j] = i;
    }
  }
}
