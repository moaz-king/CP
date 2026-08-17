
// Big Integer Template
// https://codeforces.com/blog/entry/74200
struct big_int {
  string a;
  int sign;

  big_int() {}
  void operator=(string b) {
    a = (b[0] == '-' ? b.substr(1) : b);
    reverse(a.begin(), a.end());
    (*this).Remove0(b[0] == '-' ? -1 : 1);
  }
  big_int(string x) { (*this) = x; }
  big_int(int64_t x) { (*this) = to_string(x); }
  void operator=(int64_t x) { *this = to_string(x); }

  char operator[](int i) { return a[i]; }
  int size() { return a.size(); }
  big_int inverseSign() {
    sign *= -1;
    return (*this);
  }

  big_int Remove0(int newSign) {
    sign = newSign;
    for (int i = a.size() - 1; i > 0 && a[i] == '0'; i--) a.pop_back();
    if (a.size() == 1 && a[0] == '0') sign = 1;
    return (*this);
  }

  bool operator==(big_int x) { return sign == x.sign && a == x.a; }
  bool operator==(string x) { return *this == big_int(x); }
  bool operator==(int64_t x) { return *this == big_int(x); }
  bool operator!=(big_int x) { return !(*this == x); }
  bool operator!=(string x) { return !(*this == x); }
  bool operator!=(int64_t x) { return !(*this == x); }

  bool operator<(big_int b) {
    if (sign != b.sign) return sign < b.sign;
    if (a.size() != b.size()) return a.size() * sign < b.size() * sign;
    for (int i = a.size() - 1; i >= 0; i--)
      if (a[i] != b[i]) return a[i] < b[i];
    return false;
  }
  bool operator<(string x) { return *this < big_int(x); }
  bool operator<(int64_t x) { return *this < big_int(x); }
  bool operator<=(big_int b) { return *this == b || *this < b; }
  bool operator<=(string b) { return *this == b || *this < b; }
  bool operator<=(int64_t b) { return *this == b || *this < b; }
  bool operator>(big_int b) { return !(*this == b || *this < b); }
  bool operator>(string x) { return !(*this == x || *this < x); }
  bool operator>(int64_t b) { return !(*this == b || *this < b); }
  bool operator>=(big_int b) { return *this == b || *this > b; }
  bool operator>=(string b) { return *this == b || *this > b; }
  bool operator>=(int64_t b) { return *this == b || *this > b; }

  big_int operator+(big_int b) {
    if (sign != b.sign) return (*this) - b.inverseSign();
    big_int sum;
    for (int i = 0, carry = 0; i < a.size() || i < b.size() || carry; i++) {
      if (i < a.size()) carry += a[i] - '0';
      if (i < b.size()) carry += b[i] - '0';
      sum.a += (carry % 10 + 48);
      carry /= 10;
    }
    return sum.Remove0(sign);
  }
  big_int operator+(string x) { return *this + big_int(x); }
  big_int operator+(int64_t x) { return *this + big_int(x); }
  big_int operator++(int) {
    *this += 1;
    return *this - 1;
  }
  big_int operator++() {
    *this += 1;
    return *this;
  }
  void operator+=(big_int x) { *this = *this + x; }
  void operator+=(string x) { *this = *this + x; }
  void operator+=(int64_t x) { *this = *this + x; }

  big_int operator-(big_int b) {
    if (sign != b.sign) return (*this) + b.inverseSign();
    if (*this < b) return (b - *this).inverseSign();
    big_int sub;
    for (int i = 0, borrow = 0; i < a.size(); i++) {
      borrow = a[i] - borrow - (i < b.size() ? b.a[i] : '0');
      sub.a += borrow >= 0 ? borrow + '0' : borrow + 58;
      borrow = borrow >= 0 ? 0 : 1;
    }
    return sub.Remove0(sign);
  }
  big_int operator-(string x) { return *this - big_int(x); }
  big_int operator-(int64_t x) { return *this - big_int(x); }
  big_int operator--(int) {
    *this -= 1;
    return *this + 1;
  }
  big_int operator--() {
    *this -= 1;
    return *this;
  }
  void operator-=(big_int x) { *this = *this - x; }
  void operator-=(string x) { *this = *this - x; }
  void operator-=(int64_t x) { *this = *this - x; }

  big_int operator*(big_int b) {
    big_int mult("0");
    for (int i = 0, k = a[i]; i < a.size(); i++, k = a[i]) {
      while (k-- - '0') mult = mult + b;
      b.a.insert(b.a.begin(), '0');
    }
    return mult.Remove0(sign * b.sign);
  }
  big_int operator*(string x) { return *this * big_int(x); }
  big_int operator*(int64_t x) { return *this * big_int(x); }
  void operator*=(big_int x) { *this = *this * x; }
  void operator*=(string x) { *this = *this * x; }
  void operator*=(int64_t x) { *this = *this * x; }

  big_int operator/(big_int b) {
    if (b.size() == 1 && b[0] == '0') b.a[0] /= (b[0] - '0');
    big_int c("0"), d;
    for (int j = 0; j < a.size(); j++) d.a += "0";
    int dSign = sign * b.sign;
    b.sign = 1;
    for (int i = a.size() - 1; i >= 0; i--) {
      c.a.insert(c.a.begin(), '0');
      c = c + a.substr(i, 1);
      while (!(c < b)) c = c - b, d.a[i]++;
    }
    return d.Remove0(dSign);
  }
  big_int operator/(string x) { return *this / big_int(x); }
  big_int operator/(int64_t x) { return *this / big_int(x); }
  void operator/=(big_int x) { *this = *this / x; }
  void operator/=(string x) { *this = *this / x; }
  void operator/=(int64_t x) { *this = *this / x; }

  big_int operator%(big_int b) {
    if (b.size() == 1 && b[0] == '0') b.a[0] /= (b[0] - '0');
    big_int c("0");
    int cSign = sign * b.sign;
    b.sign = 1;
    for (int i = a.size() - 1; i >= 0; i--) {
      c.a.insert(c.a.begin(), '0');
      c = c + a.substr(i, 1);
      while (!(c < b)) c = c - b;
    }
    return c.Remove0(cSign);
  }
  big_int operator%(string x) { return *this % big_int(x); }
  big_int operator%(int64_t x) { return *this % big_int(x); }
  void operator%=(big_int x) { *this = *this % x; }
  void operator%=(string x) { *this = *this % x; }
  void operator%=(int64_t x) { *this = *this % x; }

  void print() {
    if (sign == -1) putchar('-');
    for (int i = a.size() - 1; i >= 0; i--) putchar(a[i]);
  }
  friend istream& operator>>(istream& in, big_int& x) {
    string s;
    in >> s;
    x = s;
    return in;
  }
  friend ostream& operator<<(ostream& out, big_int x) {
    if (x.sign == -1) out << '-';
    for (int i = x.size() - 1; i >= 0; i--) out << x[i];
    return out;
  }

  friend big_int pow(big_int base, big_int pw) {
    big_int ans = 1;
    while (pw != 0) {
      if (pw % 2 != 0) ans *= base;
      base *= base, pw /= 2;
    }
    return ans;
  }
  friend big_int pow(big_int a, big_int b, big_int mod) {
    if (b == 0) return big_int(1);
    big_int tmp = pow(a, b / 2, mod);
    if ((b % 2) == 0)
      return (tmp * tmp) % mod;
    else
      return (((tmp * tmp) % mod) * a) % mod;
  }
  friend big_int sqrt(big_int x) {
    big_int ans = x, tmp = (x + 1) / 2;
    while (tmp < ans) ans = tmp, tmp = (tmp + x / tmp) / 2;
    return ans;
  }
  friend big_int gcd(big_int a, big_int b) {
    return a % b == 0 ? b : gcd(b, a % b);
  }
  friend big_int lcm(big_int a, big_int b) { return a / gcd(a, b); }
};
