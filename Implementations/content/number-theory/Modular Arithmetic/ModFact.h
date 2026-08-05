/**
 * Description: Combinations modulo a prime $MOD$. Assumes $2\le N \le MOD$.
 * Time: O(N)
 * Source: KACTL
 * Verification: https://dmoj.ca/problem/tle17c4p5
 * Usage: F.init(10); F.C(6, 4); // 15
 */

#include "ModIntShort.h"

struct {
	vector<mint> invs, fac, ifac;
	void init(int N) {
		fac.resize(N, 1); invs.resize(N); ifac.resize(N);
		for (int i = 1; i < N; i++) fac[i] = fac[i-1] * i;
		ifac[N-1] = inv(fac[N-1]);
		for (int i = N-1; i > 0; i--) {
			ifac[i-1] = ifac[i] * i;
			invs[i] = ifac[i] * fac[i-1];
		}
	}
	mint C(int n, int r) { // nCr
		if (n < r || r < 0) return 0;
		return fac[n]*ifac[r]*ifac[n-r];
	}
	mint P(int n, int r) { // nPr
		if (n < r || r < 0) return 0;
		return fac[n]*ifac[n-r];
	}
} F;