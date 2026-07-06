/**
 * Description: Answers queries offline in (N+Q)sqrt(N)
	* Also see Mo's on trees
 * Source: Codeforces
 * Verification: https://codeforces.com/contest/86/problem/D
 */

template<class T, class U> struct MO {
	U cur = 0;
	const int BLOCK = 500;
	int l = 0, r = -1, q = 0; // l = start; r = prev start
	vector<array<int, 3>> todo;
	void addQuery(int L, int R) {
		todo.push_back({L, R, q++});
	}
	void insert(int p, bool b) { }
	void erase(int p, bool b) { }
	U query(int L, int R) { // modify just interval
		while (l > L) insert(--l, 0);
		while (r < R) insert(++r, 1);
		while (l < L) erase(l++, 0);
		while (r > R) erase(r--, 1);
		return cur;
	}
	vector<U> gen() {
		sort(begin(todo), end(todo), [&](auto& x, auto& y) {
			if (x[0]/BLOCK != y[0]/BLOCK) return x[0] < y[0];
			return x[0]/BLOCK%2 ? x[1] < y[1] : x[1] > y[1];
		});

		vector<U> ans(q);
		for (auto& [L, R, i]: todo) {
			ans[i] = query(L, R);
		}
		return ans;
	}
};