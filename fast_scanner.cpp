struct FastScanner {
  static constexpr int BUFSIZE = 1 << 16;
  int idx = 0, size = 0;
  char buf[BUFSIZE];
  inline char readChar() {
    if (idx >= size) {
      size = (int)fread(buf, 1, BUFSIZE, stdin);
      idx = 0;
      if (size == 0) return 0;
    }
    return buf[idx++];
  }
  template <class T>
  bool nextInt(T& out) {
    char c = readChar();
    if (!c) return false;
    while (c <= ' ') {
      c = readChar();
      if (!c) return false;
    }
    bool neg = false;
    if (c == '-') {
      neg = true;
      c = readChar();
    }
    int64_t val = 0;
    while (c > ' ') {
      val = val * 10 + (c - '0');
      c = readChar();
    }
    out = neg ? (T)-val : (T)val;
    return true;
  }
  bool nextString(string& out) {
    out.clear();
    char c = readChar();
    if (!c) return false;
    while (c <= ' ') {
      c = readChar();
      if (!c) return false;
    }
    while (c > ' ') {
      out.push_back(c);
      c = readChar();
    }
    return true;
  }
};
