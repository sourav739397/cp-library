/**
 * Description: Factors integers.
 * Time: O(\sqrt N)
 * Source: Own
 * Verification: https://csacademy.com/contest/ceoi-2018-day-2/task/toys-big/
 */

inline namespace factorBasic {
template<class T> vector<pair<T,int>> factor(T x) { 
	vector<pair<T,int>> primes;
	for (T i = 2; i*i <= x; ++i) if (x % i == 0) {
		int t = 0;
		while (x % i == 0) x /= i, t++;
		primes.pb({i,t});
	}
	if (x > 1) primes.push_back({x,1});
	return primes;
}
/* Note:
 * number of operations needed s.t.
 *				  phi(phi(...phi(n)...))=1
 * is O(log n).
 * Euler's theorem: a^{\phi(p)}\equiv 1 (mod p), gcd(a,p)=1
 */
template<class T> T phi(T x) {
	for (auto& [pri, _]: factor(x)) x -= x / pri;
	return x;
}

template<class T> void tour(vector<pair<T, int>> &v, 
vector<T> &V, int ind, T cur) {
  if (ind == (int)size(v)) V.push_back(cur);
  else {
    T mul = 1;
    for (int i = 0; i <= v[ind].second; i++) {
      tour(v, V, ind + 1, cur * mul);
      mul *= v[ind].first;
    }
  }
}

template<class T> vector<T> getDiv(T x) {
  auto v = factor(x);
  vector<T> V;
  tour(v, V, 0, (T)1);
  ranges::sort(V);
  return V;
}
}