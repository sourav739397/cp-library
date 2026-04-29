/**
 * Description: Calculates a valid assignment to boolean variables a, b, c,... 
 	* to a 2-SAT problem, so that an expression of the type 
 	* $(a\|\|b)\&\&(!a\|\|c)\&\&(d\|\|!b)\&\&...$ becomes true, 
 	* or reports that it is unsatisfiable.
 	* Negated variables are represented by bit-inversions (\texttt{\tilde{}x}).
 * Usage:
	* TwoSat G(n);
	* ts.either(0, \tilde3); // Var 0 is true or var 3 is false
	* G.gen(N); // Returns true iff it is solvable
	* G.ans[0..N-1] holds the assigned values to the vars
 * Source: https://cp-algorithms.com/graph/2SAT.html
 * Verification: https://cses.fi/problemset/task/1684/
 */

#include "SCCK.h"

struct TwoSAT {
	int N;
  vector<bool> ans;
  vector<pair<int, int>> edges;
	TwoSAT(int _N) { 
    N = _N; 
    ans.resize(N);
  }
	void either(int u, int v) { 
		u = max(2*u, -1-2*u), v = max(2*v, -1-2*v);
		edges.push_back({u, v}); 
  }
	bool gen() {
    SCC S(2*N);
    for (auto& [u, v]: edges) {
      S.ae(u^1, v);
      S.ae(v^1, u);
    }
		S.gen(); 
    for (int i = 0; i < N; i++) {
      if (S.comp[2*i] == S.comp[2*i^1]) return false;
      ans[i] = S.comp[2*i] > S.comp[2*i^1];
    }
    return true;
	}
};