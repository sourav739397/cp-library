/**
 * Description: Finds the last value x in [lo, hi] such that predicate f(x) is true.
 * Source: Benq
 * Verification: 
 * Time: O(\log(hi - lo))
 * Usage: int ans = fstTrue()
 */

template<typename T, typename U> T lstTrue(T lo, T hi, U f) {
  --lo;
  assert(lo <= hi);
  while (lo < hi) {
    T mid = lo + (hi - lo + 1) / 2;
    f(mid) ? lo = mid : hi = mid - 1;
  }
  return lo;
};