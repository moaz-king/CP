string dectobin(int64_t n) {
  if (!n) {
    return "0";
  }
  string s = bitset<64>(n).to_string();
  return s.substr(s.find_first_not_of('0'));
}
