/**
 * Description: Generalized Euclidean algorithm. \texttt{euclid} and 
 	* \texttt{invGeneral} work for $A,B<2^{62}$. 
 * Source: KACTL
 * Time: O(\log AB)
 * Verification: https://codeforces.com/gym/102411/problem/G
 */

pair<int64_t, int64_t> euclid(int64_t A, int64_t B) { // For A,B>=0, finds (x,y) s.t.
	// Ax+By=gcd(A,B), |Ax|,|By|<=AB/gcd(A,B)
	if (!B) return {1, 0};
	pair<int64_t, int64_t> p = euclid(B, A%B); 
  return {p.second, p.first-A/B*p.second}; 
}
int64_t invGeneral(int64_t A, int64_t B) { // find x in [0,B) such that Ax=1 mod B
	pair<int64_t, int64_t> p = euclid(A,B); 
  assert(p.first*A + p.second*B == 1);
	return p.first + (p.first<0)*B;  
} // must have gcd(A,B)=1