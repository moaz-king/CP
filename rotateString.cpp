void operator<<=(string &s, int n) {
  string f = s + s;
  s = f.substr(n % s.length(), s.length());
}
void operator>>=(string &s, int n) {
  s <<= s.length() - (n % s.length());
}
