const int SZ = 1<<30;
template<class T> struct DynamicSegTree {
	struct Node {
		int l, r; T sum = ID;
		T get() { return sum; }
	};
	static const T ID{};
	T cmb(T a, T b) { return a + b; }
	int N, nxt = 0; vector<Node> seg;
	DynamicSegTree(int _N, int MXV) : N(_N), seg(MXV) {}
	void pull(int p) {
		seg[p].sum = cmb(seg[seg[p].l].get(), seg[seg[p].r].get());
	}
	void update(int p, int x, T v, int L, int R) {
		if (x < L || R < x) return;
		if (L == R) { seg[p].sum = v; return; } // a[x] = v
		int M = (L+R)/2;
		seg[c].l = update(seg[p].l, x, v, L, M);
		seg[c].r = update(seg[p].r, x, v, M+1, R);
		pull(c); return c;
	}
	void update(int p, T val, int ind = 1, int L = 0, int R = SZ-1) {
		if (L == R) {
			seg[ind].data += val;
			return;
		}
		int M = (L+R)/2;
		if (p <= M) {
			if (seg[ind].l == -1) {
				seg[ind].l = seg.size();
				seg.push_back(Node());
			}
			update(p, val, seg[ind].l, L, M);
		} 
		else {
			if (seg[ind].r == -1) {
				seg[ind].r = seg.size();
				seg.push_back(Node());
			}
			update(p, val, seg[ind].r, M+1, R);
		}
		pull(ind);
	}
	T query(int lo, int hi, int ind = 1, int L = 0, int R = SZ-1) {
		if (ind == -1) return ID;
		if (lo > R || L > hi) return ID;
		if (lo <= L && R <= hi) return seg[ind].data;
		int M = (L+R)/2;
		return cmb(query(lo,hi,seg[ind].l,L,M), query(lo,hi,seg[ind].r,M+1,R));
	}
};