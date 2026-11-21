/**
 * Description: Sort suffixes.
 	* \texttt{isa} is the inverse of \texttt{sa}, and \texttt{lcp} stores
 	* the longest common prefix between every two consecutive elements of \texttt{sa}.
 * Time: O(N\log N)
 * Source: Benq, Claude.ai
 * Verification: 
	* https://open.kattis.com/problems/suffixsorting
	* https://judge.yosupo.jp/problem/suffixarray
 */

#include "SparseTable.h"

struct SuffixArray {
	string S; int N;
	vector<int> sa, isa, lcp;
	SuffixArray(string _S) { 
		N = size(S = _S); genSA(); genLCP();
	}
	void genSA() {
		sa = isa = vector(N, 0); iota(begin(sa), end(sa), 0);
		sort(begin(sa), end(sa), [&](int a, int b) {
			return S[a] < S[b];
		});
		for (int i = 1; i < N; i++) {
			int a = sa[i-1], b = sa[i];
			isa[b] = S[a]==S[b]? isa[a]:i;
		}
		for (int len = 1; len < N; len *= 2) {
			vector<int> s(sa), is(isa), pos(N);
			iota(pos.begin(), pos.end(), 0); is.push_back(-1);
			sa[pos[isa[N-len]]++] = N-len;
			for (int t : s) {
				int T = t - len;
				if (T >= 0) sa[pos[isa[T]]++] = T;
			}
			for (int i = 1; i < N; ++i) {
				int a = sa[i-1], b = sa[i];
				isa[b] = is[a]==is[b]&&is[a+len]==is[b+len]? isa[a]:i;
			}
		}
	}
	void genLCP() { // Kasai's Algo
		lcp.resize(N-1);
		for (int b = 0, h = 0; b < N; b++) {
			if (isa[b] == 0) continue;
			int a = sa[isa[b]-1];
			while (a+h < N && S[a+h] == S[b+h]) h++;
			lcp[isa[b]-1] = h; if (h) h--;
		}
		rmq.init(lcp);
	}
	SparseTable<int> rmq;
	int getLCP(int a, int b) {
		if (a == b) return N-a;
		int l = isa[a], r = isa[b]; if (l > r) swap(l, r);
		return rmq.query(l, r-1);
	}
	pair<int, int> find(const string& p) {
		auto lb = ranges::partition_point(sa, [&](int suf) {
			return S.compare(suf, p.size(), p) < 0;
		});
		auto ub = ranges::partition_point(sa, [&](int suf) {
			return S.compare(suf, p.size(), p) <= 0;
		});
		return {lb-sa.begin(), ub-sa.begin()};
	}
};