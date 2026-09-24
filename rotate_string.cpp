void operator<<=(string &s, int n) {
  if (int(s.length()) == 0) return;
  string f = s + s;
  s = f.substr(n % int(s.length()), int(s.length()));
}

void operator>>=(string &s, int n) {
  if (int(s.length()) == 0) return;
  s <<= int(s.length()) - (n % int(s.length()));
}