/**
 * Description: Linear-time suffix array.
 * Time: $O(N)$, \tilde 69ms for $N=5\cdot 10^5$
 * Usage: SA_IS(s, 26) // all entries must be in [0, 26)
 * Source: https://github.com/atcoder/ac-library/blob/master/atcoder/string.hpp
 * Verification: https://judge.yosupo.jp/problem/suffixarray
*/

vector<int> SA_IS(const vector<int>& s, int upper) {
	int n = size(s); if (!n) return {};
	vector<int> sa(n); vector<bool> ls(n);
	for (int i = n - 2; i >= 0; i--) {
		ls[i] = (s[i] == s[i+1]) ? ls[i+1] : (s[i] < s[i+1]);
	}
	vector<int> sum_l(upper), sum_s(upper);
	for (int i = 0; i < n; i++) {
		(ls[i] ? sum_l[s[i]+1] : sum_s[s[i]])++;
	}
	for (int i = 0; i < upper; i++) {
		if (i) sum_l[i] += sum_s[i-1];
		sum_s[i] += sum_l[i];
	}
	auto induce = [&](const vector<int>& lms) {
		fill(begin(sa), end(sa), -1);
		vector<int> buf = sum_s;
		for (int d: lms) if (d != n) sa[buf[s[d]]++] = d;
		buf = sum_l; sa[buf[s[n-1]]++] = n-1;
		for (int i = 0; i < n; i++) {
			int v = sa[i]-1;
			if (v >= 0 && !ls[v]) sa[buf[s[v]]++] = v;
		}
		buf = sum_l;
		for (int i = n-1; i >= 0; i--) {
			int v = sa[i]-1;
			if (v >= 0 && ls[v]) sa[--buf[s[v]+1]] = v;
		}
	};
	vector<int> lms_map(n+1, -1), lms; int m = 0;
	for (int i = 1; i < n; i++) if (!ls[i-1] && ls[i]) {
		lms_map[i] = m++, lms.push_back(i);
	}
	induce(lms);
	vector<int> sorted_lms;
	for (int v: sa) if (lms_map[v] != -1) {
		sorted_lms.push_back(v);
	}
	vector<int> rec_s(m); int rec_upper = 0;
	for (int i = 1; i < m; i++) {
		int l = sorted_lms[i-1], r = sorted_lms[i];
		int end_l = lms_map[l]+1 < m ? lms[lms_map[l]+1] : n;
		int end_r = lms_map[r]+1 < m ? lms[lms_map[r]+1] : n;
		bool same = 0;
		if (end_l-l == end_r-r) {
			for (; l < end_l && s[l] == s[r]; ++l, ++r);
			if (l != n && s[l] == s[r]) same = 1;
		}
		rec_s[lms_map[sorted_lms[i]]] = (rec_upper += !same);
	}
	vector<int> rec_sa = SA_IS(rec_s, rec_upper+1);
	for (int i = 0; i < m; i++) sorted_lms[i] = lms[rec_sa[i]];
	induce(sorted_lms);
	return sa;
}