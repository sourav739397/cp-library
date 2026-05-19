/**
 * Description: just DFS
 * Time: O(N+M)
 * Source: Own
 */

struct DFS {
	int N;
	vector<bool> vis;
	vector<vector<int>> adj;
	DFS(int _N) {
		N = _N;
		adj.resize(N); vis.resize(N);
	}
	void ae(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	void dfs(int u) {
		vis[u] = true;
		for (auto& v: adj[u]) {
			if (!vis[v]) dfs(v);
		}
	}
};