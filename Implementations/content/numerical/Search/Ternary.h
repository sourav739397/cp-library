/**
 * Description: Ternary search to find the min of a unimodal function
 * Source: usaco.guide
 * Time: O(\log(N/eps))
 */

template<typename U> 
double Ternary(double lo, double hi, U f) {
	while (hi - lo > eps) {
		double l = lo + (hi - lo) / 3;
		double r = hi - (hi - lo) / 3;
		f(l) > f(r) ? lo = l : hi = r;
	}
	return lo;
}