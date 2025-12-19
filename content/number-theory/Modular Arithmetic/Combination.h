/**
 * Description: Combinations modulo a prime $MOD$. Assumes $2\le N \le MOD$.
 * Time: O(N)
 * Source: KACTL
 * Verification: https://dmoj.ca/problem/tle17c4p5
 * Usage: F.C(6, 4); // 15
 */

constexpr int MOD = 1E9 + 7;
 
struct Combination {
	vector<int64_t> inv, fac, ifac;
	Combination(int N) {
		inv.resize(N), fac.resize(N), ifac.resize(N); 
		inv[1] = fac[0] = ifac[0] = 1; 
	  for (int i = 2; i < N; i++) 
      inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
		for (int i = 1; i < N; i++) {
      fac[i] = fac[i-1] * i % MOD;
      ifac[i] = ifac[i-1] * inv[i] % MOD;
    }
	}
	int C(int n, int r) {
    if (r < 0 || r > n) return 0;
    return (int)(fac[n] * ifac[r] % MOD * ifac[n - r] % MOD);
  }
};
Combination F(5<<18);