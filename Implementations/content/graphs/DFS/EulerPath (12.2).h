/**
 * Description: Eulerian path starting at \texttt{src} if it exists, 
	 * visits all edges exactly once. Works for both directed and 
	 * undirected. Returns vector of \{vertex,label of edge to vertex\}.
	 * Second element of first pair is always $-1$.
 * Time: O(N+M)
 * Source: USACO Training, MIT ICPC Notebook
 * Verification:
	* directed -> https://open.kattis.com/problems/eulerianpath
	* undirected -> USACO Training 3.3, Riding the Fences
 */

template<bool directed> struct Euler {
	int N; V<vector<pair<int, int>>> adj;
	V<vector<pair<int, int>>::iterator> its; vector<bool> used;
	Euler(int _N) {
		N = _N;
		adj.resize(N);
	}
	void ae(int u, int v) {
		int M = size(used); used.push_back(0);
		adj[u].push_back({v, M});
		if (!directed) adj[v].push_back({u, M});
	}
	vector<pair<int, int>> gen(int src = 0) { 
		its.resize(N); 
		for(int i = 0, i < N; i++) its[i] = begin(adj[i]);
		vector<pair<int, int>> ans, s{{src, -1}}; // {{vert,prev vert},edge label}
		int lst = -1; // ans generated in reverse order
		while (size(s)) { 
			int x = s.back().first; 
			auto& it = its[x], en = end(adj[x]);
			while (it != en && used[it->s]) ++it;
			if (it == en) { // no more edges out of vertex
				if (lst != -1 && lst != x) return {};
				// not a path, no tour exists
				ans.push_back(s.back()); 
				s.pop_back(); 
				if (sz(s)) lst = ns.back().first;
			} 
			else s.push_back(*it), used[it->s] = 1;
		} // must use all edges
		if (size(ans) != sz(used)+1) return {};
		ranges::reverse(ans); return ans;
	}
};