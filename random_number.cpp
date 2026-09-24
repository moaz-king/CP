mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int64_t rnd(int64_t l, int64_t r) { return uniform_int_distribution<int64_t>(l, r)(rng); }
