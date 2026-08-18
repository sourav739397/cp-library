/**
 * Description: Each node stores the sorted elements of its segment.
 	* \texttt{op} performs a query on a sorted node vector, allowing
 	* binary-search-based operations such as counting elements in a
 	* value range, finding the number of elements below/above a value, etc.
 * Time: O(N \log N) build, O(\log^2 N) query
 * Source: KACTL
 * Verification: https://cses.fi/problemset/task/3163
*/

template<class T> struct MergeSortTree {
	int op(const vector<T>& v, T x, T y) {
		return ranges::upper_bound(v, y) - ranges::lower_bound(v, x);
	}
	int N = 1;
	vector<vector<T>> seg;
	MergeSortTree(int _N) {
		while (N < _N) N *= 2;
		seg.resize(2*N);
	}
	void pull(int p) {
		merge(
			seg[2*p].begin(), seg[2*p].end(),
			seg[2*p+1].begin(), seg[2*p+1].end(),
			back_inserter(seg[p])
		);
	}
	void build(const vector<T>& v) {
		for (int i = 0; i < (int)v.size(); i++) {
			seg[i+N] = {v[i]};
		}
		for (int i = N-1; i > 0; i--) pull(i);
	}
	int query(int l, int r, T x, T y) { // zero-indexed, inclusive
		int ans = 0;
		for (l += N, r += N+1; l < r; l /= 2, r /= 2) {
			if (l & 1) ans += op(seg[l++], x, y);
			if (r & 1) ans += op(seg[--r], x, y);
		}
		return ans;
	}
};