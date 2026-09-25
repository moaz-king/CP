struct XorBasis {
  static constexpr int B = 20;
  struct Node {
    int val = 0, pos = -1;
  };
  array<Node, B> b{};

  // inserts x (originally from index pos) into the basis
  void insert(int x, int pos) {
    for (int i = B - 1; ~i; --i) {
      if (!(x >> i & 1)) continue;
      if (!b[i].val) {
        b[i] = {x, pos};
        return;
      }
      if (b[i].pos < pos) {
        swap(b[i].val, x);
        swap(b[i].pos, pos);
      }
      x ^= b[i].val;
    }
  }

  // max subset-xor achievable using only elements with pos >= l
  int max_xor(int l) {
    int x = 0;
    for (int i = B - 1; ~i; --i) {
      if (b[i].pos >= l) {
        x = max(x, x ^ b[i].val);
      }
    }
    return x;
  }

  // min nonzero subset-xor achievable using only elements with pos >= l
  int min_xor(int l) {
    for (int i = 0; i < B; ++i) {
      if (b[i].pos >= l) return b[i].val;
    }
    return 0;
  }

  // checks whether x can be formed as a subset-xor of elements with pos >= l
  bool can_represent(int x, int l) {
    for (int i = B - 1; ~i; --i) {
      if (!(x >> i & 1)) continue;
      if (b[i].pos < l || !b[i].val) return false;
      x ^= b[i].val;
    }
    return x == 0;
  }

  // number of distinct subset-xor values (including 0) achievable using
  // elements with pos >= l
  int64_t count(int l) {
    int r = 0;
    for (int i = 0; i < B; ++i) {
      if (b[i].pos >= l) ++r;
    }
    return 1LL << r;
  }

  // number of independent basis vectors (dimension) with pos >= l
  int rank(int l) {
    int r = 0;
    for (int i = 0; i < B; ++i) {
      if (b[i].pos >= l) ++r;
    }
    return r;
  }

  // k-th smallest (0-indexed) achievable subset-xor value using elements with
  // pos >= l
  int kth_xor(int64_t k, int l) {
    vector<int> vecs;
    for (int i = 0; i < B; ++i) {
      if (b[i].pos >= l) vecs.push_back(b[i].val);
    }
    int x = 0;
    for (int i = 0; i < (int)vecs.size(); ++i) {
      if ((k >> i) & 1) x ^= vecs[i];
    }
    return x;
  }

  // max value of (t xor subset-xor) achievable using elements with pos >= l
  int max_xor_with(int t, int l) {
    int x = t;
    for (int i = B - 1; ~i; --i) {
      if (b[i].pos >= l && (x ^ b[i].val) > x) x ^= b[i].val;
    }
    return x;
  }

  // merges another basis into this one, preserving pos of each inserted vector
  void merge(const XorBasis& other) {
    for (int i = 0; i < B; ++i) {
      if (other.b[i].val) {
        insert(other.b[i].val, other.b[i].pos);
      }
    }
  }
};
