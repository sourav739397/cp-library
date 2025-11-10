/**
 * Description: Binary search on continuous (floating-point) domain.
 * Source: Own
 * Verification: https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/B
 * Time: O(\log(precision))  — write 100 iterations and have a relax
 * Usage: int ans = realTrue()
 */

template<typename T, typename U>T realTrue(T lo, T hi, U f) {
  for (int i = 0; i < 100; ++i) {
    T mid = 0.5 * (hi + lo);
    f(mid) ? lo = mid : hi = mid;
  }
  return lo;
};