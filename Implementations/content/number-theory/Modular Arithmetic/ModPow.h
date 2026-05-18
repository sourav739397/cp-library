/**
 * Description: Computes a^p in O(log p) time using binary exponentiation
 * Time: O(\log P)
 * Source: KACTL
 */

int modPow(int a, int64_t p, const int mod) {
  if (p == 0) return 1;
  int res = modPow(a, p/2, mod); 
  res = (1ll*res*res) % mod;
  return p&1 ? (1ll*res*a) % mod : res;
}
