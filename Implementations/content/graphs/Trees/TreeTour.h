/**
 * Description: Subtree corresponding to \texttt{x} -> range \texttt{[st[x],en[x]]}
 * Source: USACO
 */

struct TreeTour {
	int N, timer = -1;
	vector<int> start, end;
	vector<vector<int>> adj;
	EularTour(int _N) {
		N = _N;
		adj.resize(N);
		start.resize(N), end.resize(N);
	}
	void ae(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	void dfs(int u, int p = -1) {
		start[u] = ++timer;
		for (auto& v: adj[u]) if (v != p) { 
			dfs(v, u);
		}
		end[u] = timer; 
	}
};