/**
* Description: SegmentTree on values instead of indices.
	* 0-indexed interval \texttt{[lo,hi)}.
	* $SZ=2^p$ and all values in $a$ must lie in $[0,SZ)$.
* Memory: O(N\log N)
* Time: O(\log N) query
* Source: https://codeforces.com/blog/entry/52854
* Verification: http://www.spoj.com/problems/MKTHNUM/
* Usage:
	* WaveletTree<SZ> w; w.build(a);
	* w.kth(lo, hi, k) = k-th smallest in [lo, hi)
	* w.count(lo, hi, k) = occurrences of k in [lo, hi)
	* w.rank(lo, hi, k) = number of elements <= k in [lo, hi)
*/

template<int SZ> struct WaveletTree {
	vector<int> nexl[SZ], nexr[SZ];
	void build(vector<int> a, int ind = 1, int L = 0, int R = SZ-1) {
		if (L == R) return;
		nexl[ind] = nexr[ind] = {0};
		vector<int> A[2]; int M = (L+R)/2;
		for (auto& t: a) {
			A[t>M].push_back(t);
			nexl[ind].push_back(A[0].size());
			nexr[ind].push_back(A[1].size());
		}
		build(A[0], 2*ind, L, M); build(A[1], 2*ind+1, M+1, R);
	}
	int kth(int lo, int hi, int k, int ind = 1, int L = 0, int R = SZ-1) {
		if (L == R) return L;
		int M = (L+R)/2, t = nexl[ind][hi]-nexl[ind][lo];
		if (t >= k) return kth(nexl[ind][lo], nexl[ind][hi], k, 2*ind, L, M);
		return kth(nexr[ind][lo], nexr[ind][hi], k-t, 2*ind+1, M+1, R);
	}
	int count(int lo, int hi, int k, int ind = 1, int L = 0, int R = SZ-1) {
		if (k < L || R < k) return 0;
		if (L == R) return hi - lo;
		int M = (L+R)/2;
		if (k <= M) return count(nexl[ind][lo], nexl[ind][hi], k, 2*ind, L, M);
		return count(nexr[ind][lo], nexr[ind][hi], k, 2*ind+1, M+1, R);
	}
	int rank(int lo, int hi, int k, int ind = 1, int L = 0, int R = SZ-1) {
		if (k < L) return 0;
		if (R <= k) return hi - lo;
		int M = (L+R)/2;
		return rank(nexl[ind][lo], nexl[ind][hi], k, 2*ind, L, M)
			 + rank(nexr[ind][lo], nexr[ind][hi], k, 2*ind+1, M+1, R);
	}
};
