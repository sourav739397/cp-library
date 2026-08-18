/**
 * Description: Eulerian path starting at \texttt{src},
	 * visiting all edges exactly once. Works for both directed and
	 * undirected.
	 * Returns vector of \{vertex, edge\_id\}, first pair edge\_id = -1.
	 * Eulerian path exists iff all edges are in the same connected component and
	 * for undirected, degree of each node is even (circuit) or
	 * exactly two nodes have odd degree (start and end).
	 * For directed, indegree = outdegree for all nodes (circuit) or
	 * exactly one node has outdegree = indegree + 1 (start) and
	 * exactly one node has indegree = outdegree + 1 (end).
 * Time: O(N+M)
 * Source: USACO Training, MIT ICPC Notebook
 * Verification:
	* directed -> https://cses.fi/problemset/task/1693/
	* undirected -> https://cses.fi/problemset/task/1691
 */

template<bool directed> struct EulerianPath {
	int N; vector<bool> used;
	vector<vector<pair<int, int>>> adj;
	vector<vector<pair<int, int>>::iterator> its;
	EulerianPath(int _N) : N(_N), adj(_N), its(_N) {}
	void ae(int u, int v) {
		int M = size(used); used.push_back(0);
		adj[u].push_back({v, M});
		if (!directed) adj[v].push_back({u, M});
	}
	vector<pair<int, int>> path(int src) {
		for(int u = 0; u < N; u++) its[u] = adj[u].begin();
		vector<pair<int, int>> ans, stk{{src, -1}};
		while (stk.size()) {
			int u = stk.back().first;
			auto& it = its[u], en = adj[u].end();
			while (it != en && used[it->second]) ++it;
			if (it == en) { // no more edges out of vertex
				ans.push_back(stk.back());
				stk.pop_back();
			}
			else stk.push_back(*it), used[it->second] = 1;
		}
		if (ans.size() != used.size()+1) return {};
		ranges::reverse(ans); return ans;
	}
};