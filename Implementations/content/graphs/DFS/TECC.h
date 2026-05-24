/**
 * Description: Computes 2-edge-connected components (TECC) of an
 	* undirected graph using Tarjan's low-link algorithm.
 	* Two vertices belong to the same component iff there is no bridge
 	* on any path between them.
 * Source: https://cp-algorithms.com/graph/bridge-searching.html
 * Verification: https://judge.yosupo.jp/problem/two_edge_connected_components
 */

struct TECC {
	int N, ti = 0;
	vector<int> disc, low, comp;
	vector<vector<int>> adj, comps;
	TECC(int _N) {
		N = _N;
		disc.resize(N), low.resize(N); 
		adj.resize(N), comp.resize(N, -1);
	}
	void ae(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	bool isBridge(int u, int v) {
		if (disc[u] > disc[v]) swap(u, v);
		return low[v] > disc[u];
	}
	void dfs(int u, int p) {
		bool pSkip = false;
		disc[u] = low[u] = ++ti;
		for (auto& v: adj[u]) {
			if (v == p && !pSkip) {
				pSkip = true;
				continue;
			}
			if (!disc[v]) {
				dfs(v, u);
				low[u] = min(low[u], low[v]);
				// if (isBridge(u, v)) {} // it's a bridge
			}
			else low[u] = min(low[u], disc[v]);
		}
	}
	void getComps(int u) {
		comps[comp[u]].push_back(u);
		for (auto& v: adj[u]) {
			if (~comp[v] || isBridge(u, v)) continue;
			comp[v] = comp[u];
			getComps(v);
		}
	}
	void gen() {
		for (int u = 0; u < N; u++) {
			if (!disc[u]) dfs(u, -1);
		}
		int id = 0;
		for (int u = 0; u < N; u++) {
			if (comp[u] == -1) {
				comp[u] = id++;
				comps.emplace_back();
				getComps(u);
			}
		}
	}
};