/**
 * Description: 1D point update and range query where \texttt{cmb} is
  * any associative operation. \texttt{seg[1]==query(0,N-1)}.
 * Time: O(\log N)
 * Source:
  * http://codeforces.com/blog/entry/18051
  * KACTL
 * Verification: SPOJ Fenwick, https://cses.fi/problemset/task/1648/
 */

template<class T> struct SegmentTree {
  const T ID{};
  T cmb(T a, T b) { return a + b; }
  int N = 1; vector<T> seg;
  SegmentTree(int _N) {
    while (N < _N) N *= 2;
    seg.assign(2*N, ID);
  }
  void pull(int p) { 
    seg[p] = cmb(seg[2*p], seg[2*p+1]); 
  }
  void update(int p, T val) { // set val at position p
    seg[p += N] = val;
    for (p /= 2; p > 0; p /= 2) pull(p);
  }
  T query(int l, int r) { // zero-indexed, inclusive
    T lf = ID, rf = ID;
    for (l += N, r += N + 1; l < r; l /= 2, r /= 2) {
      if (l & 1) lf = cmb(lf, seg[l++]);
      if (r & 1) rf = cmb(seg[--r], rf);
    }
    return cmb(lf, rf);
  }
  // int first_at_least(int lo, int val, int ind, int l, int r) { // if seg stores max across range
  //   if (r < lo || val > seg[ind]) return -1;
  //   if (l == r) return l;
  //   int m = (l+r)/2;
  //   int res = first_at_least(lo,val,2*ind,l,m); if (res != -1) return res;
  //   return first_at_least(lo,val,2*ind+1,m+1,r);
  // }
};