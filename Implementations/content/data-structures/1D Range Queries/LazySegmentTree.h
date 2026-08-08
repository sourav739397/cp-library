/**
 * Description: 1D range increment and sum query.
 * Source: Benq
 * Verification: https://cses.fi/problemset/task/1651/
 * Time: O(\log N)
 * Usage: LazySeg<int64_t> T(n); T.update(l, r, val);
 */

template<class T>struct LazySegmentTree {
	const T ID{};
	T cmb(T a, T b) { return a + b; }
	int N = 1; vector<T> seg, lazy;
	LazySegmentTree(int _N) {
		while (N < _N) N *= 2;
		seg = lazy = vector(2*N, ID);
	}
	void push(int ind, int L, int R) {
		seg[ind] += lazy[ind] * (R-L+1); // dependent on operation
		if (L != R) for (int i = 0; i < 2; ++i) { /// prop to children
			lazy[2*ind+i] += lazy[ind];
		}
		lazy[ind] = 0;
	}
	void pull(int ind) { seg[ind] = cmb(seg[2*ind], seg[2*ind+1]); }
	void build() { for (int i = N-1; i >= 1; --i) pull(i); }
	void update(int lo, int hi, T inc, int ind, int L, int R) {
		push(ind, L, R);
		if (hi < L || R < lo) return;
		if (lo <= L && R <= hi) {
			lazy[ind] = inc;
			push(ind, L, R);
			return;
		}
		int M = (L+R) / 2;
		update(lo, hi, inc, 2*ind, L, M);
		update(lo, hi, inc, 2*ind+1, M+1, R);
		pull(ind);
	}
	void update(int lo, int hi, T inc) { update(lo, hi, inc, 1, 0, N-1); }
	T query(int lo, int hi, int ind, int L, int R) {
		push(ind, L, R);
		if (lo > R || L > hi) return ID;
		if (lo <= L && R <= hi) return seg[ind];
		int M = (L+R) / 2;
		return cmb(query(lo,hi,2*ind,L,M), query(lo,hi,2*ind+1,M+1,R));
	}
	T query(int lo, int hi) { return query(lo, hi, 1, 0, N-1); }
};