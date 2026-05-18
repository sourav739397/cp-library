/**
 * Description: Tarjan's, DFS once to generate 
 	* strongly connected components in topological order. $a,b$
 	* in same component if both $a\to b$ and $b\to a$ exist.
 	* Uses less memory than Kosaraju b/c doesn't store reverse edges.
 * Time: O(N+M)
 * Source: KACTL
 	* https://github.com/kth-competitive-programming/kactl/blob/master/content/graph/SCC.h
 * Verification: https://cses.fi/problemset/task/1686/
 */

struct SCC {
	int N, ti = 0;
  vector<vector<int>> adj;
	vector<int> disc, comp, stk, comps;
	SCC(int _N){ 
    N = _N, 
    adj.resize(N);
		disc.resize(N), comp.resize(N, -1);
  }
	void ae(int u, int v) { adj[u].push_back(v); }
	int dfs(int u) {
		int low = disc[u] = ++ti; 
    stk.push_back(u);
		for (auto& v: adj[u]) if (comp[v] == -1) {
      low = !disc[v] ? min(low, dfs(v)) : min(low, disc[v]);
    }
		if (low == disc[u]) {
			comps.push_back(u); 
      for (int v = -1; v != u;) {
				comp[v = stk.back()] = u;
        stk.pop_back();
      }
		}
		return low;
	}
	void gen() {
    for (int i = 0; i < N; i++) {
      if (!disc[i]) dfs(i);
    }
		ranges::reverse(comps);
	}
};
