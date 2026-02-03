/**
 * Description: Calculates a valid assignment to boolean variables a, b, c,... 
 	* to a 2-SAT problem, so that an expression of the type 
 	* $(a\|\|b)\&\&(!a\|\|c)\&\&(d\|\|!b)\&\&...$ becomes true, 
 	* or reports that it is unsatisfiable.
 	* Negated variables are represented by bit-inversions (\texttt{\tilde{}x}).
 * Usage:
	* TwoSat ts;
	* ts.either(0, \tilde3); // Var 0 is true or var 3 is false
	* ts.setVal(2); // Var 2 is true
	* ts.atMostOne({0,\tilde1,2}); // <= 1 of vars 0, \tilde1 and 2 are true
	* ts.solve(N); // Returns true iff it is solvable
	* ts.ans[0..N-1] holds the assigned values to the vars
 * Source: KACTL
 * Verification: https://codeforces.com/contest/1007/problem/D
 	* https://cses.fi/problemset/task/1684/
 */

#include "SCCK.h"

struct TwoSAT {
	int N = 0; 
  vector<pair<int, int>> edges;
	void init(int _N) { N = _N; }
	int addVar() { return N++; }
	void either(int x, int y) { 
		x = max(2*x, -1-2*x), y = max(2*y, -1-2*y);
		edges.push_back({x, y}); 
  }
	void implies(int x, int y) { either(~x, y); }
	void must(int x) { either(x, x); }
	void atMostOne(const vector<int>& li) {
		if (li.size() <= 1) return;
		int cur = ~li[0];
		for (int i = 2; i < li.size(); i++) {
			int next = addVar();
			either(cur, ~li[i]); either(cur,next);
			either(~li[i], next); cur = ~next;
		}
		either(cur, ~li[1]);
	}
	vector<bool> gen() {
    SCC S(2*N);
    for (auto& [u, v]: edges) {
      S.ae(u^1, v);
      S.ae(v^1, u);
    }
		S.gen(); ranges::reverse(S.comps); // reverse topo order
		for (int i = 0; i < 2*N; i += 2) {
			if (S.comp[i] == S.comp[i^1]) return {};
    }
		vector<int> tmp(2*N); 
    for (auto& i: S.comps) if (!tmp[i]) {
      tmp[i] = 1, tmp[S.comp[i^1]] = -1;
    }
		vector<bool> ans(N); 
    for (int i = 0; i < N; i++) {
      ans[i] = (tmp[S.comp[2*i]] == 1);
    } 
		return ans;
	}
};