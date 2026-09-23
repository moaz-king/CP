using T = long double;
using point = complex<T>;
#define X real()
#define Y imag()

const T EPS = 1e-9;
const T PI = acosl(-1.0);

T dot(point a, point b) { return (conj(a) * b).real(); }

T cross(point a, point b) { return (conj(a) * b).imag(); }

T pointLineDistance(point a, point b, point p) {
  return fabsl(cross(b - a, p - a)) / abs(b - a);
}

T pointSegmentDistance(point a, point b, point p) {
  if (dot(b - a, p - a) < 0) return abs(p - a);
  if (dot(a - b, p - b) < 0) return abs(p - b);
  return pointLineDistance(a, b, p);
}

int orientation(point a, point b, point c) {
  T val = (b.X - a.X) * (c.Y - a.Y) - (b.Y - a.Y) * (c.X - a.X);
  if (fabsl(val) < EPS) return 0;
  return (val > 0 ? 1 : -1);
}

bool onSegment(point a, point b, point p) {
  return min(a.X, b.X) <= p.X && p.X <= max(a.X, b.X) && min(a.Y, b.Y) <= p.Y && p.Y <= max(a.Y, b.Y);
}

bool intersect(point a, point b, point c, point d) {
  int o1 = orientation(a, b, c);
  int o2 = orientation(a, b, d);
  int o3 = orientation(c, d, a);
  int o4 = orientation(c, d, b);
  if (o1 != o2 && o3 != o4) return true;
  if (o1 == 0 && onSegment(a, b, c)) return true;
  if (o2 == 0 && onSegment(a, b, d)) return true;
  if (o3 == 0 && onSegment(c, d, a)) return true;
  if (o4 == 0 && onSegment(c, d, b)) return true;
  return false;
}

T lineLineDistance(point a, point b, point c, point d) {
  if (a == b) {
    return pointSegmentDistance(c, d, a);
  } else if (c == d) {
    return pointSegmentDistance(a, b, c);
  }
  if (intersect(a, b, c, d)) return 0;
  T ans = pointSegmentDistance(a, b, c);
  ans = min(ans, pointSegmentDistance(a, b, d));
  ans = min(ans, pointSegmentDistance(c, d, a));
  ans = min(ans, pointSegmentDistance(c, d, b));
  return ans;
}
