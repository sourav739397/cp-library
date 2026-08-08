/**
 * Description: Modular arithmetic. Assumes $MOD$ is prime.
 * Source: KACTL
 * Verification: https://open.kattis.com/problems/modulararithmetic
 * Usage: mint a = MOD+5; inv(a); // 400000003
*/

struct mint {
	inline static int MOD = 1e9 + 7;
	int v; explicit operator int() const { return v; }
	mint() : v(0) {}
	mint(int64_t _v) : v(int(_v % MOD)) { v += (v<0)*MOD; }
	mint& operator+=(mint o) {
		if ((v += o.v) >= MOD) v -= MOD;
		return *this; }
	mint& operator-=(mint o) {
		if ((v -= o.v) < 0) v += MOD;
		return *this; }
	mint& operator*=(mint o) {
		v = int((int64_t)v*o.v % MOD);
		return *this; }
	friend mint pow(mint o, int64_t p) {
		mint ans = 1;
		for (; p; p /= 2, o *= o) if (p&1) ans *= o;
		return ans; }
	friend mint inv(mint o) {
		return pow(o, MOD - 2); }
	friend mint operator+(mint a, const mint& b) { return a += b; }
	friend mint operator-(mint a, const mint& b) { return a -= b; }
	friend mint operator*(mint a, const mint& b) { return a *= b; }
};