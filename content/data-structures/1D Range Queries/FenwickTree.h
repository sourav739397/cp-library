/**
 * Author: Lukas Polacek
 * Date: 2009-10-30
 * License: CC0
 * Source: folklore/TopCoder
 * Description: Computes partial sums a[0] + a[1] + ... + a[pos - 1], and updates single elements a[i],
 * taking the difference between the old and new value. 0-Indexed.
 * Time: Both operations are $O(\log N)$.
 * Status: Stress-tested
 */
#pragma once

template<class T> struct FenwickTree {
  int N; vector<T> bit;
  FenwickTree(int _N) { N = _N; bit.resize(N); }
  void add(int p, T x) { 
    for (++p; p <= N; p += p&-p) bit[p-1] += x; 
  }
  T sum(int l, int r) { return sum(r+1)-sum(l); }
  T sum(int r) { 
    T res = 0; 
    for(; r; r -= r&-r) res += bit[r-1]; 
    return res; 
  }
  int lower_bound(T sum) {
    if (sum <= 0) return -1;
    int pos = 0;
    for (int pw = 1<<25; pw; pw >>= 1) {
      int npos = pos+pw;
      if (npos <= N && bit[npos-1] < sum) 
        pos = npos, sum -= bit[pos-1];
    }
    return pos;
  }
};