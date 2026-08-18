/**
 * Description: Persistent segtree with point updates and range queries.
	\texttt{loc} stores the root of each version.
 * Memory: O(N+Q\log N)
 * Source: usaco.guide
 * Verification: https://cses.fi/problemset/task/1737/
*/

template<class T> struct PersistentSegTree {
	struct Node {
		int l, r; T sum = ID;
		T get() { return sum; }
	};
	static const T ID{};
	T cmb(T a, T b) { return a + b; }
	int N, nxt = 0; vector<Node> seg;
	PersistentSegTree(int _N, int MXV) : N(_N), seg(MXV) {}
	int copy(int p) { seg[nxt] = seg[p]; return nxt++; }
	void pull(int p) {
		seg[p].sum = cmb(seg[seg[p].l].get(), seg[seg[p].r].get());
	}
	int build(const vector<T>& arr, int L, int R) {
		int c = nxt++;
		if (L == R) { seg[c].sum = arr[L]; return c; }
		int M = (L+R)/2;
		seg[c].l = build(arr, L, M);
		seg[c].r = build(arr, M+1, R);
		pull(c); return c;
	}
	int update(int p, int x, T v, int L, int R) {
		if (x < L || R < x) return p;
		int c = copy(p);
		if (L == R) { seg[c].sum = v; return c; } // a[x] = v
		int M = (L+R)/2;
		seg[c].l = update(seg[p].l, x, v, L, M);
		seg[c].r = update(seg[p].r, x, v, M+1, R);
		pull(c); return c;
	}
	T query(int p, int lo, int hi, int L, int R) {
		if (R < lo || hi < L) return ID;
		if (lo <= L && R <= hi) return seg[p].get();
		int M = (L+R)/2;
		return cmb(
			query(seg[p].l, lo, hi, L, M),
			query(seg[p].r, lo, hi, M+1, R)
		);
	}
	vector<int> loc;
	void build(const vector<T>& arr) {
		loc.push_back(build(arr, 0, N-1));
	}
	void update(int ti, int x, T v) {
		loc[ti] = update(loc[ti], x, v, 0, N-1);
	}
	void add(int ti) {
		loc.push_back(loc[ti]);
	}
	T query(int ti, int lo, int hi) {
		return query(loc[ti], lo, hi, 0, N-1);
	}
};