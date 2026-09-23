template <class T>
struct Offline_2D_BIT {
  int sz{};
  bool ready{};
  vector<pair<int, int>> todo;
  vector<int> cnt, start, val;
  vector<T> bit;
  Offline_2D_BIT(int sz) : sz(sz), cnt(sz), start(sz) { }
  void init() {
    assert(!ready);
    ready = true;
    vector<int> last(sz, 0);
    fill(cnt.begin(), cnt.end(), 0);
    sort(todo.begin(), todo.end(), [](const auto &a, const auto &b) { return a.second < b.second; });
    for (auto [x, y] : todo) {
      for (; x < sz; x += x & -x) {
        if (last[x] != y) {
          last[x] = y;
          cnt[x]++;
        }
      }
    }
    int total = 0;
    for (int i = 0; i < sz; i++) {
      last[i] = 0;
      total += cnt[i];
      start[i] = total;
    }
    val.resize(total);
    bit.resize(total);
    reverse(todo.begin(), todo.end());
    for (auto [x, y] : todo) {
      for (; x < sz; x += x & -x) {
        if (last[x] != y) {
          last[x] = y;
          val[--start[x]] = y;
        }
      }
    }
  }
  int rank(int y, int l, int r) {
    return upper_bound(val.begin() + l, val.begin() + r, y) - val.begin() - l;
  }
  void updateNode(int x, int y, T d) {
    for (y = rank(y, start[x], start[x] + cnt[x]); y <= cnt[x]; y += y & -y) {
      bit[start[x] + y - 1] += d;
    }
  }
  void update(int x, int y, T d) {
    if (!ready) {
      todo.push_back({x, y});
    } else {
      for (; x < sz; x += x & -x) {
        updateNode(x, y, d);
      }
    }
  }
  T queryNode(int x, int y) {
    T res = 0;
    for (y = rank(y, start[x], start[x] + cnt[x]); y > 0; y -= y & -y) {
      res += bit[start[x] + y - 1];
    }
    return res;
  }
  T query(int x, int y) {
    assert(ready);
    T res = 0;
    for (; x > 0; x -= x & -x) {
      res += queryNode(x, y);
    }
    return res;
  }
  T query(int x1, int y1, int x2, int y2) {
    return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
  }
};
