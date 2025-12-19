/**
 * Description: Kosaraju's Algorithm, DFS twice to generate 
 	* strongly connected components in topological order. $a,b$
 	* in same component if both $a\to b$ and $b\to a$ exist.
 * Time: O(N+M)
 * Source: Wikipedia
 * Verification: POI 8 peaceful commission
 */

struct SCC {
	int N; 
  vector<bool> vis;
  vector<vector<int>> adj, radj;
	vector<int> todo, comp, comps; 
	void init(int _N) { 
    N = _N; 
    comp = vector<int>(N,-1);
		adj.resize(N), radj.resize(N), vis.resize(N);
  }
	void ae(int u, int v) { 
    adj[u].push_back(v);
    radj[v].push_back(u); 
  }
	void dfs1(int u) {
		vis[u] = 1; 
    for (auto v: adj[u]) if (!vis[v]) dfs1(v);
		todo.push_back(u); 
  }
	void dfs2(int x, int v) {
		comp[x] = v; 
		each(y,radj[x]) if (comp[y] == -1) dfs2(y,v); }
	void gen() { // fills allComp
		for (int i = 0; i < N; i++) if (!vis[i]) dfs1(i);
		ranges::reverse(todo); 
		each(x,todo) if (comp[x] == -1) dfs2(x,x), comps.pb(x);
	}
};
