/**
 * Description: Combinations modulo a prime $MOD$. Assumes $2\le N \le MOD$.
 * Time: O(N)
 * Source: KACTL
 * Verification: https://dmoj.ca/problem/tle17c4p5
 * Usage: F.gen(100), F.C(6, 4); // 15
 */

struct {
  vector<int> inv, fac, ifac;
  void gen(int N) {
    inv.resize(N); fac.resize(N); ifac.resize(N);
    inv[1] = fac[0] = ifac[0] = 1;
    for (int i = 2; i < N; i++){
      inv[i] = int(MOD-(int64_t)MOD/i*inv[MOD%i]%MOD);
    }
    for (int i = 1; i < N; i++) {
			fac[i] = int((int64_t)fac[i-1]*i%MOD);
			ifac[i] = int((int64_t)ifac[i-1]*inv[i]%MOD);
    }
  }
  int P(int n, int r) { // nPr
    if (n < r || r < 0) return 0;
    return (int64_t)fac[n]*ifac[n-r]%MOD;
  }
  int C(int n, int r) { // nCr
    if (n < r || r < 0) return 0;
    return (int64_t)fac[n]*ifac[r]%MOD*ifac[n-r]%MOD; 
  }
} F;