template<typename T1, typename T2>
bool mpcomp(pair<T1, T2> p1, pair<T1, T2> p2) {
  return p1.second < p2.second;
}
