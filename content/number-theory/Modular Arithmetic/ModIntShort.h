/**
 * Description: Modular arithmetic. Assumes $MOD$ is prime.
 * Source: KACTL
 * Verification: https://open.kattis.com/problems/modulararithmetic
 * Usage: Z a = MOD+5; inv(a); // 400000003
*/

struct Z {
  int v;
  static const int MOD = 1E9 + 7;
  explicit operator int() const { return v; }
  Z() : v(0) {}
  Z(int64_t _v) : v(int(_v % MOD)) { v += (v < 0) * MOD; }
  Z &operator+=(Z o) {
    if ((v += o.v) >= MOD) v -= MOD;
    return *this; }
  Z &operator-=(Z o) { 
    if ((v -= o.v) < 0) v += MOD;
    return *this; }
  Z &operator*=(Z o) {
    v = int((int64_t)v * o.v % MOD);
    return *this; }
  friend Z pow(Z a, int64_t p) {
    return p == 0 ? 1 : pow(a*a, p/2)*(p&1 ? a:1); }
  friend Z inv(Z a) {
    return pow(a, MOD - 2); }
  friend Z operator+(Z a, Z b) { return a += b; }
  friend Z operator-(Z a, Z b) { return a -= b; }
  friend Z operator*(Z a, Z b) { return a *= b; }
};