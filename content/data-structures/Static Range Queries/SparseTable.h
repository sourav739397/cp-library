/**
 * Description: Static 1D range (min/max/gcd/lcm/or/and) query. If TL is an issue, use 
	* arrays instead of vectors and store values instead of indices.
 * Source: KACTL
 * Verification: 
	* https://cses.fi/problemset/stats/1647/
	* http://wcipeg.com/problem/ioi1223
	* https://pastebin.com/ChpniVZL
 * Memory: O(N\log N)
 * Time: O(1)
**/

template<class T> struct SparseTable {
  int N, LOG;
  vector<vector<T>> jmp;
  T cmb(T a, T b) { return min(a, b); }
  SparseTable(const vector<T>& v) {
    N = v.size(); LOG = __lg(N);
    jmp.resize(N, vector<T>(LOG + 1));
    for (int i = 0; i < N; ++i) jmp[i][0] = v[i];
    for (int j = 1; j <= LOG; ++j) {
      for (int i = 0; i + (1<<j) <= N; ++i) {
        jmp[i][j] = cmb(jmp[i][j-1], jmp[i+(1<<(j-1))][j-1]);
      }
    }
  }
  T query(int l, int r) {
    int d = __lg(r-l+1);
    return cmb(jmp[l][d], jmp[r-(1<<d)+1][d]);
  }
};