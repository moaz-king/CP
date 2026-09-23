void Assert(bool f, int code) {
  if (!f) {
    cerr << "Assertion: " << code << " failed.\n";
    exit(code);
  }
}
