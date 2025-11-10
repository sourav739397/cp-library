/**
 * Description: Finds the first value x in [lo, hi] such that predicate f(x) is true.
 * Source: Benq
 * Verification: 
 * Time: O(\log(hi - lo))
 * Usage: int ans = fstTrue()
 */

template<typename T, typename U> T fstTrue(T lo, T hi, U f) {
  ++hi;
  assert(lo <= hi);
  while (lo < hi) {
    T mid = lo + (hi - lo) / 2;
    f(mid) ? hi = mid : lo = mid + 1;
  }
  return lo;
};