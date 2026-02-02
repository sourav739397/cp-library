/**
 * Description: coordinate compression, get index of x by counting
  * number of element less than x
 * Source: Benq
 * Time: O(N \log N)
 * Verification: LIS[https://cses.fi/problemset/task/1145/]
 */

template<class T> void compress(vector<T>& v) {
	ranges::sort(v);
  v.erase(unique(v.begin(), v.end()), v.end()); 
}
template<class T> int get(vector<T>& v, T x) { 
	return ranges::lower_bound(v, x) - begin(v);
}