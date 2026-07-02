/**
 * Description: Undirected
 * Source: https://www.geeksforgeeks.org/detect-cycle-in-a-graph/
 * Verification: VT HSPC 2019 D
 */

struct UnDirectedCycle {
	int N, st, ed;
	vector<bool> vis;
	vector<int> cyc, par;
	vector<vector<int>> adj;
	UnDirectedCycle(int _N) {
		N = _N;
		adj.resize(N);
		par.resize(N, -1), vis.resize(N);
	}
	void ae(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	vector<int> gen() {
		st = -1;
		for (int u = 0; u < N; u++) {
			if (!vis[u] && dfs(u, -1)) break;
		}
		if (st == -1) return {};
		cyc.push_back(st);
		for (int u = ed; u != st; u = par[u]) {
			cyc.push_back(u);
		}
		cyc.push_back(st);

		return cyc;
	}
	bool dfs(int u, int p = -1) {
		vis[u] = true;
		for (auto& v: adj[u]) {
			if(v == p) continue;
			if (vis[v]) {
				ed = u;
				st = v;
				return true;
			}
			par[v] = u;
			if (dfs(v, u)) return true;
		}
		return false;
	}
};
